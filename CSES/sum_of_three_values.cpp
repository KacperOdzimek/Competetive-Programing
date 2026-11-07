#include <bits/stdc++.h>
using ull = long long;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    int n; ull x; std::cin >> n >> x; std::vector<std::pair<ull, int>> V(n);
    for (int i = 0; i < n; i++) { std::cin >> V[i].first; V[i].second = i + 1; }
    std::sort(V.begin(), V.end());

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            ull sum = V[i].first + V[j].first;
            if (sum > x) continue;
            ull mis = x - sum;
            auto k_itr = std::lower_bound(V.begin(), V.end(), std::pair<ull, int>{mis, 0});

            while (k_itr != V.end() && (k_itr->second == V[i].second || k_itr->second == V[j].second)) k_itr++;
            if (k_itr == V.end()) continue;

            if (k_itr->first == mis) {
                std::cout << V[i].second << ' ' << V[j].second << ' ' << k_itr->second;
                return 0;
            }
        }
    }
    std::cout << "IMPOSSIBLE";
}
