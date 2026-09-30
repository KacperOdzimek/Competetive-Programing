#include <bits/stdc++.h>
constexpr int max_n = 200;

int B[max_n];
int C[max_n];
int I[max_n];

bool dfs(int v, int k) {
    if (k == 0) return true;
    if (v < 0) return false;

    int maxTake = std::min(k / B[v], C[v]);
    for (int cnt = maxTake; cnt >= 0; cnt--) {
        I[v] = cnt; if (dfs(v - 1, k - cnt * B[v])) return true;
    }

    I[v] = 0; return false;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> B[i];
    for (int i = 0; i < n; i++) std::cin >> C[i];

    int k; std::cin >> k;
    dfs(n - 1, k);

    int sum = 0; for (int i = 0; i < n; i++) sum += I[i];
    std::cout << sum << '\n'; for (int i = 0; i < n; i++) std::cout << I[i] << ' ';
}
