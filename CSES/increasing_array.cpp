#include <bits/stdc++.h>
using ull = unsigned long long;

int main() {
    int n; std::cin >> n; ull ans = 0; ull prev = 0;
    for (int i = 0; i < n; i++) {
        ull v; std::cin >> v;
        if (v < prev) {
            ans += prev - v;
            v = prev;
        }
        prev = v;
    }
    std::cout << ans;
}
