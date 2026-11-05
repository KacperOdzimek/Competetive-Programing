#include <bits/stdc++.h>
using ll = long long;
int main() {
    std::set<ll> C; std::queue<ll> Q;
    int n; std::cin >> n; 
    int ans = 0; while (n--) {
        ll k; std::cin >> k; 
        if (C.find(k) == C.end()) {
            C.insert(k); Q.push(k);
            ans = std::max(ans, (int)C.size());
        }
        else {
            while (Q.front() != k) { C.erase(Q.front()); Q.pop(); } 
            Q.pop(); Q.push(k);
        }
    } std::cout << ans;
}
