#ifndef GRAPHVISUALIZER_H
#define GRAPHVISUALIZER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QApplication>
#include <QMainWindow>
#include "Graph.h"

class GraphVisualizer : public QMainWindow {
    Q_OBJECT

public:
    GraphVisualizer(Graph& graph, QWidget* parent = nullptr);
    void visualize_path(const std::vector<int>& path, double total_weight);

private:
    std::vector<Point>& points_ref;
    std::unordered_map<int, std::vector<std::pair<int, double>>>& adjacency_list_ref;

    QGraphicsScene* scene;
    QGraphicsView* view;
    Graph& graph;
    void visualize_graph();
    void scale_graph(double scale_factor);
};

#endif // GRAPHVISUALIZER_H
