#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    int n; ull x; std::cin >> n >> x; std::vector<ull> V(n);
    for (int i = 0; i < n; i++) std::cin >> V[i];
    
    std::vector<ull> P(n); P[0] = V[0];
    for (int i = 1; i < n; i++) P[i] = P[i - 1] + V[i];

    ull ans = 0; for (int i = -1; i < n - 1; i++) {
        ull removed  = i >= 0 ? P[i] : 0;
        ull searched = removed + x;
        ans += std::binary_search(P.begin(), P.end(), searched);
    }
    
    std::cout << ans;
}
