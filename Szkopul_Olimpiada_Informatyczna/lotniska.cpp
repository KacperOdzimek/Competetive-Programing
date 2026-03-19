#include <iostream>
#include <algorithm>
#include <vector>

constexpr int max_n = 500;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0); 

    int n; std::cin >> n;
    std::vector<std::pair<int, int>> L(n);

    for (int i = 0; i < n; i++) {
        auto& l = L[i]; std::cin >> l.first; l.second = i;
    }

    std::sort(L.begin(), L.end());

    std::vector<std::pair<int, int>> E;
    while (L.back().first != 0) {
        int j = L.size() - 2;

        while (L.back().first && j >= 0) {
            if (L[j].first == 0) {
                j--; continue;
            }

            E.push_back({L.back().second, L[j].second});
            L.back().first--; L[j].first--;

            j--;
        }

        std::sort(L.begin(), L.end());
    }

    for (auto e : E) std::cout << (e.first + 1) << ' ' << (e.second + 1) << '\n';
}
