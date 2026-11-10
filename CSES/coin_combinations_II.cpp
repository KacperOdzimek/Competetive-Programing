#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr ull M = 1'000'000'000 + 7; 
int main() {
    int n, x; std::cin >> n >> x; std::vector<ull> DP(x + 1);
    DP[0] = 1; while (n--) {
        int c; std::cin >> c;
        for (int i = 0; i < DP.size(); i++) {
            if (i + c >= x + 1) break;
            (DP[i + c] += DP[i]) %= M;
        }
    }
    std::cout << DP[x];
}
