#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using std::vector;
using std::cin;
using std::cout;

int n;
long INF = std::numeric_limits<long>::max();

long max_flow(int s, int t, std::vector<std::vector<long>> &cap, std::vector<std::vector<int>> &graph) {
    std::vector<std::vector<long>> flow(n, std::vector<long>(n, 0));
    for (;;) {
        std::queue<int> queue;
        queue.push(s);
        vector<int> from (n, -1);
        from[s] = s;
        while (!queue.empty()) {
            int cur = queue.front();
            queue.pop();
            if (cur == t) {
                break;
            }
            for (int ii : graph[cur]) {
                if (from[ii] == -1 &&
                    cap[cur][ii] - flow[cur][ii] > 0) {
                    queue.push(ii);
                    from[ii] = cur;
                }
            }
        }
        if (from[t] == -1) break;
        long cap_min = INF;
        for (int cur = t; cur != s;) {
            int pred = from[cur];
            cap_min = std::min(cap_min, cap[pred][cur] - flow[pred][cur]);
            cur = pred;
        }
        for (int cur = t; cur != s;) {
            int pred = from[cur];
            flow[pred][cur] += cap_min;
            flow[cur][pred] -= cap_min;
            cur = pred;
        }
    }

    long f_flow = 0;
    for (int ii : graph[s]) {
        if (cap[s][ii]) {
            f_flow += flow[s][ii];
        }
    }
    return f_flow;
}

int main() {
    int nn, mm;
    std::cin >> nn >> mm;
    n = nn;
    std::vector<std::vector<int>> graph(nn);
    std::vector<std::vector<long>> cap(nn, std::vector<long>(nn, 0));
    for (int ii = 0; ii < mm; ++ii) {
        int from, to;
        long capacity;
        std::cin >> from >> to >> capacity;
        from--;
        to--;
        graph[from].push_back(to);
        graph[to].push_back(from);
        cap[from][to] = capacity;
    }
    long answer = max_flow(0, nn - 1, cap, graph);
    cout << answer;
}
