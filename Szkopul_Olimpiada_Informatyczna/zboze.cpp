#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr int max_n = 100'000;
constexpr int log_n = 17;

// Graf
std::vector<std::pair<int, int>> adj[max_n];    // Adjacency drzewa

// LCA

int up[max_n][log_n];   // Jump pointery
int dp[max_n];          // Glebkosc
ull cs[max_n];          // Koszt [0, v]

void lca_dfs(int v, int p, ull c) { 
    // Poczatkowe
    up[v][0] = p;
    dp[v]    = dp[p] + 1;
    cs[v]    = c;

    // Obliczanie up i cs
    for (int i = 1; i < log_n; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    
    // Wejdz do dzieci
    for (auto e : adj[v]) {
        if (e.first == p) continue;
        lca_dfs(e.first, v, c + e.second);
    }
}

int lca_get(int v, int u) {
    // V glebsze
    if (dp[v] < dp[u]) std::swap(v, u);

    // Jezeli da sie wykonac jakis skok, wykonaj
    for (int i = log_n - 1; i >= 0; i--) {
        if (dp[v] - (1 << i) >= dp[u]) v = up[v][i];
    }

    // Zakoncz tutaj
    if (v == u) return v;

    // Skacz tak dlugo az sie nie zejda
    for (int i = log_n - 1; i >= 0; i--) {
        if (up[v][i] == up[u][i]) continue;
        v = up[v][i]; u = up[u][i];
    }

    // Zejdz
    return up[v][0];
}

ull lca_dist(int v, int u) {
    if (v == u) return 0;
    return cs[v] + cs[u] - 2 * cs[lca_get(v, u)];
}

// Centroid

int                 P[max_n];   // Parent centroid; Domyslnie == -2
std::vector<int>    C[max_n];   // Centroidy dzieci
int subtree[max_n];             // Subtree drzewa; Temp

void oblicz_subtree(int v, int p) {
    subtree[v] = 1;
    for (auto& edge : adj[v]) {
        int u = edge.first;
        if (u == p || P[u] != -2) continue; // Nie zawracaj i nie wchodz do centroidow
        oblicz_subtree(u, v);
        subtree[v] += subtree[u];
    }
}

int szukaj_centroida(int v, int p, int total_size) {
    for (auto& edge : adj[v]) {
        int u = edge.first;
        if (u == p || P[u] != -2) continue;
        if (subtree[u] > total_size / 2) {  // Wchodz tylko do tych co moga spelnic warunek
            return szukaj_centroida(u, v, total_size);
        }
    }
    return v;   // Jak nie ma takiego dziecka zwroc siebie
}

int buduj_centroida(int v, int parent_centroid) {
    oblicz_subtree(v, -1);
    
    int centroid = szukaj_centroida(v, -1, subtree[v]);
    P[centroid] = parent_centroid;

    for (auto& edge : adj[centroid]) {
        int u = edge.first;
        if (P[u] != -2) continue;
        C[centroid].push_back(buduj_centroida(u, centroid));
    }

    return centroid;
}

// Logika zadania

bool Z[max_n];                // Czy wierzchołek jest zamkiem
int cnt[max_n];               // Liczba zamków w poddrzewie centroidu
ull sum_dist[max_n];          // Suma dist(x, c) dla zamków x w poddrzewie c
ull sum_dist_parent[max_n];   // Suma dist(x, P[c]) dla zamków x w poddrzewie c

ull last_ans = 0;

ull dodaj_zamek(int v) {
    if (Z[v]) return last_ans; // Zamek już istnieje
    Z[v] = true;

    ull zmiana = 0;
    int curr = v;
    int prev = -1;

    int old_cnt_prev = 0;
    ull old_sum_parent_prev = 0;

    while (curr != -1) {
        ull d = lca_dist(v, curr);

        // Liczba zamków w poddrzewie curr z wyłączeniem gałęzi prev
        int count_other = cnt[curr] - old_cnt_prev;
        ull sum_other = sum_dist[curr] - old_sum_parent_prev;

        // Dystans od v do wszystkich istniejących zamków przechodzących przez curr
        zmiana += (ull)count_other * d + sum_other;

        // Zapamiętaj wartości przed aktualizacją dla następnego kroku w górę
        old_cnt_prev = cnt[curr];
        old_sum_parent_prev = sum_dist_parent[curr];

        // Aktualizacja struktur dla curr
        cnt[curr]++; sum_dist[curr] += d;
        if (P[curr] != -1) {
            sum_dist_parent[curr] += lca_dist(v, P[curr]);
        }

        prev = curr;
        curr = P[curr];
    }

    // Ponieważ pytamy o skierowane pary (u, v) oraz (v, u), mnożymy przez 2
    last_ans += zmiana * 2; return last_ans;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    int n, k; std::cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int v, u, c; std::cin >> v >> u >> c; v--; u--;
        adj[v].push_back({u, c}); adj[u].push_back({v, c});
    }

    // Buduj LCA
    lca_dfs(0, 0, 0);

    // Buduj centroid
    std::fill(P, P + max_n, -2);
    buduj_centroida(0, -1);

    dodaj_zamek(0); for (int i = 0; i < k; i++) {
        int v; std::cin >> v; v--;
        std::cout << dodaj_zamek(v) << '\n';
    }
}
