#include <bits/stdc++.h>
using ll = long long;
constexpr int max_n = 2500;
constexpr ll  inf_u = LONG_LONG_MAX / 2;

int n, m;
std::vector<std::tuple<int, int, ll>> E;

std::set<int> VISITED;
std::set<int> PRINTED;
bool print_path(int v, const std::vector<int>& prev) {
    if (VISITED.find(v) != VISITED.end()) {
        std::cout << v + 1 << ' '; 
        PRINTED.insert(v);
        return true;
    }
    VISITED.insert(v); 

    bool print = print_path(prev[v], prev);
    if (!print) return false;
    
    std::cout << v + 1 << ' ';
    if (PRINTED.find(v) != PRINTED.end()) {
        return false;
    }
    PRINTED.insert(v);
    return true;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; ll c; std::cin >> x0 >> x1 >> c;
        x0--; x1--; E.push_back({x0, x1, c});
    }

    std::vector<ll>  DIST(n, 0);
    std::vector<int> PREV(n, -1);
    for (int i = 0; i < n - 1; i++) {
        for (auto [x0, x1, c] : E) {
            if (DIST[x1] > DIST[x0] + c) {
                DIST[x1] = DIST[x0] + c;
                PREV[x1] = x0;
            }
        }
    }

    for (auto [x0, x1, c] : E) {
        if (DIST[x1] > DIST[x0] + c) {
            std::cout << "YES\n";
            PREV[x1] = x0;
            print_path(x0, PREV);
            return 0;
        }
    }

    std::cout << "NO\n";
}