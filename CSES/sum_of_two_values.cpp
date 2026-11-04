#include <bits/stdc++.h>
using ll = long long;
int main() {
    int n; ll x; std::cin >> n >> x; std::vector<std::pair<ll, int>> L(n);
    for (int i = 0; i < n; i++) {
        std::cin >> L[i].first; L[i].second = i + 1;
    }; std::sort(L.begin(), L.end());
    for (int i = 0; i < L.size(); i++) {
        ll m = x - L[i].first; 
        auto itr = std::lower_bound(L.begin() + i + 1, L.end(), std::pair<ll, int>{m, 0});
        if (itr == L.end()) continue; if (itr->first > m) continue;
        std::cout << L[i].second << ' ' << itr->second; return 0;
    }
    std::cout << "IMPOSSIBLE\n";
}