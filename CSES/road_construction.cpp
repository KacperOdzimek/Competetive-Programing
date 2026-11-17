#include <bits/stdc++.h>
constexpr int max_n = 100000;

int DSC;
int DSM;
int DSU[max_n];
void init(int n) {
    DSC = n; DSM = -1;
    for (int i = 0; i < n; i++) DSU[i] = -1;
}
int rep(int v) {
    if (DSU[v] < 0) return v;
    DSU[v] = rep(DSU[v]);
    return DSU[v];
}
void join(int ra, int rb) {
    ra = rep(ra); rb = rep(rb);
    if (ra == rb) return;
    if (DSU[ra] < DSU[rb]) std::swap(ra, rb);   // If ra is not bigger (more negative)
    DSU[ra] += DSU[rb];
    DSU[rb] = ra; DSC--;
    DSM = std::min(DSM, DSU[ra]);
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, m; std::cin >> n >> m; init(n); while (m--) {
        int a, b; std::cin >> a >> b; a--; b--;
        join(a, b); std::cout << DSC << ' ' << -DSM << '\n';
    }
}