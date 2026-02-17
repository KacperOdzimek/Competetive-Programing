#include <iostream>
#include <vector>

constexpr int max_n = 20;

int n, m;

std::vector<int> G[max_n];

int              P[max_n];
std::vector<int> D[max_n];
std::vector<int> W[max_n];

int  low  [max_n];
int  depth[max_n];
bool vis  [max_n];

void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b; std::cin >> a >> b; a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
}

void clear_vis() {
    for (int i = 0; i < max_n; i++) vis[i] = false;
}

// drzewo rozpinajace dfs
void dfs(int v, int p) {
    vis[v] = true;
    P[v] = p;

    for (auto u : G[v]) {
        if (u == p) continue;

        if (vis[u]) W[v].push_back(u);
        else {
            D[v].push_back(u);
            D[u].push_back(v);
            dfs(u, v);
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

void mosty() {
    for (int v = 1; v < n; v++) {
        if (low[v] == depth[v]) std::cout << (v + 1) << ' ' << (P[v] + 1) << '\n';
    }
}

int main() {
    load();

    clear_vis();
    dfs(0, -1);

    clear_vis();
    calculate_low(0);

    mosty();
}

/*
10 11
1 3
1 4
5 4
5 8
9 8
4 9
3 7
2 3
2 6
6 3
10 6
*/
