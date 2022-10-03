#include "graph.h"


// копирование
Graph::Graph(const Graph& other) = default;
Graph& Graph::operator=(const Graph& other) = default;

// move конструктор
Graph::Graph(Graph&& other) noexcept = default;

// move оператор присваивания
Graph &Graph::operator=(Graph &&) noexcept = default;

// деструктор
Graph::~Graph() {}

void Graph::AddVertex(int v_num) {
    this->vertex.push_back(v_num);
    int some_size = 15;
    std::vector<Edge> for_new_v;
    for_new_v.reserve(some_size);
    this->edge.push_back(for_new_v);
}

void Graph::AddVertex(int v_num, std::vector<int>& edges) {
    this->vertex.push_back(v_num);
    std::vector<Edge> for_new_v(edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        Edge new_e(v_num, edges[i]);
        for_new_v[i] = new_e;

        int ind = this->findVertex(edges[i]);
        Edge new_o(edges[i], v_num);
        this->edge[ind].push_back(new_o);
    }
    this->edge.push_back(for_new_v);
}

void Graph::AddVertex(int v_num, const std::vector<int>& edges, const std::vector<int>& weights) {
    this->vertex.push_back(v_num);
    std::vector<Edge> for_new_v(edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        Edge new_e(v_num, edges[i], weights[i]);
        for_new_v[i] = new_e;

        int ind = this->findVertex(edges[i]);
        Edge new_o(edges[i], v_num, weights[i]);
        this->edge[ind].push_back(new_o);
    }
    this->edge.push_back(for_new_v);
}

void Graph::RemoveVertex(int v_num) {
    int ind = findVertex(v_num);
    this->edge[ind].swap(this->edge[this->edge.size() - 1]);
    for (auto& edge : this->edge[this->edge.size() - 1]) {
        int ind_other = findVertex(edge.other_vertex);
        int ind_e = findEdge(ind_other, v_num);
        if (ind_e != -1) {
            std::swap(this->edge[ind_other][ind_e], this->edge[ind_other][this->edge[ind_other].size() - 1]);
            this->edge[ind_other].pop_back();
        }
    }
    this->edge.pop_back();

    std::swap(this->vertex[ind], this->vertex[this->vertex.size() - 1]);
    this->vertex.pop_back();
}

void Graph::AddEdge(Edge new_edge) {
    int ind_v1 = findVertex(new_edge.from_vertex);
    int ind_v2 = findVertex(new_edge.other_vertex);

    Edge new_e1(new_edge.from_vertex, new_edge.other_vertex, new_edge.weight);
    this->edge[ind_v1].push_back(new_e1);

    Edge new_e2(new_edge.other_vertex, new_edge.from_vertex, new_edge.weight);
    this->edge[ind_v2].push_back(new_e2);
}

void Graph::AddEdge(int from_v, int to_v) {
    int ind_v1 = findVertex(from_v);
    int ind_v2 = findVertex(to_v);

    Edge new_e1(from_v, to_v);
    this->edge[ind_v1].push_back(new_e1);

    Edge new_e2(to_v, from_v);
    this->edge[ind_v2].push_back(new_e2);
}

void Graph::AddEdge(int from_v, int to_v, int weight) {
    int ind_v1 = findVertex(from_v);
    int ind_v2 = findVertex(to_v);

    Edge new_e1(from_v, to_v, weight);
    this->edge[ind_v1].push_back(new_e1);

    Edge new_e2(to_v, from_v, weight);
    this->edge[ind_v2].push_back(new_e2);
}

void Graph::RemoveEdge(int from_v, int to_v) {
    int ind_v1 = findVertex(from_v);
    int ind_v2 = findVertex(to_v);

    int ind_e1 = findEdge(ind_v1, to_v);
    std::swap(this->edge[ind_v1][ind_e1], this->edge[ind_v1][this->edge[ind_v1].size() - 1]);
    this->edge[ind_v1].pop_back();

    int ind_e2 = findEdge(ind_v2, from_v);
    std::swap(this->edge[ind_v2][ind_e2], this->edge[ind_v2][this->edge[ind_v2].size() - 1]);
    this->edge[ind_v2].pop_back();
}

