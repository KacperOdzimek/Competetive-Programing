#include <bits/stdc++.h>
using ll = long long;
constexpr int max_n = 2500;
constexpr ll  inf_l = LONG_LONG_MIN / 2;

int n, m; 
std::vector<std::tuple<int, int, ll>> E;
std::vector<int> R[max_n];

int ITR = 0;
int VIS[max_n];

bool CRN[max_n];    // Can reach N?
void can_reach_n_dfs(int v) {
    if (VIS[v] == ITR) return; 
    VIS[v] = ITR; CRN[v] = true;
    for (int u : R[v]) can_reach_n_dfs(u);
}

ll DIST[max_n];
ll bellman_ford() {
    for (int i = 0; i < n; i++) DIST[i] = inf_l;
    DIST[0] = 0; for (int i = 1; i < n; i++) {
        for (auto [x0, x1, c] : E) {
            if (DIST[x0] == inf_l) continue;
            if (DIST[x0] + c > DIST[x1]) {
                DIST[x1] = DIST[x0] + c;
            }
        }
    }

    for (auto [x0, x1, c] : E) {
        if (DIST[x0] == inf_l) continue;
        if (DIST[x0] + c > DIST[x1] && CRN[x1]) return -1;
    }

    return DIST[n - 1];
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; while (m--) {
        int x0, x1; ll c; std::cin >> x0 >> x1 >> c; 
        x0--; x1--; E.push_back({x0, x1, c}); R[x1].push_back(x0);
    }
    ITR++; can_reach_n_dfs(n - 1);
    std::cout << bellman_ford();
}
