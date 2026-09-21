#include <bits/stdc++.h>

constexpr int max_n = 2 * 100000;
constexpr int LOG = 18;                 // 2^18 > 2*10^5
int n, m; int maxans = 0;

// DSU
int DSU[max_n];
int sz[max_n];
int E1[max_n];  // Jeden koniec srednicy
int E2[max_n];  // Drugi koniec srednicy

// LCA
int up[LOG][max_n];
int dep[max_n];
std::vector<int> adj[max_n];

int rep(int v) {
    int r = v;
    while (r != DSU[r]) r = DSU[r];
    while (v != r) { int nx = DSU[v]; DSU[v] = r; v = nx; }  // kompresja sciezek
    return r;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) std::swap(a, b);
    int diff = dep[a] - dep[b];

    for (int k = 0; k < LOG; k++) {
        if (diff >> k & 1) a = up[k][a];
    }

    if (a == b) return a;

    for (int k = LOG - 1; k >= 0; k--) {
        if (up[k][a] != up[k][b]) { 
            a = up[k][a]; b = up[k][b];
        }
    }
        
    return up[0][a];
}

int dist(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}

void ustaw(int x, int parent) {
    up[0][x] = parent;
    dep[x] = dep[parent] + 1;
    for (int k = 1; k < LOG; k++)
        up[k][x] = up[k - 1][up[k - 1][x]];
}

void przepnij(int v, int u) {
    std::vector<int> q;
    q.push_back(u);
    ustaw(u, v);
    for (size_t i = 0; i < q.size(); i++) {
        int x = q[i];
        for (int w : adj[x]) {
            if (w == up[0][x]) continue;
            ustaw(w, x);
            q.push_back(w);
        }
    }
}

void dodaj_krawedz(int v, int u) {
    int a = rep(v), b = rep(u);
    if (a == b) {   // Krawedz w obrebie skladowej
        std::cout << (maxans) << '\n'; return;
    }

    // b ma byc mniejsza skladowa
    if (sz[a] < sz[b]) { std::swap(a, b); std::swap(v, u); }

    // Lacz drzewa
    przepnij(v, u);
    adj[v].push_back(u);
    adj[u].push_back(v);
    DSU[b] = a;
    sz[a] += sz[b];

    // Nowa srednica: 2 z 4 starych koncow
    int c[4] = {E1[a], E2[a], E1[b], E2[b]};
    int best = -1, bi = c[0], bj = c[1];
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++) {
            int d = dist(c[i], c[j]);
            if (d > best) { best = d; bi = c[i]; bj = c[j]; }
        }
    E1[a] = bi; E2[a] = bj;

    maxans = std::max(maxans, best + 1);
    std::cout << (maxans) << '\n';
}

void zaszyfrowane() {
    int v, u; std::cin >> v >> u; v--; u--;
    dodaj_krawedz(v, u);

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
    for (int i = 0; i < n; i++) {
        DSU[i] = i; sz[i] = 1; E1[i] = E2[i] = i;
        dep[i] = 0;
        for (int k = 0; k < LOG; k++) up[k][i] = i;
    }
    if (t) zaszyfrowane();
    else   nieszyfrowane();
}
