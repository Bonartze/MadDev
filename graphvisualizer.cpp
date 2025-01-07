#include "GraphVisualizer.h"

GraphVisualizer::GraphVisualizer(Graph& graph, QWidget* parent)
    : QMainWindow(parent), graph(graph),  points_ref(graph.get_points()),
    adjacency_list_ref(graph.get_adjacency_list()) {

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->scale(0.8, 0.8);

    setCentralWidget(view);
    resize(800, 800);

    visualize_graph();
}

void GraphVisualizer::visualize_graph() {
    const int POINT_RADIUS = 10;
    const int OFFSET = 200;
    const double SCALE = 5.0;

    scale_graph(SCALE);

    for (const auto& [vertex, neighbors] : adjacency_list_ref) {

        double x1 = points_ref[vertex].x + OFFSET;
        double y1 = points_ref[vertex].y + OFFSET;

        for (const auto& [neighbor, weight] : neighbors) {
            double x2 = points_ref[neighbor].x + OFFSET;
            double y2 = points_ref[neighbor].y + OFFSET;
            scene->addLine(x1, y1, x2, y2, QPen(Qt::red));
        }
    }

    for (const auto& point : points_ref) {
        double x = point.x + OFFSET - POINT_RADIUS;
        double y = point.y + OFFSET - POINT_RADIUS;

        scene->addEllipse(x, y, 2 * POINT_RADIUS, 2 * POINT_RADIUS, QPen(Qt::black), QBrush(Qt::blue));
        QGraphicsTextItem* text = scene->addText(QString::number(point.id), QFont("Arial", 10));
        text->setDefaultTextColor(Qt::red);
        text->setPos(x, y);
    }
}

void GraphVisualizer::scale_graph(double scale_factor) {
    for (auto& point : points_ref) {
        point.x *= scale_factor;
        point.y *= scale_factor;
    }
}

void GraphVisualizer::visualize_path(const std::vector<int>& path, double total_weight) {
    const int OFFSET = 200;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int current = path[i];
        int next = path[i + 1];

        double x1 = points_ref[current].x + OFFSET;
        double y1 = points_ref[current].y + OFFSET;
        double x2 = points_ref[next].x + OFFSET;
        double y2 = points_ref[next].y + OFFSET;

        scene->addLine(x1, y1, x2, y2, QPen(Qt::green, 2));

        double mid_x = (x1 + x2) / 2.0;
        double mid_y = (y1 + y2) / 2.0;

        QGraphicsTextItem* text = scene->addText(QString::number(adjacency_list_ref[current][0].second, 'f', 2), QFont("Arial", 8));
        text->setDefaultTextColor(Qt::blue);
        text->setPos(mid_x, mid_y);
    }

    QString weight_text = QString("Total Path Weight: %1").arg(total_weight, 0, 'f', 2);
    QGraphicsTextItem* weight_item = scene->addText(weight_text, QFont("Arial", 12, QFont::Bold));
    weight_item->setDefaultTextColor(Qt::white);
    weight_item->setPos(400, 780);
}
