#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr int max_n = 100000 + 1;

int DSU_COUNT;
int DSU[max_n];

void init(int n) {
    DSU_COUNT = n;
    for (int i = 0; i < n; i++) DSU[i] = -1;
}

int rep(int v) {
    if (DSU[v] < 0) return v;
    return DSU[v] = rep(DSU[v]);
}

void join(int ra, int rb) {
    DSU_COUNT--;

    ra = rep(ra);
    rb = rep(rb);

    if (ra == rb) return;
    if (DSU[ra] > DSU[rb]) std::swap(ra, rb);

    DSU[ra] += DSU[rb];
    DSU[rb] = ra;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, m; std::cin >> n >> m; std::vector<std::tuple<ull, int, int>> E(m);

    init(n);

    for (int i = 0; i < m; i++) {
        int a, b; ull c; std::cin >> a >> b >> c;
        a--; b--; E[i] = {c, a, b};
    } std::sort(E.begin(), E.end());

    ull ans = 0; for (auto [c, a, b] : E) {
        int ra = rep(a); int rb = rep(b);
        if (ra == rb) continue;
        join(ra, rb); ans += c;
    }

    if (DSU_COUNT > 1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    std::cout << ans;
}