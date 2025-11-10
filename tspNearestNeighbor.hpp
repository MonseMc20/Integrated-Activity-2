/*
   Traveling Salesman Problem (TSP) - Nearest Neighbor 
    Description:
    This file implements two functions:
    tspNearestNeighbor() — Runs the Nearest Neighbor heuristic
    from a specific starting city.
    tspRepetitiveNearestNeighbor() — Runs tspNearestNeighbor()
    from every city and selects the best (shortest) route.
*/

#ifndef TSP_NEAREST_NEIGHBOR_HPP
#define TSP_NEAREST_NEIGHBOR_HPP

#include <iostream>
#include <vector>
using namespace std;

/*
    Function: tspNearestNeighbor
    Description:
    Runs the Nearest Neighbor algorithm starting from a specific city.

    Parameters:
    n: number of cities
    start: index of the starting city (0-based)
    graph: adjacency matrix with distances between cities

    Return value:
    A pair containing:
     Total distance of the route
     Vector with the route order
*/
pair<int, vector<int>> tspNearestNeighbor(int n, int start, const vector<vector<int>> &graph) {
    vector<bool> visited(n, false);  
    vector<int> path;                
    int current = start;             
    int totalDistance = 0;           

    path.push_back(current);
    visited[current] = true;

    for (int i = 1; i < n; i++) {
        int nearest = -1;
        int minDistance = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[current][j] > 0 && graph[current][j] < minDistance) {
                minDistance = graph[current][j];
                nearest = j;
            }
        }

        if (nearest != -1) {
            visited[nearest] = true;
            path.push_back(nearest);
            totalDistance += minDistance;
            current = nearest;
        }
    }

    if (graph[current][start] > 0) {
        totalDistance += graph[current][start];
    }
    path.push_back(start);

    // Return both total distance and path
    return {totalDistance, path};
}

/*
    Function: tspRepetitiveNearestNeighbor
    Description:
    Executes the Nearest Neighbor heuristic starting from every city
    and selects the route with the smallest total distance.

    Parameters:
    n: number of neighborhoods
    graph: adjacency matrix with distances between neighborhoods

    Return value:
    None — it prints the best route and total distance.
*/
void tspRepetitiveNearestNeighbor(int n, const vector<vector<int>> &graph) {
    int bestDistance = INT_MAX;
    vector<int> bestPath;

    for (int start = 0; start < n; start++) {
        pair<int, vector<int>> result = tspNearestNeighbor(n, start, graph);

        if (result.first < bestDistance) {
            bestDistance = result.first;
            bestPath = result.second;
        }
    }

    cout << "\n2. Mail Delivery Route:\n";
    for (int i = 0; i < static_cast<int>(bestPath.size()); i++) {
        cout << char('A' + bestPath[i]);
        if (i < static_cast<int>(bestPath.size()) - 1) {
            cout << " -> ";
        }
    }
    cout << "\nTotal distance: " << bestDistance << " km\n";
}

#endif
