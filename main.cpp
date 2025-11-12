#include "tspNearestNeighbor.hpp"
#include "kruskal.hpp"
#include "fordFulkerson.hpp"
#include <fstream>
#include <cstdlib>  
using namespace std;

int main() {

    // --- part 1 ---
    ifstream file("graph.txt");
    if (!file.is_open()) {
        cerr << "Error: could not open file.\n";
        return 1;
    }

    int V;
    file >> V; // Read number of vertices

    vector<vector<int>> matrix(V, vector<int>(V));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            file >> matrix[i][j];
        }
    }

    vector<vector<int>> edges;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (matrix[i][j] != 0) {
                edges.push_back({i, j, matrix[i][j]});
            }
        }
    }

    auto [cost, mstEdges] = kruskalsMST(V, edges);
      cout << "\n PART 1:\n";
    for (auto &e : mstEdges) {
        cout << e[0] << " " << e[1] << " ";;
    }
    
    // --- part 2 ---
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file.\n";
        return 1;
    }

    int n;
    inputFile >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> graph[i][j];
        }
    }

    inputFile.close();

    // --- part 3 ---
    
    readFile("small_instance.dimacs");
    if (source == -1 || sink == -1) {
        return 1;
    }
    int maxFlow = edmondsKarp(n, source, sink);
    std::cout << "The maximum possible flow is " << maxFlow << std::endl;
    return 0;


    tspRepetitiveNearestNeighbor(n, graph);
     cout << "\n PART 4:\n";
//  --- Part 4 ---
    int ret = system(".\\build\\Release\\voronoi.exe"); // Para Windows
    if (ret != 0) {
        std::cerr << "Error al ejecutar voronoi.exe\n";
    }
    return 0;

    return 0;
}
