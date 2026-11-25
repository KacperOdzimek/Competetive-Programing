#include <bits/stdc++.h>
using ll = long long;
constexpr ll  M = 1'000'000'000 + 7;
constexpr int X = 1'000'000 + 1;

std::vector<ll> C;
bool VIST[X];
ll   WAYS[X];

ll dfs(ll needed) {
    if (VIST[needed]) return WAYS[needed];
    for (ll coin : C) {
        ll new_needed = needed - coin;
        if (new_needed < 0 || new_needed >= X) continue;
        (WAYS[needed] += dfs(new_needed)) %= M;
    }
    VIST[needed] = true;
    return WAYS[needed];
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    ll n, x; std::cin >> n >> x; C.resize(n);
    for (ll i = 0; i < n; i++) std::cin >> C[i];
    VIST[0] = true; WAYS[0] = 1;
    ll ans = dfs(x); std::cout << ans;
}