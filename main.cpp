#include <iostream>
#include <vector>
#include <stack>
#include <exception>
#include <stdexcept>

using namespace std;

enum Color
{
    WHITE,
    GREY,
    BLACK,
};

class Graph
{
public:
    Graph(vector < vector <int> > _edges): edges(_edges), colors(_edges.size(), WHITE)
    { }

    void dfs(int start)
    {
        if (start < 0 || start >= (int)edges.size()) {
            throw runtime_error("DFS vertex index is out of bounds");
        }

        if (colors[start] == BLACK) {
            // Мы здесь уже были
            return;
        } else if (colors[start] == GREY) {
            // Всё очень плохо, и в графе есть цикл
            throw runtime_error("DFS: graph contains loops");
        }

        // А так всё хорошо
        colors[start] = GREY; // Помечаем, что мы сюда вошли, но отсюда ещё не вышли
        for (const auto &edge_to : edges[start]) {
            dfs(edge_to);
        }
        colors[start] = BLACK; // Выходим отсюда
        exits.push_back(start); // И отмечаем это
    }

    vector <int> topological_sort()
    {
        for (int i = 0; i < (int)edges.size(); ++i) {
            dfs(i);
        }
        return exits;
    }

    void reset_colors()
    {
        for (auto &i : colors) {
            i = WHITE;
        }
        exits.resize(0);
    }

    const vector < vector <int> > &get_edges()  const
    {
        return edges;
    }

protected:
    // Граф в виде списка смежности. Индексы 0..n-1
    vector < vector <int> > edges;

    // Цвета вершин. Индексы: 0..n-1
    vector <int> colors;

    // Заполняется методом сортировки
    vector <int> exits;
};

// Вводит граф в виде матрицы смежности
Graph input_graph(istream &in)
{
    int n;
    in >> n;
    vector < vector <int> > edges(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int is_edge;
            in >> is_edge;
            if (is_edge) {
                edges[i].push_back(j);
            }
        }
    }
    return Graph(edges);
}

void output_graph(const Graph &graph, ostream &out)
{
    vector < vector <int> > edges = graph.get_edges();
    for (const auto &i : edges) {
        int prev = 0;
        for (const auto &j : i) {
            while (prev < j) {
                ++prev;
                out << 0 << ' ';
            }
            ++prev;
            out << 1 << ' ';
        }
        while (prev < (int)edges.size()) {
            ++prev;
            out << 0 << ' ';
        }
        out << '\n';
    }
}

int main()
{
    Graph graph = input_graph(cin);
    auto sorted = graph.topological_sort();
    for (const auto &i : sorted) {
        cout << i << ' ';
    }
    cout << endl;
}
