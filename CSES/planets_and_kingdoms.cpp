#include <bits/stdc++.h>
constexpr int max_n = 100000;
std::vector<int> G[max_n];
std::vector<int> R[max_n];

int VITR;
int VIS[max_n];

int SCC;
int VSCC[max_n];

void korasaju_dfs_1(int v, std::vector<int>& O) {
    if (VIS[v] == VITR) return;
    VIS[v] = VITR; for (int u : G[v]) korasaju_dfs_1(u, O);
    O.push_back(v);
}

void korasaju_dfs_2(int v) {
    if (VIS[v] == VITR) return;
    VIS[v] = VITR; for (int u : R[v]) (korasaju_dfs_2(u));
    VSCC[v] = SCC;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, m; std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; 
        x0--; x1--; G[x0].push_back(x1); R[x1].push_back(x0);
    }

    std::vector<int> O; VITR++; for (int i = 0; i < n; i++) {
        if (VIS[i] == VITR) continue;
        korasaju_dfs_1(i, O);
    }

    VITR++; for (int i = O.size() - 1; i >= 0; i--) {
        int v = O[i]; if (VIS[v] == VITR) continue;
        SCC++; korasaju_dfs_2(v);
    }

    std::cout << SCC << '\n';
    for (int i = 0; i < n; i++) std::cout << VSCC[i] << ' ';
}