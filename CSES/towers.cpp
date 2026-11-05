#include <bits/stdc++.h>
using ll = long long;
int main() {
    int n; std::cin >> n; std::multiset<ll> T;
    while (n--) {
        ll v; std::cin >> v;
        auto itr = T.upper_bound(v);
        if (itr == T.end()) T.insert(v);
        else {
            T.erase(itr);
            T.insert(v);
        }
    }
    std::cout << T.size();
}
