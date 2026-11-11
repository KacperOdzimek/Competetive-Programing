#include <bits/stdc++.h>
constexpr int max_val = 100 * 1000 + 1;

int main() {
    int n; std::cin >> n;
    std::bitset<max_val> V;
    V[0] = true; while (n--) {
        int x; std::cin >> x;
        V |= (V << x);
    }
    std::cout << V.count() - 1 << '\n';
    for (auto i = V._Find_next(V._Find_first()); i != V.size(); i = V._Find_next(i)) {
        std::cout << i << ' ';
    }
}