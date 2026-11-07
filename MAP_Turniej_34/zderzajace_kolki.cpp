#include <bits/stdc++.h>
using ll = long long;

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(0);
    int n; std::cin >> n;
    std::unordered_set<ll> s;
    s.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        ll x; std::cin >> x;
        if (!s.insert(x + i).second) {
            std::cout << "NIE\n";
            return 0;
        }
    }
    std::cout << "TAK\n";
}
