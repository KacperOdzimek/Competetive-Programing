#include <bits/stdc++.h>

constexpr int max_n = 30'000 + 1;
constexpr int log_n = 16;
int n, m; std::vector<int> G[max_n];

int depth[max_n];       // glebokosc
int up[max_n][log_n];   // 2^i przodek

void dfs(int v, int p) {
    depth[v] = depth[p] + 1;
    up[v][0] = p;

    for (int i = 1; i < log_n; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int u : G[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }

    // U idzie do gory zeby byc w tej
    // samej klasie glebokosci
    for (int i = log_n - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }

    if (u == v) return u;

    for (int i = log_n - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

int dst(int v, int u) {
    return depth[v] + depth[u] - 2 * depth[get_lca(v, u)];
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n; for (int i = 0; i < n - 1; i++) {
        int v, u; std::cin >> v >> u;
        G[v].push_back(u); G[u].push_back(v);
    }

    dfs(1, 0);

    int obecny, suma = 0;
    std::cin >> m >> obecny; m--;
    while (m--) {
        int x; std::cin >> x;
        suma += dst(obecny, x);
        obecny = x;
    }
    std::cout << suma;
}
