#include <bits/stdc++.h>
constexpr int max_n = 100000;
constexpr int log_n = 17;
constexpr int inf_i = INT32_MAX - max_n - 1;

// Drzewo
int n; std::vector<int> T[max_n];

// LCA
int     D[max_n];           // Depth
int     U[max_n][log_n];    // Jump Pointers

// p poczatkowo rowne v
void lca_build(int v, int p) {
    D[v] = D[p] + 1; U[v][0] = p; 
    for (int i = 1; i < log_n; i++) {
        U[v][i] = U[U[v][i - 1]][i - 1];
    }
    
    for (int u : T[v]) {
        if (u == p) continue;
        lca_build(u, v);
    }
}

int lca_get(int v, int u) {
    if (D[v] < D[u]) std::swap(v, u);
    for (int i = log_n - 1; i >= 0; i--) {
        if (D[v] - (1 << i) >= D[u]) v = U[v][i];
    }

    if (v == u) return v;

    for (int i = log_n - 1; i >= 0; i--) {
        if (U[v][i] == U[u][i]) continue;
        v = U[v][i]; u = U[u][i];
    }

    return U[v][0];
}

int lca_dist(int v, int u) {
    if (v == u) return 0;
    return D[v] + D[u] - 2 * D[lca_get(v, u)];
}

// Centroidy
int     P[max_n]; // Parent centroidy
int     S[max_n]; // Subtree [Temp]
bool    Z[max_n]; // Czy zabrano wiercholek [Temp]

void cent_size_dfs(int v, int p) {
    S[v] = 1; for (int u : T[v]) {
        if (u == p) continue;
        if (Z[u])   continue;
        cent_size_dfs(u, v);
        S[v] += S[u];
    }
}

int cent_find_dfs(int v, int p, int sz) {
    for (int u : T[v]) {
        if (u == p) continue;
        if (Z[u])   continue;
        if (2 * S[u] > sz) return cent_find_dfs(u, v, sz);
    }
    return v;
}

int cent_build(int v) {
    cent_size_dfs(v, -1);
    int c = cent_find_dfs(v, -1, S[v]);
    P[c] = -1; Z[c] = true; 
    for (int u : T[c]) {
        if (Z[u]) continue;
        int cc = cent_build(u);
        P[cc] = c;
    }
    return c;
}

// Zadanie

int m;
int L[max_n]; // Odleglosc do najbliszego czerwonego

// Mark node red : (log n)^2
void paint_red(int v) {
    int vi = v; while (vi != -1) {
        L[vi] = std::min(L[vi], lca_dist(vi, v));
        vi = P[vi];
    }
}

// Shortest dist to red node : (log n)^2
int query_red(int v) {
    int ans = inf_i; int vi = v; while (vi != -1) {
        ans = std::min(ans, L[vi] + lca_dist(vi, v));
        vi = P[vi];
    } return ans;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; for (int i = 0; i < n - 1; i++) {
        int v, u; std::cin >> v >> u; v--; u--;
        T[v].push_back(u); T[u].push_back(v);
    }

    lca_build(0, 0);
    cent_build(0);

    std::fill(L, L + max_n, inf_i);
    paint_red(0); while (m--) {
        int t, v; std::cin >> t >> v; v--;
        if (t == 1) paint_red(v);
        if (t == 2) std::cout << query_red(v) << '\n';
    }
}
