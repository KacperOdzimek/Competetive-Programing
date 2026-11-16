#include <bits/stdc++.h>
constexpr int max_n = 100000;

std::vector<int> G[max_n];
char             C[max_n];

bool dfs(int v, char c) {
    if (C[v]) return C[v] == c;
    C[v] = c; char co = c == '1' ? '2' : '1';
    bool R = true; for (int u : G[v]) R &= dfs(u, co);
    return R;
}

int main() {
    int n, m; std::cin >> n >> m; while (m--) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        G[x0].push_back(x1); G[x1].push_back(x0);
    }

    bool R = true; for (int v = 0; v < n; v++) {
        if (C[v] == '\0') R &= dfs(v, '1');
    }

    if (!R) std::cout << "IMPOSSIBLE";
    else for (int i = 0; i < n; i++) std::cout << C[i] << ' ';
}
