#include <bits/stdc++.h>
constexpr int MOD = 1'000'000'000 + 7;
int main() {
    int n, m; std::cin >> n >> m;
    auto DP = std::vector<std::vector<int>>(n + 1, std::vector<int>(102));

    // So every range of three have one 1
    for (int i = 0; i < 101; i++) {
        if (i % 3 == 0) DP[0][i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        int c; std::cin >> c;
        if (c == 0) {
            c = m; while (c != 0) {
                DP[i][c] = DP[i - 1][c + 1] + DP[i - 1][c] + DP[i - 1][c - 1];
                c--;
            }
        }
        else {
            DP[i][c] = DP[i - 1][c + 1] + DP[i - 1][c] + DP[i - 1][c - 1];
        }
    }

    int ans = 0; for (int i = 0; i < m; i++) {
        ans += DP[n - 1][i];
        ans %= MOD;
    }

    std::cout << ans;
}
