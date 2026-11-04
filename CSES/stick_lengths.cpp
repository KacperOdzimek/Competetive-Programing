#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    int n; std::cin >> n;
    ull longer = 0; std::vector<ull> V(n); while (n--) {
        std::cin >> V[n]; longer += V[n];
    } std::sort(V.begin(), V.end());
    ull ans = ULLONG_MAX; ull shorter = 0; for (int i = 0; i < V.size(); i++) {
        longer -= V[i];
        ull target       = V[i];
        ull shorter_cost = i * target - shorter;
        ull longer_cost  = longer - (V.size() - i - 1) * target;
        ans = std::min(ans, shorter_cost + longer_cost);
        shorter += V[i];
    }
    std::cout << ans;
}