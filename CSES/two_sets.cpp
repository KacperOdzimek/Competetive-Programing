#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    ull n; std::cin >> n;

    if (n % 4 == 0 || n % 4 == 3) {
        std::cout << "YES\n";
        std::vector<ull> S1, S2;
        ull start = (n % 4 == 3) ? 0 : 1;
        for (ull i = start; i < n; i += 4) {
            S1.push_back(i); S1.push_back(i + 3);
            S2.push_back(i + 1); S2.push_back(i + 2);
        }

        if (S1.front() == 0) {
            std::cout << S1.size() - 1 << '\n';
            for (int i = 1; i < S1.size(); i++) std::cout << S1[i] << ' ';
        }
        else {
            std::cout << S1.size() << '\n';
            for (int i = 0; i < S1.size(); i++) std::cout << S1[i] << ' ';
        }

        std::cout << '\n' << S2.size() << '\n';
        for (int i = 0; i < S2.size(); i++) std::cout << S2[i] << ' ';
    }
    else {
        std::cout << "NO\n";
    }

    return 0;
}
