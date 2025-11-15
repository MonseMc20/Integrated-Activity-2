/* 
    Voronoi Diagram 
    Description:
    This program constructs and displays a Voronoi diagram from a given set 
    of 2D points using the CGAL (Computational Geometry Algorithms Library).
    It outputs the coordinates of the sites and the vertices of each Voronoi cell.

*/

#ifndef VORONOI_DIAGRAM_HPP
#define VORONOI_DIAGRAM_HPP

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <iostream>
#include <vector>
using namespace std;

// Type definitions for geometric kernel and structures
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Delaunay_triangulation_2<Kernel> DelaunayTriangulation;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DelaunayTriangulation> AdaptationTraits;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DelaunayTriangulation> AdaptationPolicy;
typedef CGAL::Voronoi_diagram_2<DelaunayTriangulation, AdaptationTraits, AdaptationPolicy> VoronoiDiagram;

typedef AdaptationTraits::Site_2 Site2;
typedef Kernel::Point_2 Point2;

/*
    Function: displayVoronoiDiagram
    Description:
    Displays the coordinates of the sites and the vertices of each Voronoi cell.

    Parameters:
    voronoiDiagram: The Voronoi diagram object constructed from the given points.
    points: Vector of 2D points used as sites to generate the Voronoi diagram.

    Return value:
    None — prints all site coordinates and Voronoi cells to the console.
*/
void displayVoronoiDiagram(const VoronoiDiagram &voronoiDiagram, const vector<Point2> &points) {
    cout << "Sites coordinates:\n[";
    for (size_t i = 0; i < points.size(); i++) {
        cout << "(" << points[i].x() << "," << points[i].y() << ")";
        if (i != points.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]\n\n";

    cout << "Voronoi polygons:\n[\n";
    for (auto face = voronoiDiagram.faces_begin(); face != voronoiDiagram.faces_end(); ++face) {
        if (face->is_unbounded()) {
            continue;
        }

        cout << "  [";
        auto edgeStart = face->ccb();
        auto edge = edgeStart;

        do {
            auto source = edge->source()->point();
            cout << "(" << source.x() << "," << source.y() << ")";
            ++edge;

            if (edge != edgeStart) {
                cout << ", ";
            }
        } while (edge != edgeStart);

        cout << "],\n";
    }
    cout << "]\n";
}

/*
    Function: main
    Description:
    Defines a set of 2D points, constructs a Voronoi diagram using CGAL, 
    and displays the site coordinates and resulting Voronoi cells.

    Parameters:
    None

    Return value:
    0 — indicates successful execution.
*/
int main() {
    // Main site points
    vector<Point2> points = {
        Point2(200, 500),
        Point2(300, 100),
        Point2(450, 150),
        Point2(520, 480)
    };

    // Additional points to enclose the diagram boundaries
    points.push_back(Point2(-1000, -1000));
    points.push_back(Point2(-1000, 1000));
    points.push_back(Point2(1000, -1000));
    points.push_back(Point2(1000, 1000));

    // Construct the Voronoi diagram
    VoronoiDiagram voronoiDiagram;
    for (const auto &point : points) {
        voronoiDiagram.insert(Site2(point));
    }

    // Display the diagram’s sites and polygons
    displayVoronoiDiagram(voronoiDiagram, points);

    return 0;
}

#endif
