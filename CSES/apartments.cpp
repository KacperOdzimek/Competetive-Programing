#include <bits/stdc++.h>
using ll = long long;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    ll n, m, k; std::cin >> n >> m >> k; std::vector<ll> S(n); std::multiset<ll> A;
    for (int i = 0; i < n; i++) std::cin >> S[i];
    for (int i = 0; i < m; i++) {ll x; std::cin >> x; A.insert(x); }
    std::sort(S.begin(), S.end());

    ll ans = 0; for (ll s : S) {
        ll min_s = s - k, max_s = s + k;
        auto itr = A.lower_bound(min_s);
        if (itr == A.end()) continue;
        if (*itr > max_s) continue;
        A.erase(itr); ans++;
    }
    
    std::cout << ans;
}
