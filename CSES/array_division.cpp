#include <bits/stdc++.h>
using ull = unsigned long long;

bool check(const std::vector<ull>& V, int k, ull m) {
    ull c = 0; int d = 0;
    for (ull v : V) {
        if (v > m) return false;
        if (c + v > m) {d++; c = 0;}
        c += v;
    }
    return d < k;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, k; std::cin >> n >> k; std::vector<ull> V(n);
    for (int i = 0; i < n; i++) std::cin >> V[i];

    ull l = 0; ull h = 1'000'000'000'000'000'000 + 1;
    ull ans = h; while (l < h) {
        ull m = l + (h - l) / 2;
        if (check(V, k, m)) {
            ans = std::min(ans, m);
            h = m;
        }
        else {
            l = m + 1;
        }
    }

    std::cout << ans;
}