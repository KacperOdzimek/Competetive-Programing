#include <bits/stdc++.h>
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; unsigned long long ans = 0; 
    std::queue<int> Q; std::unordered_set<int> S;
    std::cin >> n; while (n--) {
        int x; std::cin >> x; while (S.count(x)) {
            S.erase(Q.front()); Q.pop();
        }
        Q.push(x); S.insert(x); ans += Q.size();
    }
    std::cout << ans;
}
