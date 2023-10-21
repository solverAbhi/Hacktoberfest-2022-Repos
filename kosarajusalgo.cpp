#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void DFS(int v, vector<bool> &visited, stack<int> &s) {
        visited[v] = true;

        for (int u : adj[v]) {
            if (!visited[u]) {
                DFS(u, visited, s);
            }
        }

        s.push(v);
    }

    void reverseGraph() {
        vector<vector<int>> reversedAdj(V);

        for (int v = 0; v < V; ++v) {
            for (int u : adj[v]) {
                reversedAdj[u].push_back(v);
            }
        }

        adj = reversedAdj;
    }

    void findSCCs() {
        vector<bool> visited(V, false);
        stack<int> s;

        for (int v = 0; v < V; ++v) {
            if (!visited[v]) {
                DFS(v, visited, s);
            }
        }

        reverseGraph();
        fill(visited.begin(), visited.end(), false);

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                vector<int> scc;
                DFS(v, visited, scc);

                cout << "SCC: ";
                for (int u : scc) {
                    cout << u << " ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    cout << "Strongly Connected Components:\n";
    g.findSCCs();

    return 0;
}