std::vector<int> Graph::VertexNeighbours(int v_num) {
    int ind = findVertex(v_num);

    size_t i = 0;
    std::vector<int> neighbours(this->edge[ind].size());
    for (auto& edge : this->edge[ind]) {
        neighbours[i] = edge.other_vertex;
        i++;
    }

    return neighbours;
}

int Graph::Size() {
    return this->vertex.size();
}

void Graph::Union(const Graph &other, int this_v, int other_v) {
    for (size_t i = 0; i < other.vertex.size(); i++) {
        if (this->findVertex(other.vertex[i]) == -1) {
            this->AddVertex(other.vertex[i]);
            for (size_t j = 0; j < other.edge[i].size(); j++) {
                if (this->findVertex(other.edge[i][j].other_vertex) != -1) {
                    this->AddEdge(other.edge[i][j]);
                }
            }
        }
    }
    this->AddEdge(this_v, other_v);
}

void Graph::Union(const Graph &other, Edge some_edge) {
    for (size_t i = 0; i < other.vertex.size(); i++) {
        if (this->findVertex(other.vertex[i]) == -1) {
            this->AddVertex(other.vertex[i]);
            for (size_t j = 0; j < other.edge[i].size(); j++) {
                if (this->findVertex(other.edge[i][j].other_vertex) != -1) {
                    this->AddEdge(other.edge[i][j]);
                }
            }
        }
    }
    this->AddEdge(some_edge);
}

////    ShowGraph();
//
std::istream& Graph::ReadFrom(std::istream& in) {
    Graph new_graph;

    std::string str_title;
    in >> str_title;
    if (str_title != "vertex:") {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    int size;
    in >> size;
    this->vertex.reserve(size);
    for (size_t i = 0; i < size; i++) {
        int v_num;
        in >> v_num;
        if (v_num < 0) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        new_graph.AddVertex(v_num);
    }

    bool weight = false;
    std::string str_weight;
    in >> str_weight;
    if (str_weight == "Weight") {
        weight = true;
    } else if (str_weight != "NotWeight") {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    in >> str_title;
    if (str_title != "edge:") {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    int size_e;
    in >> size_e;
    for (size_t j = 0; j < size_e; j++) {
        if (weight) {
            int v_from, v_to, weight;
            in >> v_from >> v_to >> weight;
            if (v_from < 0 || v_to < 0 || weight < 1) {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            new_graph.AddEdge(v_from, v_to, weight);
        } else {
            int v_from, v_to;
            in >> v_from >> v_to;
            if (v_from < 0 || v_to < 0) {
                in.setstate(std::ios_base::failbit);
                return in;
            }

            new_graph.AddEdge(v_from, v_to);
        }
    }

    *this = new_graph;
    return in;
}

std::ostream& Graph::WriteTo(std::ostream& out) {
    std::sort(this->vertex.begin(), this->vertex.end());
    out << "Количество вершин: " << this->vertex.size() << '\n';
    for (size_t i = 0; i < this->vertex.size(); i++) {
        out << this->vertex[i] << ' ';
    }
    out << '\n';

    out << "Ребра графа\n";
    for (size_t i = 0; i < this->vertex.size(); i++) {
        for (size_t j = 0; j < this->edge[i].size(); j++) {
            if (this->edge[i][j].from_vertex < this->edge[i][j].other_vertex) {
                out << this->edge[i][j].from_vertex << ' ' << this->edge[i][j].other_vertex << ' ' << this->edge[i][j].weight << '\n';
            }
        }
    }

    return out;
}

int Graph::findVertex(int v_num) const {
    for (size_t i = 0; i < this->vertex.size(); i++) {
        if (vertex[i] == v_num) {
            return i;
        }
    }
    return -1;
}

int Graph::findEdge(int from_ind, int to_num) const {
    for (int i = 0; i < this->edge[from_ind].size(); i++) {
        if (this->edge[from_ind][i].other_vertex == to_num) {
            return i;
        }
    }
    return -1;
}

std::istream& operator>>(std::istream& in, Graph& gr) {
    return gr.ReadFrom(in);
}

std::ostream& operator<<(std::ostream& out, Graph& gr) {
    return gr.WriteTo(out);
}