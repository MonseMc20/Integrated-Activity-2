#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }
    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};

bool comparator(vector<int> &a, vector<int> &b) {
    return a[2] < b[2];
}

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
