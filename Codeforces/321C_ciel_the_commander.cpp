#include <bits/stdc++.h>

// Drzewo

constexpr int max_n = 100000;
int n; std::vector<int> T[max_n];

// Centroidy

int              S[max_n]; // Subtree
std::vector<int> C[max_n]; // Drzewo centroidow (tylko dzieci)
bool             P[max_n]; // Czy wyjete z grafu

void cent_size_dfs(int v, int p) {
    S[v] = 1; for (int u : T[v]) {
        if (u == p) continue;
        if (P[u])   continue;
        cent_size_dfs(u, v);
        S[v] += S[u];
    }
}

int cent_find_dfs(int v, int p, int sz) {
    for (int u : T[v]) {
        if (u == p) continue;
        if (P[u])   continue;
        if (2 * S[u] > sz) return cent_find_dfs(u, v, sz);
    } return v;
}

int cent_build(int v) {
    cent_size_dfs(v, -1);
    int c = cent_find_dfs(v, -1, S[v]);
    P[c] = true; for (int u : T[c]) {
        if (P[u]) continue;
        C[c].push_back(cent_build(u));
    } 
    return c;
}

// Zadanie

char L[max_n];  // Nadana litera

bool rang_dfs(int v) {
    bool scc = ++L[v] <= 'Z';
    for (int u : C[v]) {
        L[u] = L[v];
        scc &= rang_dfs(u);
    }
    return scc;
}

int main() {
    // Laduj
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n; for (int i = 0; i < n - 1; i++) {
        int v, u; std::cin >> v >> u; v--; u--;
        T[v].push_back(u); T[u].push_back(v);
    }

    // Buduj centroid
    int mc = cent_build(0);

    // Nadaj rangi
    L[mc] = 'A' - 1; 
    bool scc = rang_dfs(mc);

    // Odpowiedz
    if (scc) for (int i = 0; i < n; i++) std::cout << L[i] << ' ';
    else std::cout << "Impossible!";
}
