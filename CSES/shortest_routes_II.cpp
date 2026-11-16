#include <bits/stdc++.h>
using ull = unsigned long long;

constexpr int max_n = 500;
constexpr ull inf = UINT64_MAX / 2 - 1;
ull DIST[max_n][max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    for (int i = 0; i < max_n; i++) for (int j = 0; j < max_n; j++) DIST[i][j] = (i == j) ? 0 : inf;

    int n, m, q; std::cin >> n >> m >> q; while (m--) {
        int x0, x1; ull d; std::cin >> x0 >> x1 >> d; x0--; x1--;
        DIST[x0][x1] = std::min(DIST[x0][x1], d); 
        DIST[x1][x0] = std::min(DIST[x1][x0], d);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                DIST[i][j] = std::min(DIST[i][j], DIST[i][k] + DIST[k][j]);
            }
        }
    }

    while (q--) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        ull dist = DIST[x0][x1];
        if (dist >= inf) std::cout << "-1\n";
        else std::cout << dist << '\n';
    }
}
