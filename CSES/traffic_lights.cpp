#include <bits/stdc++.h>
using ll = long long;
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    ll x; std::cin >> x; 
    std::multiset<ll>           LENGHTS;    // All ranges lengths
    std::set<std::pair<ll, ll>> RANGES;     // End; Start
    LENGHTS.insert(x); RANGES.insert({x, 0});
    int n; std::cin >> n; while (n--) {
        ll p; std::cin >> p;
        auto itr = RANGES.lower_bound({p, 0}); // Always is
        ll end = itr->first; ll start = itr->second;
        LENGHTS.erase(LENGHTS.find(end - start));
        RANGES.erase(itr);

        LENGHTS.insert(p - start);
        RANGES.insert({p, start});

        LENGHTS.insert(end - p);
        RANGES.insert({end, p});

        std::cout << *LENGHTS.rbegin() << ' ';
    }
}