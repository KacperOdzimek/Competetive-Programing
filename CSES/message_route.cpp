#include <bits/stdc++.h>
constexpr int max_n = 100000;

int n, m;
std::vector<int> G[max_n];
int P[max_n];   // Previous

int main() {
    std::cin.tie(0); std::ios::sync_with_stdio(0);

    std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        G[x0].push_back(x1); G[x1].push_back(x0);
    }

    std::queue<int>   Q;
    std::vector<bool> V(n, false);
    Q.push(0); V[0] = true; P[0] = -1;

    while (Q.size()) {
        int v = Q.front(); Q.pop();
        for (int u : G[v]) {
            if (V[u]) continue;
            V[u] = true; P[u] = v;
            Q.push(u);
        }
    }

    if (!V[n - 1]) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }

    std::vector<int> R; int v = n - 1; while (v != -1) { R.push_back(v + 1); v = P[v]; }
    std::reverse(R.begin(), R.end());

    std::cout << R.size() << '\n';
    for (int i = 0; i < R.size(); i++) std::cout << R[i] << ' ';
}
