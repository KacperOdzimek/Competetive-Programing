#include <bits/stdc++.h>
constexpr int max_n = 100000;

std::vector<int> A[max_n];
bool V[max_n];

void dfs(int v) {
    if (V[v]) return;
    V[v] = true; for (int u : A[v]) dfs(u);
}

int main() {
    int n, m; std::cin >> n >> m;
    while (m--) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        A[x0].push_back(x1); A[x1].push_back(x0);
    }

    std::vector<int> R; for (int v = 0; v < n; v++) {
        if (V[v]) continue;
        R.push_back(v); dfs(v);
    }

    std::cout << R.size() - 1 << '\n';
    for (int i = 0; i < R.size() - 1; i++) {
        std::cout << R[i] + 1 << ' ' << R[i + 1] + 1 << '\n';
    }
}
