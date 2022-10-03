#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <iosfwd>
#include <iostream>
#include <exception>
#include <string>
#include <string_view>
#include <algorithm>


class Graph {
private: class Edge;
public:
    // конструкторы
    Graph() = default;

    // копирование
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);

    // move конструктор
    Graph(Graph&& other) noexcept;

    // move оператор присваивания
    Graph& operator=(Graph&& other) noexcept;

    // деструктор
    ~Graph();

    // добавление вершины
    void AddVertex(int v_num);
    void AddVertex(int v_num, std::vector<int> &edges);
    void AddVertex(int v_num, const std::vector<int>&edges, const std::vector<int> &weights);

    void RemoveVertex(int v_num);

    void AddEdge(Edge new_edge);
    void AddEdge(int from_v, int to_v);
    void AddEdge(int from_v, int to_v, int weight);
    void RemoveEdge(int from_v, int to_v);
    std::vector<int> VertexNeighbours(int v_num);
    Graph FindMST(); // поиск минимального остовного дерева, вернет его в виде графа
    int Size();
//
    void Union(const Graph& other, Edge some_edge);
    void Union(const Graph &other, int from_v, int to_v);
////    ShowGraph();
//
    std::istream& ReadFrom(std::istream&);
    std::ostream& WriteTo(std::ostream&);

private:
    // класс ошибок
    class Exceptions : public std::exception {
    public:
        explicit Exceptions(std::string_view error) : m_error{error} {}
        const char* what() const noexcept override {
            return m_error.c_str();//;
        }
    private:
        std::string m_error;
    };

    class Edge {
    public:
        int from_vertex;
        int other_vertex;
        int weight = 1;

        Edge() = default;
        Edge(int from_v, int to_v) : from_vertex(from_v), other_vertex(to_v) {}
        Edge(int from_v, int to_v, int weight) : from_vertex(from_v), other_vertex(to_v), weight(weight) {}
    };

    std::vector<int> vertex;
    std::vector<std::vector<Edge>> edge;

    int findEdge(int from_ind, int to_num) const;
    int findVertex(int v_num) const;
};

std::istream& operator>>(std::istream&, Graph&);
std::ostream& operator<<(std::ostream&, Graph&);

#endif