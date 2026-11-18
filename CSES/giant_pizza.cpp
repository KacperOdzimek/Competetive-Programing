#include <bits/stdc++.h>
constexpr int max_m = 100000;

// Graphs

int n, m;
std::vector<int> G[2 * max_m];
std::vector<int> R[2 * max_m];

void add_implication(int reason_this, int imply_this) {
    G[reason_this].push_back(imply_this);
    R[imply_this].push_back(reason_this);
}

void build_sat() {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char g1; int v1; std::cin >> g1 >> v1; v1--;
        char g2; int v2; std::cin >> g2 >> v2; v2--;

        int v1_false = v1 * 2;
        int v1_true  = v1 * 2 + 1;

        int v2_false = v2 * 2;
        int v2_true  = v2 * 2 + 1;

        int v1_met = g1 == '+' ? v1_true : v1_false;
        int v1_inv = g1 == '+' ? v1_false : v1_true;

        int v2_met = g2 == '+' ? v2_true : v2_false;
        int v2_inv = g2 == '+' ? v2_false : v2_true;

        add_implication(v1_inv, v2_met);
        add_implication(v2_inv, v1_met);
    }
}

// SCC Finding

int VITR;
int VIS[2 * max_m];

int SCC;
int VSCC[2 * max_m];
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
    std::vector<int> O; VITR++;
    for (int i = 0; i < 2 * m; i++) {
        if (VIS[i] == VITR) continue;
        korasaju_dfs_1(i, O);
    }

    VITR++; for (int i = O.size() - 1; i >= 0; i--) {
        int v = O[i]; if (VIS[v] == VITR) continue;
        SCC++; korasaju_dfs_2(v);
    }
}

// Main Logic

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    build_sat(); korasaju();

    for (int i = 0; i < m; i++) {
        if (VSCC[2*i] != VSCC[2*i+1]) continue;
        std::cout << "IMPOSSIBLE\n"; return 0;
    }

    std::vector<bool> state(m);
    for (int i = 0; i < m; i++) state[i] = VSCC[2*i+1] > VSCC[2*i];
    for (int i = 0; i < m; i++) std::cout << (state[i] ? '+' : '-') << ' ';
}
