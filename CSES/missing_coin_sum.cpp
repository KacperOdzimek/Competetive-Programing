#include <bits/stdc++.h>
using ll = long long;
int main() {
    int n; std::cin >> n;
    std::vector<ll> coins(n);

    for (int i = 0; i < n; i++) {
        std::cin >> coins[i];
    }

    sort(coins.begin(), coins.end());

    ll missing = 1;
    for (ll coin : coins) {
        if (coin > missing) break;
        missing += coin;
    }

    std::cout << missing << '\n';
}
