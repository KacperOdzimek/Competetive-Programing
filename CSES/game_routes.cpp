#include <bits/stdc++.h>
constexpr int max_n = 100000;
constexpr int mod   = 1'000'000'000 + 7;

int n, m;
std::vector<int> G[max_n];
int I[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; 
        x0--; x1--; G[x0].push_back(x1); I[x1]++;
    }

    std::vector<int> TOPO;
    for (int i = 0; i < n; i++) if (!I[i]) TOPO.push_back(i);

    for (int i = 0; i < TOPO.size(); i++) {
        int v = TOPO[i]; for (int u : G[v]) {
            I[u]--; if (!I[u]) TOPO.push_back(u);
        }
    }

    std::vector<int> WAYS(n, 0); WAYS[0] = 1;
    for (int i = 0; i < n; i++) {
        int v = TOPO[i]; for (int u : G[v]) {
            (WAYS[u] += WAYS[v]) %= mod;
        }
    }

    std::cout << WAYS[n - 1];
}
