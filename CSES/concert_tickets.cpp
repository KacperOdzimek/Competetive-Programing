#include <bits/stdc++.h>
using ll = long long;
int main() {
    int n, m; std::cin >> n >> m;
    std::multiset<ll> P; while (n--) {
        ll x; std::cin >> x; P.insert(x);
    }
    while (m--) {
        ll x; std::cin >> x;
        auto itr = P.lower_bound(x);
        if (itr != P.end() && *itr == x) {
            std::cout << x << '\n';
            P.erase(itr);
        }
        else if (itr != P.begin()) {
            itr--; std::cout << *itr << '\n';
            P.erase(itr);
        }
        else {
            std::cout << "-1\n";
        }
    }
}