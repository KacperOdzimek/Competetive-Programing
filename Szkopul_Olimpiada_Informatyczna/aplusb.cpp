#include <iostream>

using ull = unsigned long long;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int t; std::cin >> t;
    while (t--) {
        ull a, b; std::cin >> a >> b;
        std::cout << (a + b) << '\n';
    }
}
