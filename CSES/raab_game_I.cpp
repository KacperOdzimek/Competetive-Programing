#include <bits/stdc++.h>

void solve() {
    int n, a, b; std::cin >> n >> a >> b;
    if (a + b > n || (a == 0) != (b == 0)) {
        std::cout << "NO\n"; return;
    }

    std::cout << "YES\n";
    for (int i = 1; i <= n; i++) std::cout << i << " ";
    std::cout << "\n";

    int c = n - a - b;
    for (int i = 1; i <= c; i++)         std::cout << i << " "; // First c cards result in draws
    for (int i = c + a + 1; i <= n; i++) std::cout << i << " "; // First player loses b rounds
    for (int i = c + 1; i <= c + a; i++) std::cout << i << " "; // First player wins a rounds
    std::cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int t; std::cin >> t; while (t--) solve();
}
