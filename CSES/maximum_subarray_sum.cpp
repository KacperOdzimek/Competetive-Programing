#include <bits/stdc++.h>
using ll = long long;
int main() {
    int n; std::cin >> n;
    ll ans = LLONG_MIN, cur = 0;
    for (int i = 0; i < n; i++) {
        ll x; std::cin >> x;
        cur = std::max(x, cur + x);
        ans = std::max(ans, cur);
    }
    std::cout << ans;
}
