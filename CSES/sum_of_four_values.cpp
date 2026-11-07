#include <bits/stdc++.h>
using ll = long long;

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(0);
    int n; ll x; std::cin >> n >> x;

    std::vector<ll> v(n);
    for (auto &a : v) std::cin >> a;

    std::map<ll, std::vector<std::pair<int, int>>> mp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll need = x - v[i] - v[j];
            if (mp.count(need)) {
                for (auto [a, b] : mp[need]) {
                    if (a != i && a != j && b != i && b != j) {
                        std::cout << a + 1 << ' ' << b + 1 << ' ' << i + 1 << ' ' << j + 1;
                        return 0;
                    }
                }
            }
            mp[v[i] + v[j]].push_back({i, j});
        }
    }

    std::cout << "IMPOSSIBLE";
}
