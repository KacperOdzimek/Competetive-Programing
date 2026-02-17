#include <iostream>
#include <vector>
#include <cstring>

// 1) wykluczenie wiercholka moze prowadzic do rozspojnienia grafu
//      (jest punktem artykulacyjnym)
// 2) wtedy wynik dla wierchołka to
//      bazowe spotkania - E (n rozmiar spojnych) (n * (n - 1))
// 3) musimy znac wiec rozmiary spojnych

using ll = long long;

constexpr int max_n = 100'000;
constexpr int max_m = 500'000;

ll n, m;

std::vector<int> G[max_n]; // graf oryginalny

std::vector<int> D[max_n]; // drzewo rozpinajace
std::vector<int> W[max_n]; // drzewo krawedzi wtornych

int P[max_n]; // ojciec w D
ll  R[max_n]; // rozmiar mojego podrzewa (ze mna)!

int  low  [max_n];
int  depth[max_n];
bool ART[max_n];

bool vis[max_n];

// drzewo rozpinajace dfs
void dfs_rozp(int v, int p) {
    vis[v] = true;
    P[v] = p;

    for (auto u : G[v]) {
        if (u == p) continue;

        if (vis[u]) W[v].push_back(u);
        else {
            D[v].push_back(u);
            D[u].push_back(v);
            dfs_rozp(u, v);
        }
    }
}

// low i depth
void calculate_low (int v) {
    vis[v] = true;
    low[v] = depth[v];

    // na wektorze drzewo trzymamy liste sasiedztwa
    // drzewa rozpinajacego DFS
    for (int u : D[v]) {
        if(!vis[u]) {
            depth[u] = depth[v] + 1;
            calculate_low(u);
            low[v] = std::min(low[v], low[u]);
        }
    }

    // na wektorze kraw_wsteczne[x] trzymamy
    // krawedzie wsteczne wychodace z x
    for(int u : W[v]) low[v] = std::min(low[v], depth[u]);
}

// rozmiary poddrzew
void dfs_rozm(int v) {
    vis[v] = true;
    ll rozm = 0;

    for (int u : D[v]) {
        if (vis[u]) continue;
        dfs_rozm(u);
        rozm += R[u];
    }

    R[v] = rozm + 1;
}

void mark_articulation() {
    for (int v = 1; v < n; v++) {
        for (auto u : D[v]) {
            if (u == P[v]) continue;
            ART[v] |= (low[u] >= depth[v]);
        }
    }

    if (D[0].size() > 1) ART[0] = 1;
}

ll bazowe;
ll dla_nie_art;

inline ll answer(int v) {
    if (!ART[v]) return dla_nie_art;
    
    ll suma = 0;
    ll pozostale = n - 1;

    for (int u : D[v]) {
        if (u == P[v]) continue;

        if (low[u] >= depth[v]) {
            suma += R[u] * (R[u] - 1);
            pozostale -= R[u];
        }
    }

    suma += pozostale * (pozostale - 1);
    return (bazowe - suma);
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; std::cin >> a >> b; a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    bazowe      = n * (n - 1);
    dla_nie_art = bazowe - ((n - 1) * (n - 2));

    memset(vis, 0, sizeof(vis));
    dfs_rozp(0, -1);

    memset(vis, 0, sizeof(vis));
    calculate_low(0);

    memset(vis, 0, sizeof(vis));
    dfs_rozm(0);

    mark_articulation();

    for (int v = 0; v < n; v++) 
        std::cout << answer(v) << '\n';
}
