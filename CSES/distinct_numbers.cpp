#include <bits/stdc++.h>
int main() {
    int n; std::cin >> n;
    std::set<long long> S; while (n--) {
        long long x; std::cin >> x; S.insert(x);
    } std::cout << S.size();
}