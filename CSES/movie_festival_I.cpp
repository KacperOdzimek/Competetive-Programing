#include <bits/stdc++.h>
constexpr int max_n = 2 * 100000;
using ll = long long;
int DP[max_n];  // Max watched prior movie
int main() {
    std::vector<std::tuple<ll, bool, int>> E;
    int n; std::cin >> n; for (int i = 0; i < n; i++) {
        ll a, b; std::cin >> a >> b;
        E.push_back({a, true, i}); E.push_back({b, false, i});
    } std::sort(E.begin(), E.end());
    int max_dp = 0; for (auto [a, t, i] : E) {
        if (t) DP[i] = max_dp;
        else   max_dp = std::max(max_dp, DP[i] + 1);
    }
    std::cout << max_dp;
}