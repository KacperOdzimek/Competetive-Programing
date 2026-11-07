#include <bits/stdc++.h>
using ll = long long;
int main() {
    int n; ll x; std::cin >> n >> x; std::vector<ll> V(n);
    for (int i = 0; i < n; i++) std::cin >> V[i];
    
    std::vector<ll> P(n); P[0] = V[0];
    for (int i = 1; i < n; i++) P[i] = P[i - 1] + V[i];

    std::vector<std::pair<ll, int>> PS(n);
    for (int i = 0; i < n; i++) PS[i] = {P[i], i};
    std::sort(PS.begin(), PS.end());

    ll ans = 0; for (int i = -1; i < n - 1; i++) {
        ll removed  = i >= 0 ? P[i] : 0;
        ll searched = removed + x;
        auto litr = std::lower_bound(PS.begin(), PS.end(), std::pair<ll, int>{searched, i + 1});
        auto uitr = std::upper_bound(PS.begin(), PS.end(), std::pair<ll, int>{searched, n});
        if (litr != PS.end() && litr->first == searched) {
            ans += std::distance(litr, uitr);
        }
    }
    
    std::cout << ans;
}
