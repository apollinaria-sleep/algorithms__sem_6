/*
Сложная задача: https://codeforces.com/contest/131/problem/D
Примерное время выполнения: 2 часа 
*/
#include <iostream>
#include <vector>
#include <queue>


void dfs(std::vector<std::vector<int>>& v, std::vector<int>& from, std::vector<bool>& used, int t, int& k, int& c) {
    if (k != -1) return;

    for (int j : v[t]) {
        if (!used[j]) {
            used[j] = true;
            from[j] = t;
            dfs(v, from, used, j, k, c);
            if (k != -1) return;
        } else if (j != from[t]) {
            k = t;
            c = j;
        }
    }
}


void SearchDistances(std::vector<std::vector<int>>& v) {
    std::vector<bool> used(v.size(), 0);
    std::vector<int> dist(v.size(), 3001);
    used[0] = true;

    std::vector<int> from(v.size(), -1);

    int c, k = -1;
    dfs(v, from, used, 0, k, c);
    std::vector<int> cycle;
    while (k != -1) {
        cycle.push_back(k);
        if (k == c) break;
        k = from[k];
    }

    std::queue<int> q;
    for (int i = 0; i < cycle.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            used[j] = false;
        }
        used[cycle[i]] = true;
        q.push(cycle[i]);
        dist[cycle[i]] = 0;
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            for (auto j : v[t]) {
                if (dist[j] > dist[t] + 1) {
                    dist[j] = dist[t] + 1;
                }
                if (!used[j]) {
                    q.push(j);
                    used[j] = true;
                }
            }
        }
    }

    for (int i = 0; i < dist.size(); i++) {
        std::cout << dist[i] << " ";
    }
}


int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> metro(n);
    for (int i = 0; i < n; i++) {
        int from, to;
        std::cin >> from >> to;
        metro[--from].push_back(--to);
        metro[to].push_back(from);
    }

    SearchDistances(metro);
    return 0;
}
