#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr int max_n = 100000;
std::vector<std::pair<int, ull>> G[max_n];
ull T[max_n];

int main() {
    int n, m; std::cin >> n >> m; while (m--) {
        int x0, x1, c; std::cin >> x0 >> x1 >> c; x0--; x1--;
        G[x0].push_back({x1, c});
    }

    // Time, City
    std::priority_queue<
        std::pair<ull, int>, 
        std::vector<std::pair<ull, int>>, 
        std::greater<std::pair<ull, int>>
    > Q; 
    
    Q.push({0, 0}); while (!Q.empty()) {
        auto [t, v] = Q.top(); Q.pop();
        if (T[v] != 0 && T[v] <= t) continue; 
        T[v] = t; for (auto [u, c] : G[v]) {
            ull at = t + c; Q.push({at, u});
        }
    }

    std::cout << 0 << ' ';
    for (int i = 1; i < n; i++) std::cout << T[i] << ' ';
}
