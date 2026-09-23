#include <bits/stdc++.h>

// Config
constexpr int max_n = 100000;

// Dane z zadania
int n, m;
std::vector<int>    OG[max_n];  // Oryginalny
std::set<int>       G[max_n];

void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; std::cin >> a >> b; a--; b--;
        OG[a].push_back(b);
        OG[b].push_back(a);
        G[a].insert(b);
        G[b].insert(a);
    }
}

// Stan Visited dla Przejsc
int Vitr = 0;
int VIS[max_n];

static inline void visit(int v) {
    VIS[v] = Vitr;
}

static inline bool visisted(int v) {
    return VIS[v] == Vitr;
}

static inline void clear_vis() {
    Vitr++;
}

// Mosty

// Temp:
int              P[max_n];
std::vector<int> D[max_n];
std::vector<int> W[max_n];
int  low  [max_n];
int  depth[max_n];

// Out: Posortowane mosty
std::set<std::pair<int, int>> M;

void dfs_mosty(int v, int p) {
    visit(v); P[v] = p;
    for (auto u : G[v]) {
        if (u == p) continue;
        if (visisted(u)) W[v].push_back(u);
        else {
            D[v].push_back(u);
            D[u].push_back(v);
            dfs_mosty(u, v);
        }
    }
}

void calculate_low (int v) {
    visit(v);
    low[v] = depth[v];
    for (int u : D[v]) {
        if(!visisted(u)) {
            depth[u] = depth[v] + 1;
            calculate_low(u);
            low[v] = std::min(low[v], low[u]);
        }
    }
    for(int u : W[v]) low[v] = std::min(low[v], depth[u]);
}

void mosty() {
    clear_vis();
    dfs_mosty(0, -1);

    clear_vis();
    calculate_low(0);

    for (int v = 1; v < n; v++) {
        if (low[v] == depth[v]) {
            int v1 = v; int v2 = P[v];
            if (v1 > v2) std::swap(v1, v2);
            M.insert({v1, v2});
        }
    }
}

// Rozspojnianie
void rozpojnij() {
    for (auto m : M) {
        G[m.first].erase(m.second);
        G[m.second].erase(m.first);
    }
}

// Znajdz spojne
int SP_COUNT = 0;   // Ilosc
int OSP[max_n];     // Spojna wlasciciel
int ORP[max_n];     // Reprezentant spojnej

void eksploruj_spojna(int v) {
    visit(v);
    for (int u : G[v]) {
        if (visisted(u)) continue;
        eksploruj_spojna(u);
    }
    OSP[v] = SP_COUNT;
    ORP[SP_COUNT] = v;
}

void znajdz_spojne() {
    clear_vis();
    for (int i = 0; i < n; i++) {
        if (!visisted(i)) eksploruj_spojna(i);
        SP_COUNT++;
    }
}

// Graf spojnych
std::set<int> GS[max_n];
void graf_spojnych() {
    for (int v = 0; v < n; v++) {
        for (int u : OG[v]) {
            int sv = OSP[v];
            int su = OSP[u];
            if (sv == su) continue;
            GS[sv].insert(su);
            GS[su].insert(sv);
        }
    }
}

// Odpowiedz
void odpowiedz() {
    std::vector<int> z_deg_1;
    for (int i = 0; i < SP_COUNT; i++) {
        if (GS[i].size() == 1) z_deg_1.push_back(i);
    }

    std::random_device rd{};
    std::mt19937 gen(rd() * 13 * 91);
    std::shuffle(z_deg_1.begin(), z_deg_1.end(), gen);

    std::vector<std::pair<int, int>> K;
    int i = 0; for (; i + 1 < z_deg_1.size(); i += 2) {
        int si1 = ORP[z_deg_1[i]];
        int si2 = ORP[z_deg_1[i + 1]];
        K.push_back({si1, si2});
    }

    if (z_deg_1.size() - i == 1) {
        int ostatni = z_deg_1.back();
        int inne = 0; while (inne < SP_COUNT) {
            if (inne == ostatni) inne++;
            else break;
        }
        int si1 = ORP[ostatni];
        int si2 = ORP[inne];
        K.push_back({si1, si2});
    }

    std::cout << K.size() << '\n'; for (auto k : K) {
        std::cout << (k.first + 1) << ' ' << (k.second + 1) << '\n'; 
    }
}

int main() {
    load();
    mosty();
    rozpojnij();
    znajdz_spojne();
    graf_spojnych();
    odpowiedz();
}
