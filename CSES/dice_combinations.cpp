#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr ull M = 1'000'000'000 + 7; 
int main() {
    // DP[x] = DP[x - 1] + DP[x - 2] + ... + DP[x - 6]
    int n; std::cin >> n; std::vector<ull> DP(n + 1);
    DP[0] = 1; for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= std::max(0, i - 6); j--) {
            (DP[i] += DP[j]) %= M;
        }
    }
    std::cout << DP[n];
}
