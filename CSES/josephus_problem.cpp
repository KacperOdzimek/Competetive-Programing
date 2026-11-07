#include <bits/stdc++.h>
constexpr int max_n = 2 * 100000;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; std::bitset<max_n> B;
    int p = 0; bool one_skipped = false; int r = 0; while (r != n) {
        if (B[p]) p++;
        else {
            if (one_skipped) {
                B[p] = true; r++;
                std::cout << (p + 1) << ' ';
            }
            p++; one_skipped = !one_skipped;
        }
        p %= n;
    }
}
