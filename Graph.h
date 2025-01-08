#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <iostream>
#include <utility>

const int VERTEX_NUM = 100;

struct Point {
    double x;
    double y;
    int id;

    double distance_to(const Point& other) const {
        return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

class Graph {
private:
    std::vector<Point> points;
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjacency_list;
public:
    std::vector<Point>& get_points()
    {
        return points;
    }

    std::unordered_map<int, std::vector<std::pair<int, double>>>& get_adjacency_list()
    {
        return adjacency_list;
    }

    void generate_graph(int R);
    std::pair<double, std::vector<int>> nearest_neighbor_path(int start_vertex);
    void print_graph() const;
};

#endif // GRAPH_H
