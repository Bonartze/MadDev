#include "Graph.h"
#include "graphvisualizer.h"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Graph graph;
    int R = 100;
    graph.generate_graph(R);

    bool ok;
    int start_vertex = QInputDialog::getInt(
        nullptr,
        "Choose Starting Vertex",
        QString("Enter the starting vertex (0 to %1):").arg(VERTEX_NUM - 1),
        0,
        0,          // Минимальное значение
        VERTEX_NUM - 1, // Максимальное значение
        1,          // Шаг ввода
        &ok         // Указатель на флаг подтверждения
        );

    if (!ok) {
        QMessageBox::information(nullptr, "Canceled", "You canceled the operation. Exiting...");
        return 0; // Пользователь отменил ввод, завершаем программу
    }

    // Находим путь и общий вес, начиная с выбранной вершины
    auto [total_weight, path] = graph.nearest_neighbor_path(start_vertex);

    // Визуализация графа
    GraphVisualizer visualizer(graph);
    visualizer.visualize_path(path, total_weight);
    visualizer.show();

    return app.exec();
}
