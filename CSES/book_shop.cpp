#include <bits/stdc++.h>
int main() {
    int n; int x; std::cin >> n >> x;
    std::vector<int> H(n), S(n);
    for (int i = 0; i < n; i++) std::cin >> H[i];
    for (int i = 0; i < n; i++) std::cin >> S[i];

    std::vector<int> DP(x + 1, -1); // Max pages per price
    DP[0] = 0; for (int j = 0; j < n; j++) {
        int h = H[j]; int s = S[j];
        for (int i = x; i >= 0; i--) {
            if (i + h > x)   continue;
            if (DP[i] == -1) continue;
            DP[i + h] = std::max(DP[i + h], DP[i] + s);
        }
    }

    int max = 0; for (int s : DP) max = std::max(max, s);
    std::cout << max;
}
