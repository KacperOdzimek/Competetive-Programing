#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr int max_n = 100000;

int n, m; 
ull C[max_n];
std::vector<int> G[max_n];
std::vector<int> R[max_n];

int VITR;
int VIS[max_n];

int SCC;
int VSCC[max_n];
void korasaju_dfs_1(int v, std::vector<int>& O) {
    if (VIS[v] == VITR) return;
    VIS[v] = VITR;
    for (int u : G[v]) korasaju_dfs_1(u, O);
    O.push_back(v);
}
void korasaju_dfs_2(int v) {
    if (VIS[v] == VITR) return;
    VIS[v] = VITR; VSCC[v] = SCC;
    for (int u : R[v]) korasaju_dfs_2(u);
}
void korasaju() {
    VITR++; std::vector<int> O; 
    for (int i = 0; i < n; i++) {
        if (VIS[i] == VITR) continue;
        korasaju_dfs_1(i, O);
    }
    VITR++; for (int i = O.size() - 1; i >= 0; i--) {
        int v = O[i]; if (VIS[v] == VITR) continue;
        korasaju_dfs_2(v); SCC++;
    }
}

ull  CD[max_n];
bool ID[max_n];
std::vector<int> D[max_n];
ull  AN[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; 
    for (int i = 0; i < n; i++) std::cin >> C[i];
    for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        G[x0].push_back(x1); R[x1].push_back(x0);
    }
    korasaju(); 
    for (int v = 0; v < n; v++) {
        int vscc = VSCC[v];
        CD[vscc] += C[v];
        for (int u : G[v]) {
            int uscc = VSCC[u];
            if (vscc == uscc) continue;
            D[vscc].push_back(uscc);
            ID[uscc] = true;
        }
    }
    std::vector<std::pair<int, ull>> Q, nQ;
    for (int v = 0; v < SCC; v++) if (!ID[v]) Q.push_back({v, CD[v]});
    ull answer = 0; while (Q.size()) {
        for (auto [v, coins] : Q) {
            if (coins <= AN[v]) continue;
            AN[v] = coins; answer = std::max(answer, coins);
            for (int u : D[v]) nQ.push_back({u, coins + CD[u]});
        }
        Q.swap(nQ); nQ.clear();
    }
    std::cout << answer;
}
