#include <bits/stdc++.h>
using ll = long long;
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    ll n; std::cin >> n; std::vector<std::pair<ll, ll>> R(n);
    for (ll i = 0; i < n; i++) std::cin >> R[i].first >> R[i].second;
    std::sort(R.begin(), R.end());
    ll score = 0; ll time = 0; for (auto [l, d] : R) {
        time += l; score += (d - time);
    } std::cout << score;
}
