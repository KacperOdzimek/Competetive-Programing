#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    int q; std::cin >> q; while (q--) {
        ull k; std::cin >> k;

        // Erase all elements of length
        ull l = 1; ull c = 10; 
        while (k > (c - c / 10) * l) {
            k -= (c - c / 10) * l;
            c *= 10; l++;
        }

        // Find the number containing the digit
        ull num = (k - 1) / l;
        ull pos = (k - 1) % l;

        ull first = c / 10;
        ull value = first + num;

        // Extract the required digit
        for (ull i = 0; i < l - 1 - pos; i++) {
            value /= 10;
        }

        std::cout << value % 10 << '\n';
    }
}
