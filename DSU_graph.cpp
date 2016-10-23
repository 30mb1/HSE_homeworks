#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

class web {
private:
public:
    int weight;
    int from;
    int to;
    int priority;
    web(int a, int b, int c, int d)
            : from(a), to(b), weight(c), priority(d)
    {}
};

bool weight_s(web& a, web& b) {
    return a.weight < b.weight;
}

bool prior_s(web& a, web& b) {
    return a.priority > b.priority;
}

class Dsu {
private:
    mutable vector<int> parent;
    mutable vector<int> rank;
    mutable int sets_count = 0;

    void make_set(int v) {
        parent.push_back(v);
        rank.push_back(0);
        sets_count++;
    }

public:
    Dsu(int count) {
        for (int i = 0; i < count; ++i) {
            make_set(i);
        }
    }

    int find_set(int v) const {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    const bool are_joined(int a, int b) const {
        a = find_set(a);
        b = find_set(b);
        return a == b;
    }

    const bool join(int a, int b) const {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            sets_count--;
            if (rank[a] < rank[b])
                std::swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
            return true;
        }
        return false;
    }

    const int size() const {
        return parent.size();
    }

    const int disjoint_sets_count() const {
        return sets_count;
    }
};

size_t calculate_answer() {
    vector<web> graph;
    int N, M;
    cin >> N >> M;
    for (int ii = 0; ii < N; ++ii) {
        bool edge = false;
        if (ii < N - 1) edge = true;
        for (int xx = 0; xx < M; ++xx) {
            int a = 0, b = 0, c = 0, d = 0, cur;
            if (xx < M - 1) cin >> a >> b;
            if (edge) cin >> c >> d;
            cur = ii * M + xx;
            web chain(cur, (cur + 1) % (N * M), (-1) * b, a);
            web chain1(cur, (cur + M) % (N * M), (-1) * d, c);
            graph.push_back(chain);
            graph.push_back(chain1);
        }
    }

    Dsu scheme(N * M);
    int cost = 0;
    int count = 0;
    std::sort(graph.begin(), graph.end(), prior_s);
    for (int ii = 0; graph[ii].priority == 1 && ii < graph.size(); ++ii, ++count) {
        if (scheme.find_set(graph[ii].from) != scheme.find_set(graph[ii].to)) {
            cost = cost + graph[ii].weight;
            scheme.join(graph[ii].from, graph[ii].to);
        }
    }
    std::sort(graph.begin() + count, graph.end(), weight_s);
    for (int ii = count;ii < graph.size(); ++ii) {
        if (scheme.find_set(graph[ii].from) != scheme.find_set(graph[ii].to)) {
            cost = cost + graph[ii].weight;
            scheme.join(graph[ii].from, graph[ii].to);
        }
    }
    return (-1) * cost;
}