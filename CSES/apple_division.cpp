#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    int n = 0; ull sum = 0; std::cin >> n; 
    std::vector<ull> V(n); for (int i = 0; i < n; i++) std::cin >> V[i];
    ull ans = UINT64_MAX; for (int i = 0; i < (1 << n); i++) {
        ull a = 0; ull b = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) a += V[j];
            else b += V[j];
        }
        if (a < b) std::swap(a, b);
        ans = std::min(ans, a - b);
    } std::cout << ans;
}
