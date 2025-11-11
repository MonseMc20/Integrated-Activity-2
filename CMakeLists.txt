cmake_minimum_required(VERSION 3.15)
project(voronoi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar CGAL
find_package(CGAL REQUIRED)

# Crear ejecutable
add_executable(voronoi voronoi.cpp)

# Enlazar librerías de CGAL
target_link_libraries(voronoi CGAL::CGAL)
