#include <bits/stdc++.h>
using ull = long long;
constexpr int log_n = 1 << 20;

ull T[log_n * 2];
void update(int pos, ull val) {
    pos += log_n; while (pos) {T[pos] = std::max(T[pos], val); pos /= 2;}
}
ull query(int beg, int end) {
    beg += log_n; end += log_n; 
    ull ans = 0; while (beg < end) {
        if (beg & 1) ans = std::max(ans, T[beg++]);
        if (end & 1) ans = std::max(ans, T[--end]);
        beg /= 2; end /= 2;
    } return ans;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; std::vector<std::tuple<ull, ull, ull>> P(n);

    std::map<ull, int> SC; for (int i = 0; i < n; i++) {
        ull a, b, p; std::cin >> a >> b >> p; P[i] = {a, b, p};
        SC.insert({a, 0}); SC.insert({b, 0});
    }

    int v = 1; for (auto& [k, i] : SC) i = v++;
    for (auto& [a, b, p] : P) {a = SC[a]; b = SC[b];}
    std::sort(P.begin(), P.end());

    for (auto [a, b, p] : P) {
        ull prefix = query(0, a);
        update(b, prefix + p);
    }

    std::cout << T[1];
}
