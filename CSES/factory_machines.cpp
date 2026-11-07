#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr int max_n = 2 * 100000 + 1;

int n; ull t;
ull V[max_n];

bool test(ull x) {
    ull c = 0; for (int i = 0; i < n; i++) {
        c += x / V[i]; if (c >= t) return true;
    } return c >= t;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> t; for (int i = 0; i < n; i++) std::cin >> V[i];

    ull l = 0; ull h = 1'000'000'000'000'000'000;
    ull ans = h; while (l < h) {
        ull m = l + (h - l) / 2;
        if (test(m)) {
            ans = std::min(ans, m);
            h = m;
        }
        else {
            l = m + 1;
        }
    }

    std::cout << ans;
}