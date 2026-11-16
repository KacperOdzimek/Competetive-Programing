#include <bits/stdc++.h>
constexpr int max_dim = 1000;

int  n, m;
char M[max_dim][max_dim];
bool V[max_dim][max_dim];

void dfs(int i, int j) {
    if (i < 0 || i >= n) return;
    if (j < 0 || j >= m) return;
    if (M[i][j] == '#')  return;
    if (V[i][j])         return;
    V[i][j] = true;
    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> M[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (M[i][j] == '#') continue;
            if (V[i][j]) continue;
            ans++; dfs(i, j);
        }
    }

    std::cout << ans;
}
