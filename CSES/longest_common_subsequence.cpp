#include <bits/stdc++.h>
using ll = long long;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, m; 
    if (!(std::cin >> n >> m)) return 0;
    
    std::vector<ll> A(n), B(m);
    for (int i = 0; i < n; i++) std::cin >> A[i];
    for (int i = 0; i < m; i++) std::cin >> B[i];

    // 2D DP table to store LCS lengths
    // dp[i][j] stores LCS of A[0..i-1] and B[0..j-1]
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i - 1] == B[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Reconstruction
    int i = n, j = m;
    std::vector<ll> ANS;
    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1]) {
            ANS.push_back(A[i - 1]);
            i--;
            j--;
        } 
        else if (dp[i - 1][j] == dp[i][j]) {
            i--;
        } 
        else {
            j--;
        }
    }

    std::reverse(ANS.begin(), ANS.end());

    std::cout << dp[n][m] << '\n';
    for (auto val : ANS) {
        std::cout << val << ' ';
    }
    std::cout << '\n';

    return 0;
}