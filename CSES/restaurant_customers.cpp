#include <bits/stdc++.h>
using ll = long long;
int main() {
    int n; std::cin >> n;
    std::vector<std::pair<ll, bool>> E;
    while (n--) {
        ll a, b; std::cin >> a >> b;
        E.push_back({a, true}); E.push_back({b, false});
    } std::sort(E.begin(), E.end());
    int ans = 0; int ong = 0; for (auto e : E) {
        ong += e.second ? 1 : -1;
        ans = std::max(ans, ong);
    }
    std::cout << ans;
}