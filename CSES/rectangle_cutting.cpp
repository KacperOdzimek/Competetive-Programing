#include <bits/stdc++.h>
constexpr int max_dim = 501;
constexpr int inf_mov = INT32_MAX;

// We can always make a cut on one edge
// Preserving other. We then must care about two rectangles.
// Therefore DP[i][j] = min(DP[i - x][j] + DP[i + x][j] + 1) and same for j, merged min
// Also DP for squares DP[x][x] is always 0

int DP[max_dim][max_dim];
int main() {
    for (int i = 1; i <= max_dim; i++) {
        for (int j = 1; j <= max_dim; j++) {
            DP[i][j] = (i == j) ? 0 : inf_mov;
        }
    }

    for (int i = 1; i <= max_dim; i++) {
        for (int j = 1; j <= max_dim; j++) {
            for (int x = 1; x < i; x++) DP[i][j] = std::min(DP[i][j], DP[i - x][j] + DP[x][j] + 1);
            for (int x = 1; x < j; x++) DP[i][j] = std::min(DP[i][j], DP[i][j - x] + DP[i][x] + 1);
        }
    }

    int i, j; std::cin >> i >> j;
    std::cout << DP[i][j];
}
