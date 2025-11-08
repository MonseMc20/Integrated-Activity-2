#include "tspNearestNeighbor.hpp"
#include <fstream>
using namespace std;

int main() {
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

    tspNearestNeighbor(n, graph);

    return 0;
}
