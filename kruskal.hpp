//The following code was taken from Geeks for Geeks
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Class: DSU 
// Implements an efficient structure to track and merge disjoint sets
class DSU {
    vector<int> parent, rank;
public:
    // Constructor: DSU
    // Initializes parent and rank arrays for n elements
    // Parameters:
    // - n, total number of nodes
    // Time Complexity: O(V)
    // Space Complexity: O(V)
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    // Function: find
    // Finds the representative (root) of the set that node i belongs to
    // Applies path compression to speed up future queries
    // Parameters:
    // - i, node whose root set representative is to be found.
    // Returns:
    // - The root of the set containing node i.
    // Time Complexity: O(α(V))
    // Space Complexity: O(1)
    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    // Function: unite
    // Merges the sets containing nodes x and y
    // Uses union by rank to minimize tree height
    // Parameters:
    // - x & y, nodes to be united
    // Time Complexity: O(α(V))
    // Space Complexity: O(1)
    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};

// Function: comparator
// Comparison function for sorting edges by weight (ascending order)
// Parameters:
// - a & b, edges represented as {u, v, w}
// Returns:
// - true if a's weight < b's weight
// Time Complexity: O(1)
// Space Complexity: O(1)
bool comparator(vector<int> &a, vector<int> &b) {
    return a[2] < b[2];
}


// Function: kruskalsMST
// Implements Kruskal's Algorithm to compute the Minimum Spanning Tree (MST)
// of a weighted undirected graph
// Parameters:
// - V, number of vertices.
// - edges, list of edges where each edge is {u, v, w}.
// Returns:
// - A pair containing:
//   (1) total cost (int)
//   (2) list of edges included in the MST (vector<vector<int>>)
// Time Complexity: O(E log E)
// Space Complexity: O(V + E)
pair<int, vector<vector<int>>> kruskalsMST(int V, vector<vector<int>> &edges) {
    sort(edges.begin(), edges.end(), comparator);
    DSU dsu(V);
    int cost = 0;
    vector<vector<int>> mstEdges;

    for (auto &e : edges) {
        int x = e[0], y = e[1], w = e[2];
        if (dsu.find(x) != dsu.find(y)) {
            dsu.unite(x, y);
            cost += w;
            mstEdges.push_back(e);
            if ((int)mstEdges.size() == V - 1) break;
        }
    }
    return {cost, mstEdges};
}
