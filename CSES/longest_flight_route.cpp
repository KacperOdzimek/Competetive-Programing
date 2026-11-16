#include <bits/stdc++.h>
constexpr int max_n = 100000;
std::vector<int> G[max_n];
int INDEG[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, m; std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; 
        x0--; x1--; G[x0].push_back(x1); INDEG[x1]++;
    }

    std::vector<int> TOPO; for (int i = 0; i < n; i++) {
        if (INDEG[i] == 0) TOPO.push_back(i);
    }

    for (int i = 0; i < TOPO.size(); i++) {
        int v = TOPO[i]; for (int u : G[v]) {
            INDEG[u]--; if (!INDEG[u]) TOPO.push_back(u);
        }
    }

    std::vector<int> DIST(n, -1);
    std::vector<int> PREV(n, -1);
    DIST[0] = 1;

    for (int i = 0; i < n; i++) {
        int v = TOPO[i]; 
        if (DIST[v] == -1) continue;
        for (int u : G[v]) {
            if (DIST[u] >= DIST[v] + 1) continue;
            DIST[u] = DIST[v] + 1;
            PREV[u] = v;
        }
    }

    if (DIST[n - 1] == -1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    std::cout << DIST[n - 1] << '\n';
    std::stack<int> Q; Q.push(n - 1);
    while (PREV[Q.top()] != -1) Q.push(PREV[Q.top()]);
    while (Q.size()) {std::cout << Q.top() + 1 << ' '; Q.pop(); }
}
