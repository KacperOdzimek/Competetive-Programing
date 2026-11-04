#include <bits/stdc++.h>
using ll = long long;
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; ll x; std::cin >> n >> x; std::vector<ll> C(n);
    for (int i = 0; i < n; i++) std::cin >> C[i];
    std::sort(C.begin(), C.end());

    int ans = 0; int i = 0; int j = n - 1;
    while (i <= j) {
        ll min = C[i]; ll max = C[j];
        if (min + max <= x) {
            ans++; i++; j--;
        }
        else {
            ans++; j--;
        }
    }
    std::cout << ans;
}

/*
10 2
1 1 1 1 1 1 1 1 1 1
*/
