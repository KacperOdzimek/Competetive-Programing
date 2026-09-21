/*
    1) Polaczenie w ramach DSU nic nie zmienia
    2) Gdy laczymy dwa wiercholki, nowa najdluzsza 
        to polaczenie 2 z starych wiercholkow najdluzszych sciezek obu drzew
    C) O(n log2 n)
*/

#include <bits/stdc++.h>

constexpr int max_n = 2 * 100000;
int n, m; int maxans = 0;
std::vector<int> G[max_n];

int dfs(int v, int p) {
    int child = 0;
    for (int u : G[v]) {
        if (u == p) continue;
        child = std::max(child, dfs(u, v));
    }
    return child + 1;
}

int dfs_first(int v) {
    int child1 = 0;
    int child2 = 0;
    for (int u : G[v]) {
        int child = dfs(u, v);
        if (child > child1) {
            child2 = child1;
            child1 = child;
        }
        else if (child > child2) {
            child2 = child;
        }
    }
    return child1 + child2 + 1;
}

void dodaj_krawedz(int v, int u) {
    G[v].push_back(u); G[u].push_back(v);
    maxans = std::max(maxans, dfs_first(v));
    std::cout << maxans << '\n';
}

void zaszyfrowane() {
    // Pierwsza para normalnie
    int v, u; std::cin >> v >> u; v--; u--;
    dodaj_krawedz(v, u);
    
    // Reszta zaszyfrowana
    for (int i = 0; i < m - 1; i++) {
        int v, u; std::cin >> v >> u;
        v = v ^ maxans; u = u ^ maxans;
        v--; u--; dodaj_krawedz(v, u);
    }
}

void nieszyfrowane() {
    for (int i = 0; i < m; i++) {
        int v, u; std::cin >> v >> u; v--; u--;
        dodaj_krawedz(v, u);
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int t; std::cin >> n >> m >> t;
    if (t) zaszyfrowane();
    else   nieszyfrowane();
}
