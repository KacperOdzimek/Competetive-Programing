#include <bits/stdc++.h>
constexpr int max_n = 100000;

int n, m;
std::vector<int> G[max_n];


int V = -1;         // Unroll till
std::vector<int> P; // Path


int T[max_n];

// 0 - discover
// 1 - unroll and store
// 2 - unroll
int dfs(int v, int t) {
    if (T[v] != 0) {
        // Begin loop unrolling
        if (t - T[v] >= 3) {
            V = v; P.push_back(v);
            return 1;
        }
        // Just dont loop
        else if (T[v] <= t) return 0;
    }
    T[v] = t; for (int u : G[v]) {
        int w = dfs(u, t + 1);
        if (w == 1) {
            P.push_back(v);
            if (v == V) return 2;
            return 1;
        }
        if (w == 2) return 2;
    }
    return 0;
}

int main() {
    std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        G[x0].push_back(x1); G[x1].push_back(x0);
    }

    bool found = false;
    for (int v = 0; v < n; v++) {
        if (T[v] != 0) continue;
        int w = dfs(v, 1);
        if (w != 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }

    std::cout << P.size() << '\n';
    for (int v : P) std::cout << v + 1 << ' ';
}