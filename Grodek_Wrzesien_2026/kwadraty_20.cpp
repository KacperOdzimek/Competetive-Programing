#include <bits/stdc++.h>

unsigned long long sqrto(unsigned long long x) {
    unsigned long long prv = -1;
    unsigned long long cur = 1;
    unsigned long long old = 0;
    while (cur != old && cur != prv) {
        prv = old;
        old = cur;
        cur = (cur + x / cur) / 2; 
    }
    return cur;
}

static inline bool solve() {
    unsigned long long x; std::cin >> x;
    if (x > std::pow(10, 18)) return false;
    unsigned long long s = sqrto(x);
    return s * s == x;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int t; std::cin >> t; while (t--) {
        std::cout << (solve() ? "TAK\n" : "NIE\n");
    }
}