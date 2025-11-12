#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>

#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT> AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT, AT, AP> VD;

typedef AT::Site_2 Site_2;
typedef K::Point_2 Point_2;

int main() {
    // Puntos principales
    std::vector<Point_2> points = {
        Point_2(200,500),
        Point_2(300,100),
        Point_2(450,150),
        Point_2(520,480)
    };

    // Puntos artificiales para "cerrar" el diagrama
    points.push_back(Point_2(-1000, -1000));
    points.push_back(Point_2(-1000, 1000));
    points.push_back(Point_2(1000, -1000));
    points.push_back(Point_2(1000, 1000));

    VD vd;
    for(const auto& p : points) {
        vd.insert(Site_2(p));
    }

    // Mostrar coordenadas de los sitios
    std::cout << "Sites coordinates:\n[";
    for(size_t i = 0; i < points.size(); ++i) {
        std::cout << "(" << points[i].x() << "," << points[i].y() << ")";
        if(i != points.size()-1) std::cout << ", ";
    }
    std::cout << "]\n\n";

    // Listado de polígonos
    std::cout << "Voronoi polygons:\n[\n";
    for(auto f = vd.faces_begin(); f != vd.faces_end(); ++f) {
        if(f->is_unbounded()) continue; // ignorar caras infinitas
        std::cout << "  [";
        auto ec_start = f->ccb();
        auto ec = ec_start;
        do {
            auto s = ec->source()->point();
            std::cout << "(" << s.x() << "," << s.y() << ")";
            ++ec;
            if(ec != ec_start) std::cout << ", ";
        } while(ec != ec_start);
        std::cout << "],\n";
    }
    std::cout << "]\n";

    return 0;
}
