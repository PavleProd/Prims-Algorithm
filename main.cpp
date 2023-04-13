#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

// Undirected Weighted Graph implemented using adjacency list
class Graph {
private:
    vector<vector<pair<int,int>>> list;
public:
    explicit Graph(int numEdges) {
        for(int i = 0; i < numEdges; i++) {
            list.emplace_back(vector<pair<int,int>>());
        }
    }
    void addEdge(int i, int j, int weight) {
        if(i >= list.size() || j >= list.size() || i < 0 || j < 0) {
            throw invalid_argument("Wrong argument passed");
        }
        list[i].push_back(pair<int,int>(j, weight));
        list[j].push_back(pair<int,int>(i, weight));
    }

    vector<pair<int,int>> getEdges(int i) {
        return list[i];
    }

    void print() {
        for(int i = 0; i < list.size(); i++) {
            cout << i << ": ";
            for(int j = 0; j < list[i].size(); j++) {
                cout <<  "(" << list[i][j].first << ","
                << list[i][j].second << ")" <<(j != list[i].size() - 1 ? ", " : "");
            }
            cout << "\n";
        }
    }

    int getNumVertices() const {
        return list.size();
    }
};


// Struct for keeping track of priority queue element information
class Tuple {
public:
    int weight;
    int i;
    int j;

    Tuple(int i, int j, int weight) {
        this->weight = weight;
        this->i = i;
        this->j = j;
    }
};

// Class for comparing two tuples, returns one with minimal weight
class Comparator {
public:
    bool operator()(Tuple t1, Tuple t2) {
        return t1.weight > t2.weight;
    }
};

// Returns minimal spanning tree for the given weighted graph
Graph primsAlgorithm(Graph& originalGraph) {
    int numVertices = originalGraph.getNumVertices();
    Graph msp(numVertices); // minimal spanning tree
    vector<bool> visited(numVertices, false);
    priority_queue<Tuple, vector<Tuple>, Comparator> pq;

    int i = 1;
    int next = 0; // first vertices in minimum spanning tree is 0
    while(i < numVertices) {
        vector<pair<int,int>> edges = originalGraph.getEdges(next);
        visited[next] = true;
        for(auto edge : edges) { // adds all edges of the vertices to the priority queue
            if(!visited[edge.first]) { // we don't need to add edges to already added vertices
                pq.push(Tuple(next, edge.first, edge.second));
            }
        }
        i++;
        while(!pq.empty()) { // if it's empty then some vertices is not connected to the rest of the graph
            Tuple tuple = pq.top();
            pq.pop();
            if(visited[tuple.j]) { // already in minimal spanning tree
                continue;
            }

            next = tuple.j; // for the next iteration
            msp.addEdge(tuple.i, tuple.j, tuple.weight);
            break;
        }
    }

    return msp;
}

// function that initiates graph from file containing(i j weight) edge parameters
Graph initGraph(int numVertices, const string& fileName) {
    Graph graph(numVertices);
    ifstream edges(fileName);
    string line;
    while(getline(edges, line)) {
        stringstream ss(line); // for splitting string
        int i, j, weight;
        ss >> i >> j >> weight;
        graph.addEdge(i, j, weight);
    }
    edges.close();

    return graph;
}

int main() {
    Graph graph = initGraph(8, "edges.txt"); // graph from the lecture
    cout << "Graph from the lecture:\n";
    graph.print();
    Graph msp = primsAlgorithm(graph);
    cout << "Minimal spanning tree:\n";
    msp.print();
}