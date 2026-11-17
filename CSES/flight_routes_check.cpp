#include <bits/stdc++.h>
constexpr int max_n = 100000;

int n, m;
std::vector<int> G[max_n];
std::vector<int> R[max_n];

int VITR;
int VIS[max_n];

void korasaju_dfs_1(int v, std::vector<int>& O) {
    if (VIS[v] == VITR) return;
    VIS[v] = VITR; for (int u : G[v]) korasaju_dfs_1(u, O);
    O.push_back(v); 
}

void korasaju_dfs_2(int v) {
    if (VIS[v] == VITR) return;
    VIS[v] = VITR; for (int u : R[v]) korasaju_dfs_2(u);

}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--; 
        G[x0].push_back(x1); R[x1].push_back(x0);
    }


    VITR++; std::vector<int> O; for (int i = 0; i < n; i++) {
        if (VIS[i] != VITR) korasaju_dfs_1(i, O);
    }

    VITR++; int SCC = 0;
    for (int i = O.size() - 1; i >= 0; i--) {
        int v = O[i]; if (VIS[v] == VITR) continue;
        SCC++; korasaju_dfs_2(v);
        if (SCC >= 2) {
            std::cout << "NO\n";
            std::cout << v + 1 << ' ' << O[n - 1] + 1;
            return 0;
        }
    }

    std::cout << "YES";
}
