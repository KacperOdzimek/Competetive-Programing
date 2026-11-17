#include <bits/stdc++.h>
constexpr int max_n = 100000;

int n, m;
std::vector<int> G[max_n];

bool VIS[max_n];
bool CUR[max_n];

int RECORD_TILL;
std::vector<int> ANS;

// Return flags:
// 0 - No cycle; Discover
// 1 - On cycle; Unroll and save
// 2 - Before cycle; Unroll
int dfs(int v) {   
    if (CUR[v]) { // CYCLE!!!
        ANS.push_back(v);
        RECORD_TILL = v;
        return 1;
    }
    if (VIS[v]) return 0; // Went further in past, no cycle

    VIS[v] = true; CUR[v] = true;
    for (int u : G[v]) {
        int flag = dfs(u);
        if (flag == 0) continue;
        if (flag == 2) return 2;
        ANS.push_back(v);
        return (v == RECORD_TILL) ? 2 : 1;
    }

    CUR[v] = false;
    return 0;   // No cycle by default
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1;
        x0--; x1--; G[x0].push_back(x1);
    }

    for (int i = 0; i < n; i++) {
        if (VIS[i]) continue;
        dfs(i); if (ANS.size()) goto _answer;
    }

    std::cout << "IMPOSSIBLE\n"; return 0;

_answer: 
    std::cout << ANS.size() << '\n';
    std::reverse(ANS.begin(), ANS.end());
    for (int i : ANS) std::cout << i + 1 << ' ';
}
