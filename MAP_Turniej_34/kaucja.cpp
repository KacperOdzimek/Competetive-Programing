#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    ull n; std::cin >> n; ull zl = 0; ull gr = 0; while (n--) {
        char R; std::cin >> R; 
        if (R == 'P') gr += 50;
        if (R == 'M') gr += 50;
        if (R == 'S') zl += 1;
        if (gr == 100) {
            zl++; gr = 0;
        }
    }
    std::cout << zl << ".";
    if (gr == 0) std::cout << "00";
    else std::cout << "50";
}