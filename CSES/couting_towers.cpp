#include <bits/stdc++.h>
using ll = long long;
constexpr ll MOD = 1'000'000'000 + 7;
constexpr ll MAX = 1'000'000 + 1;
ll DP[MAX][2];  // 0 - Connected at End, 1 - Disconnected at End
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    DP[1][0] = 1; DP[1][1] = 1;
    for (int i = 2; i <= MAX; i++) {
        DP[i][0] = (2 * DP[i - 1][0] + DP[i - 1][1]) % MOD; // We can either make merged seg longer, or put another merged
        DP[i][1] = (DP[i - 1][0] + 4 * DP[i - 1][1]) % MOD; // We can either make any longer, or not, giving 4 states
    }
    int t; std::cin >> t; while (t--) {
        int n; std::cin >> n;
        ll ans = (DP[n][0] + DP[n][1]) % MOD;
        std::cout << ans << '\n';
    }
}