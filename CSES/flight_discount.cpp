#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr int max_n = 100000;
constexpr ull inf_u = UINT64_MAX / 2;

std::vector<std::pair<int, ull>> G[max_n];
ull M[max_n][2]; // Minimal cost

int main() {
    // Load Data
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, m; std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; ull c; std::cin >> x0 >> x1 >> c; 
        x0--; x1--; G[x0].push_back({x1, c});
    }

    // Fill M cost state
    for (int i = 0; i < max_n; i++) {
        M[i][false] = inf_u; M[i][true] = inf_u;
    }

    // Total Cost, Vertex, Coupon Used
    using state = std::tuple<ull, int, bool>;
    std::priority_queue<state, std::vector<state>, std::greater<state>> Q;
    Q.push({0, 0, false}); while (!Q.empty()) {
        auto [c, v, cu] = Q.top(); Q.pop();
        if (M[v][cu] <= c) continue;
        M[v][cu] = c; for (auto [u, cg] : G[v]) {
            Q.push({c + cg, u, cu});
            if (!cu) Q.push({c + (cg/2), u, true});
        }
    }

    std::cout << std::min(M[n - 1][false], M[n - 1][true]);
}