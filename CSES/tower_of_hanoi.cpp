#include <bits/stdc++.h>

std::vector<std::pair<int, int>> M;
void hanoi(int n, int from, int aux, int to) {
    if (n == 0) return;
    hanoi(n - 1, from, to, aux);
    M.push_back({from, to});
    hanoi(n - 1, aux, from, to);
}

int main() {
    int n; std::cin >> n;
    hanoi(n, 1, 2, 3);
    std::cout << M.size() << '\n';
    for (auto [x, y] : M) std::cout << x << ' ' << y << '\n';
}
