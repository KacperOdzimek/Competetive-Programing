#include <bits/stdc++.h>
constexpr int max_n = 1000;
bool V[max_n][max_n];
int  D[max_n][max_n];

std::vector<std::pair<int, int>> dirs = {
    {-2, 1},  {-1, 2},  {1, 2},  {2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0); 
    int n; std::cin >> n; std::queue<std::tuple<int, int, int>> Q; 
    Q.push({0, 0, 0}); while (!Q.empty()) {
        auto [vi, vj, d] = Q.front(); Q.pop();
        if (V[vi][vj]) continue;
        V[vi][vj] = true;
        D[vi][vj] = d;
        for (auto dir : dirs) {
            int nvi = vi + dir.first;
            int nvj = vj + dir.second;
            if (nvi < 0 || nvi >= n) continue;
            if (nvj < 0 || nvj >= n) continue;
            if (V[nvi][nvj]) continue;
            Q.push({nvi, nvj, d + 1});
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << D[i][j] << ' ';
        } std::cout << '\n';
    }
}
