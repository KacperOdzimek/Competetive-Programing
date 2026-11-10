#include <bits/stdc++.h>
using ll = long long;
constexpr ll MOD = 1'000'000'000 + 7;
int main() {
    ll n; std::cin >> n; 
    std::vector<ll> W1(n), W2(n); W2[0] = 1;

    std::vector<ll>* currt = &W1;
    std::vector<ll>* other = &W2;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            currt->at(j) = 0;
            
            (currt->at(j) += other->at(j)) %= MOD;
            if (j >= 1) {
                (currt->at(j) += currt->at(j - 1)) %= MOD;
            }

            char c; std::cin >> c; 
            if (c == '*') currt->at(j) = 0;
        }
        std::swap(currt, other);
    }

    std::cout << other->at(n - 1);
}
