#include <bits/stdc++.h>
using ull = unsigned long long;

int main() {
    int t; std::cin >> t;
    while (t--) {
        ull y, x; std::cin >> y >> x;
        ull l = std::max(x, y); // Layer
        ull s = l * l;          // Base square

        if (l % 2 == 1) {
            s -= (y - 1);
            s -= (l - x);
        }
        else {
            s -= (l - y);
            s -= (x - 1);
        }

        std::cout << s << '\n';
    }
}
