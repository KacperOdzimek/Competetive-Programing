#include <bits/stdc++.h>
constexpr int max_n = 2 * 100000 + 1;
bool W[max_n];

int main() {
    int n; std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x; std::cin >> x; W[x] = true; 
    }

    for (int i = 1; i <= n; i++) {
        if (!W[i]) {
            std::cout << i;
            break;
        }
    }
}
