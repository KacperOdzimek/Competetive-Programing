#include <bits/stdc++.h>
using ll = long long;
int main() {
    int t; std::cin >> t;  while (t--) {
        ll a, b; std::cin >> a >> b;
        if ((a + b) % 3 == 0 && 
            a <= 2 * b && b <= 2 * a) {
            std::cout << "YES\n";
        } 
        else {
            std::cout << "NO\n";
        }
    }
}
