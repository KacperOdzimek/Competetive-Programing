#include <bits/stdc++.h>
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; int k; std::cin >> n >> k; 
    std::deque<int> V; V.resize(n); while (n--) V[n] = (n + 1);
    int pos = 0; while (V.size()) {
        pos += k; pos %= V.size();
        auto itr = V.begin() + pos;
        std::cout << *itr << ' ';
        V.erase(itr);
    }
}
