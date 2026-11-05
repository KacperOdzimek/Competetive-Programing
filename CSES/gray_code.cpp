#include <bits/stdc++.h>
int main() {
    int n; std::cin >> n;
    for (int i = 0; i < (1 << n); i++) {
        int c = i ^ (i >> 1);
        for (int i = 0; i < n; i++) {
            std::cout << (c & (1 << i) ? '1' : '0');
        } std::cout << '\n';
    }
}
