#include <bits/stdc++.h>
constexpr int max_n = 100000;
using ull = unsigned long long;
std::vector<std::pair<int, ull>> G[max_n];
std::stack<ull>                  B[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, m, k; std::cin >> n >> m >> k; for (int i = 0; i < m; i++) {
        int x0, x1; ull c; std::cin >> x0 >> x1 >> c;
        x0--; x1--; G[x0].push_back({x1, c});
    }

    std::priority_queue<
        std::pair<ull, int>,
        std::vector<std::pair<ull, int>>,
        std::greater<std::pair<ull, int>>
    > Q; 
    Q.push({0, 0}); std::multiset<ull> ANS; while (!Q.empty()) {
        auto [c, v] = Q.top(); Q.pop();

        while (B[v].size() && B[v].top() > c) B[v].pop();
        if (B[v].size() >= k) continue;
        B[v].push(c);
        
        if (v == n - 1) {
            ANS.insert({c});
            if (ANS.size() >= k) break;
        }
        for (auto [u, cc] : G[v]) {
            Q.push({c + cc, u});
        }
    }

    for (ull x : ANS) std::cout << x << ' ';
}
