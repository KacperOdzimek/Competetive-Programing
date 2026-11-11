#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n, m; std::cin >> n >> m;

    std::vector<std::string> grid(n);
    for (int i = 0; i < n; i++) std::cin >> grid[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (char c = 'A'; c <= 'D'; c++) {
                if (c == grid[i][j]) continue;
                if (i > 0 && c == grid[i - 1][j]) continue;
                if (j > 0 && c == grid[i][j - 1]) continue;
                grid[i][j] = c;
                break;
            }
        }
    }

    for (const std::string &row : grid) std::cout << row << '\n';
}