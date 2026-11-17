#include <bits/stdc++.h>
constexpr int max_n = 2 * 100000;

int I;
int V[max_n];
int G[max_n];
int C[max_n];

void dfs(int beg) {
    I++; std::stack<int> S; S.push(beg);
    while (!S.empty()) {
        V[S.top()] = I;
        int u = G[S.top()];
        if (V[u] == 0) S.push(u);   // Enter unvisited
        else if (V[u] < I) {        // Cycle from past; Unroll incrementing
            while (!S.empty()) {
                C[S.top()] = C[u] + 1; 
                u = S.top(); S.pop();
            }
        }
        else if (V[u] == I) {       // New cycle; Unroll cycle and then path to cycle
            int cycle_end = u;
            std::vector<int> Cycle;
            while (!S.empty()) {
                u = S.top(); S.pop();
                Cycle.push_back(u);
                if (u == cycle_end) break;
            }
            for (int w : Cycle) C[w] = Cycle.size() - 1;
            while (!S.empty()) {
                C[S.top()] = C[u] + 1; 
                u = S.top(); S.pop();
            }
        }
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; for (int i = 0; i < n; i++) {
        int x; std::cin >> x; x--; G[i] = x;
    }

    for (int i = 0; i < n; i++) {
        if (V[i] == 0) dfs(i);
        std::cout << C[i] + 1 << ' ';
    }
}