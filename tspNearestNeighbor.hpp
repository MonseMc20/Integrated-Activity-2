/*
   Traveling Salesman Problem (TSP) - Nearest Neighbor Heuristic

    Description:
    This file implements a function that approximates a solution 
    to the Traveling Salesman Problem (TSP) using the Nearest Neighbor 
    heuristic. It calculates a route that visits every neighborhood 
    exactly once and returns to the starting point.
*/

#ifndef TSP_NEAREST_NEIGHBOR_HPP
#define TSP_NEAREST_NEIGHBOR_HPP

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
    Function: tspNearestNeighbor
    Description:
        Approximates a solution for the Traveling Salesman Problem (TSP)
        using the Nearest Neighbor heuristic, starting from node 0 
        (neighborhood A) and returning to it at the end.
    
    Parameters:
        - n: number of neighborhoods (nodes in the graph)
        - graph: adjacency matrix representing distances between neighborhoods
    
    Return value:
        None. The function prints the route and the total distance.
*/
void tspNearestNeighbor(int n, vector<vector<int>> &graph) {
    vector<bool> visited(n, false);  // Tracks which neighborhoods have been visited
    vector<int> path;                // Stores the route path
    int current = 0;                 // Start at neighborhood A (index 0)
    int totalDistance = 0;           // Accumulates total travel distance

    path.push_back(current);
    visited[current] = true;

    // Visit all neighborhoods exactly once
    for (int i = 1; i < n; i++) {
        int nearest = -1;
        int minDistance = INT_MAX;

        // Find the closest unvisited neighborhood
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[current][j] > 0 && graph[current][j] < minDistance) {
                minDistance = graph[current][j];
                nearest = j;
            }
        }

        // Move to the closest neighborhood
        if (nearest != -1) {
            visited[nearest] = true;
            path.push_back(nearest);
            totalDistance += minDistance;
            current = nearest;
        }
    }

    // Return to the origin (A)
    if (graph[current][0] > 0) {
        totalDistance += graph[current][0];
    }
    path.push_back(0);

    cout << "\n2. Mail Delivery Route:\n";
    for (int i = 0; i < static_cast<int>(path.size()); i++) {
        cout << char('A' + path[i]);
        if (i < static_cast<int>(path.size()) - 1) {
            cout << " -> ";
        }
    }
    cout << "\nTotal distance: " << totalDistance ;
}

#endif
