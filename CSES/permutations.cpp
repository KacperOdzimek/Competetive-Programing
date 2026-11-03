#include <bits/stdc++.h>
int main() {
    int n; std::cin >> n;
    if (n > 1 && n <= 3) {
        std::cout << "NO SOLUTION";
        return 0;
    }

    int max_odd = (n % 2 == 0) ? n - 1 : n;
    for (int i = max_odd; i >= 1; i -= 2) {
        std::cout << i << ' ';
    }

    int max_even = (n % 2 == 0) ? n : n - 1;
    for (int i = max_even; i >= 2; i -= 2) {
        std::cout << i << ' ';
    }
}
