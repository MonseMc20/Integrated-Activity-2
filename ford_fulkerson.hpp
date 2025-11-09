#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int capacity;
};

int n;
int source = -1;
int sink = -1;
std::vector<std::vector<int>> capacity;
std::vector<std::vector<int>> adj;

using Graph = std::vector<std::vector<Edge>>;

void readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    int nodes = 0;
    int edges = 0;
    Graph graph;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        char type;
        ss >> type;

        if (type == 'c') {
            //The code reads a comment line, ignores it
        } else if (type == 'p') {
            //The code reads a problem line
            std::string format;
            ss >> format >> nodes >> edges;
            graph.resize(nodes);

        } else if (type == 'n'){
            //The code reads a source or sink node
            int nodeID;
            char type;
            ss >> nodeID >> type;
            if (type == 's'){
                //Source line
                source = nodeID - 1;
            } else if (type == 't'){
                //Sink line
                sink = nodeID - 1;
            }
        } else if (type == 'a') {
            int u;
            int v; 
            int capacity;
            ss >> u >> v >> capacity;
            graph[u-1].push_back({v - 1, capacity});
        }
    }
    file.close();
    n = nodes;
    capacity.assign(n, std::vector<int>(n, 0));
    adj.resize(n);
    for (int u = 0; u < n; ++u) {
        for (const auto& edge : graph[u]) {
            int v = edge.to;
            capacity[u][v] += edge.capacity; // In case of multiple edges
            adj[u].push_back(v);
            adj[v].push_back(u); // Add reverse edge for residual graph
        }
    }
    
}

int bfs(int s, int t, std::vector<int>& parent) {
    std::fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    std::queue<std::pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = std::min(flow, capacity[cur][next]);
                if (next == t) {
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    
    }

    return 0;
}
int edmondsKarp(int nodes, int s, int t) {
    int flow = 0;
    std::vector<int> parent(nodes);

    while (bfs(s, t, parent)) {
        
        int new_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            new_flow = std::min(new_flow, capacity[u][v]);
        }

       
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= new_flow;
            capacity[v][u] += new_flow;
        }

        flow += new_flow;
    }

    return flow;
}
