#include <bits/stdc++.h>
using ull = unsigned long long;

constexpr int max_n = 2 * 100000 + 1;
constexpr int log_n = 64;

int JUMP[max_n][log_n];
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, q; std::cin >> n >> q; for (int i = 1; i <= n; i++) std::cin >> JUMP[i][0];
    for (int l = 1; l < log_n; l++) {
        for (int i = 1; i <= n; i++) {
            int my = JUMP[i] [l - 1];
            int th = JUMP[my][l - 1];
            JUMP[i][l] = th;
        }
    }
    while (q--) {
        int i; ull d; std::cin >> i >> d;
        for (int l = log_n - 1; l >= 0; l--) {
            ull bit = 1ULL << l;
            ull cmm = d & bit;
            if (!cmm) continue;
            i = JUMP[i][l];
        }
        std::cout << i << '\n';
    }
}