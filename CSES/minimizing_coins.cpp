#include <bits/stdc++.h>
constexpr int inf = INT32_MAX - 2 * 1'000'000;
int main() {
    int n, x; std::cin >> n >> x; 
    std::vector<int> DP(x + 1, inf); 
    DP[0] = 0; while (n--) {
        int m; std::cin >> m;
        for (int i = 0; i < x; i++) {
            if (i + m >= x + 1) break;
            DP[i + m] = std::min(DP[i + m], DP[i] + 1);
        }
    }
    if (DP[x] == inf) std::cout << "-1";
    else std::cout << DP[x];
}
