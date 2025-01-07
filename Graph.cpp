#include "Graph.h"
#include <random>
#include <algorithm>
#include <limits>
#include <cmath>

void Graph::generate_graph(int R) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angle_dist(0, 2 * M_PI);
    std::uniform_real_distribution<> radius_dist(0, 1);
    std::uniform_int_distribution<> neighbors_dist(2, 6);

    for (int i = 0; i < VERTEX_NUM; ++i) {
        double theta = angle_dist(gen);
        double r = std::sqrt(radius_dist(gen)) * R;

        double x = r * std::cos(theta);
        double y = r * std::sin(theta);

        points.push_back({x, y, i});
    }

    for (size_t i = 0; i < points.size(); ++i) {
        std::vector<std::pair<double, int>> distances;

        for (size_t j = 0; j < points.size(); ++j) {
            if (i != j) {
                double distance = points[i].distance_to(points[j]);
                distances.emplace_back(distance, j);
            }
        }

        std::sort(distances.begin(), distances.end());

        int num_neighbors = neighbors_dist(gen);

        for (int k = 0; k < num_neighbors; ++k) {
            int neighbor_index = distances[k].second;
            double weight = distances[k].first;
            adjacency_list[i].emplace_back(neighbor_index, weight * 10);
            adjacency_list[neighbor_index].emplace_back(i, weight * 10);
        }
    }
}

std::pair<double, std::vector<int>> Graph::nearest_neighbor_path(int start_vertex) {
    std::vector<int> path;
    std::unordered_set<int> visited;
    int current = start_vertex;
    double total_weight = 0.0;
    path.push_back(current);
    visited.insert(current);

    while (visited.size() < VERTEX_NUM) {
        double min_distance = std::numeric_limits<double>::max();
        int next_vertex = -1;

        for (const auto& [neighbor, weight] : adjacency_list[current]) {
            if (visited.find(neighbor) == visited.end() && weight < min_distance) {
                min_distance = weight;
                next_vertex = neighbor;
            }
        }

        if (next_vertex == -1) {
            for (int i = 0; i < VERTEX_NUM; ++i) {
                if (visited.find(i) == visited.end()) {
                    next_vertex = i;
                    break;
                }
            }
        } else {
            total_weight += min_distance;
        }

        if (next_vertex == -1) {
            std::cerr << "No reachable vertices left.\n";
            break;
        }

        path.push_back(next_vertex);
        visited.insert(next_vertex);
        current = next_vertex;
    }

    for (const auto& [neighbor, weight] : adjacency_list[current]) {
        if (neighbor == start_vertex) {
            total_weight += weight;
            break;
        }
    }
    path.push_back(start_vertex);

    return {total_weight, path};
}

void Graph::print_graph() const {
    std::cout << "Graph adjacency list:\n";
    for (const auto& [vertex, neighbors] : adjacency_list) {
        std::cout << "Vertex " << vertex << " (" << points[vertex].x << ", " << points[vertex].y << ") -> ";
        for (const auto& [neighbor, weight] : neighbors) {
            std::cout << "Vertex " << neighbor
                      << " (" << points[neighbor].x << ", " << points[neighbor].y << "), Weight: "
                      << weight << "; ";
        }
        std::cout << "\n";
    }
}
