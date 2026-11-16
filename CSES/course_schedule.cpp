#include <bits/stdc++.h>
constexpr int max_n = 100000;

int n, m;
std::vector<int> G[max_n];
int INDEG[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; while (m--) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        G[x0].push_back(x1); INDEG[x1]++;
    }

    std::vector<int> Q, nQ; for (int i = 0; i < n; i++) {
        if (INDEG[i] == 0) Q.push_back(i);
    }

    if (Q.size() == 0) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    std::vector<int> A;
    while (Q.size()) {
        for (int v : Q) {
            A.push_back(v);
            for (int u : G[v]) {
                INDEG[u]--;
                if (INDEG[u] < 0) {
                    std::cout << "IMPOSSIBLE\n";
                    return 0;
                }
                if (INDEG[u] == 0) nQ.push_back(u);
            }
        }
        Q.swap(nQ); nQ.clear();
    }

    if (A.size() != n) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int v : A) std::cout << v + 1 << ' ';
}
