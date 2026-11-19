#include <bits/stdc++.h>
using ll = long long;
constexpr ll mod = 1'000'000'000 + 7;
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::unordered_map<ll, int> C; int n; std::cin >> n;
    while (n--) {
        ll x; std::cin >> x; 
        if (C.find(x) == C.end()) C.insert({x, 1});
        else C[x]++;
    }
    ll ans = 1; // Empty set
    for (auto [v, c] : C) (ans *= (c + 1)) %= mod; // Either one of instances or no instance
    std::cout << (ans - 1); // Empty set excluded
}