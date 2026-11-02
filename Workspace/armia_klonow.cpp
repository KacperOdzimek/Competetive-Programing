/*
    Stan (l, d) - liczebnosc armii i drukarki
    moze isc do (l; l)      kosztem a
    moze isc do (l + d; d)  kosztem b
*/

#include <bits/stdc++.h>
using ull = unsigned long long;

ull n, a, b;

struct stan {
    ull koszt;
    ull armia;
    ull drukarka;
};

struct compar {
    bool operator()(const stan& a, const stan& b) const {
        if (a.koszt    != b.koszt)      return a.koszt > b.koszt; // Odwrocone bo priority queue
        if (a.drukarka != b.drukarka)   return a.drukarka > b.drukarka;
        return a.armia > b.armia;
    }
};

using queue = std::priority_queue<stan, std::vector<stan>, compar>;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> a >> b;

    queue Q; Q.push({a, 1, 1});
    ull ans = UINT64_MAX; while (Q.size()) {
        stan s = Q.top(); Q.pop();
        if (s.koszt >= ans) break;
        if (s.armia > n) {
            ans = std::min(ans, s.koszt);
        }
        else {
            if (s.armia != s.drukarka) Q.push({s.koszt + a, s.armia, s.armia});
            Q.push({s.koszt + b, s.armia + s.drukarka, s.drukarka});
        }
    }

    std::cout << ans;
}
