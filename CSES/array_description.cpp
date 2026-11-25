#include <bits/stdc++.h>
using ll = long long;

constexpr ll  MOD = 1'000'000'000 + 7;
constexpr int MAX_N = 100000;
constexpr int MAX_M = 102;

int n, m;
ll WAYS[MAX_N][MAX_M];

void set_ways(int v, int layer) {
    if (v <= 0 || v > m) return;
    if (layer == 1) {
        WAYS[layer][v] = 1;
        return;
    }
    for (int i = -1; i <= 1; i++) {
        int u = v + i;
        if (u <= 0 || u > m) continue;
        (WAYS[layer][v] += WAYS[layer - 1][u]) %= MOD;
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; for (int i = 1; i <= 100; i++) WAYS[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        int v; std::cin >> v;
        if (v != 0) set_ways(v, i);                         // Set DP only for this value
        else for (int j = 1; j <= m; j++) set_ways(j, i);   // Set DP for every value
    }
    ll ans = 0; 
    for (int i = 1; i <= m; i++) (ans += WAYS[n][i]) %= MOD;
    std::cout << ans;
}
