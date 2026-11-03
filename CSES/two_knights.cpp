#include <bits/stdc++.h>
using ll = long long;
int main() {
    ll n; std::cin >> n;
    for (ll k = 1; k <= n; k++) {
        ll total = k * k * (k * k - 1) / 2;
        ll attacking = 4 * (k - 1) * (k - 2);
        std::cout << total - attacking << '\n';
    }
}
