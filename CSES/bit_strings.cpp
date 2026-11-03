#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr ull mod = 1'000'000'000 + 7;
int main() {
    ull n; std::cin >> n;
    ull a = 1; while (n--) (a *= 2) %= mod;
    std::cout << a;
}
