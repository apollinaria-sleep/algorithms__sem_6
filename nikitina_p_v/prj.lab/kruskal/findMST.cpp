#include "graph.h"


Graph Graph::FindMST() { // поиск минимального остовного дерева, вернет его в виде графа
    // сначала сделаем общий массив ребер, чтобы иметь возможность его отсортировать по весу ребер
    int edge_cnt = 0;
    for (size_t i = 0; i < this->edge.size(); i++) {
        edge_cnt += this->edge[i].size();
    }
    edge_cnt /= 2;

    std::vector<Edge> all_edges(edge_cnt);
    int k = 0;
    std::sort(this->vertex.begin(), this->vertex.end());
    for (size_t i = 0; i < this->vertex.size(); i++) {
        for (size_t j = 0; j < this->edge[i].size(); j++) {
            if (this->vertex[i] < this->edge[i][j].other_vertex) {
                this->edge[i][j].from_vertex = this->vertex[i];
                all_edges[k++] = this->edge[i][j];
            }
        }
    }

    // теперь отсортируем полученный массив по весам ребер
    std::sort(all_edges.begin(), all_edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // далее выполняем алгоритм
    std::vector<Graph> graphs;

    // для каждой вершины создаем отдельный граф
    for (auto& v : this->vertex) {
        Graph new_graph;
        new_graph.AddVertex(v);
        graphs.push_back(new_graph);
    }

    // по возрастанию веса ребер начинаем объединять графы
    Graph result;
    for (auto& edge : all_edges) {
        int ind1;
        int ind2;
        for (size_t i = 0; i < graphs.size(); i++) {
            if (graphs[i].findVertex(edge.from_vertex) != -1) {
                ind1 = i;
            }
            if (graphs[i].findVertex(edge.other_vertex) != -1) {
                ind2 = i;
            }
        }

        if (ind1 != ind2) {
            if (ind1 < ind2) {
                graphs[ind1].Union(graphs[ind2], edge);
                result = graphs[ind1];
                std::swap(graphs[ind2], graphs[graphs.size() - 1]);
            } else {
                graphs[ind2].Union(graphs[ind1], edge);
                result = graphs[ind2];
                std::swap(graphs[ind1], graphs[graphs.size() - 1]);
            }
            graphs.pop_back();

        }
    }

    return result;
}

