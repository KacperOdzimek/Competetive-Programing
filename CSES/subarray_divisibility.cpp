#include <bits/stdc++.h>
using ll = long long;
constexpr int max_n = 2 * 100000;

std::vector<int> Q[max_n];  // Prefixed indices grouped by P[i] mod n

ll mod(ll x, ll m) {
    if (x < 0) return (m - (-x % m)) % m;
    return x % m;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; std::vector<ll> V(n); 
    for (int i = 0; i < n; i++) std::cin >> V[i];

    std::vector<ll> P(n); P[0] = V[0];
    for (int i = 1; i < n; i++) P[i] = P[i - 1] + V[i];

    for (int i = 0; i < n; i++) {
        ll ii = mod(P[i], n);
        Q[ii].push_back(i);
    }

    // prefix - a == 0  mod n
    // prefix == a      mod n
    ll ans = 0; for (int i = -1; i < n - 1; i++) {
        ll prefix  = i >= 0 ? P[i] : 0;
        ll my_mod  = mod(prefix, n);
        const std::vector<int>& q = Q[my_mod];
        auto litr = std::lower_bound(q.begin(), q.end(), i + 1);
        ans += std::distance(litr, q.end());
    }

    std::cout << ans;
}
