#include <bits/stdc++.h>

int main() {
    int n; std::cin >> n; 
    std::vector<std::pair<int, int>> V(n); for (int i = 0; i < n; i++) {
        std::cin >> V[i].first; V[i].second = i;
    }; std::sort(V.begin(), V.end());
    int pos = n; int ans = 0; for (auto [v, i] : V) {
        if (i < pos) ans++; 
        pos = i;
    }
    std::cout << ans;
}
