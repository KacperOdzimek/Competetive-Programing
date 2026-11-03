#include <bits/stdc++.h>

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    unsigned long long n; std::cin >> n; do {
        std::cout << n << ' ';
        if (n == 1) break;
        if (n % 2)  n = n * 3 + 1;
        else        n = n / 2;
    } while (true);
}