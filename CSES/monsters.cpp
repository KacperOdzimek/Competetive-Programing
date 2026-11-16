/*
    We move monsters first in bfs therefore 
    player can only move to fields unreached by monsters
*/

#include <bits/stdc++.h>
constexpr int max_n = 1000;

int  n, m; 
char M[max_n][max_n];
int  T[max_n][max_n];
char S[max_n][max_n];

void collect_path_dfs(int i, int j, std::string& str) {
    char l = S[i][j]; 
    if (l == '\0') return;
    str.push_back(l);
    if (l == 'U') collect_path_dfs(i + 1, j, str);
    if (l == 'D') collect_path_dfs(i - 1, j, str);
    if (l == 'L') collect_path_dfs(i, j + 1, str);
    if (l == 'R') collect_path_dfs(i, j - 1, str);
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::queue<std::tuple<int, int, int, bool, char>> Q;
    std::cin >> n >> m; int Ai, Aj; for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> M[i][j];
            if (M[i][j] == 'A') {Ai = i; Aj = j;}
            if (M[i][j] == 'M') Q.push({i, j, 1, false, '\0'});
        }
    }

    Q.push({Ai, Aj, 1, true, '\0'}); while (!Q.empty()) {
        auto [vi, vj, vt, hero, dir] = Q.front(); Q.pop();
        if (vi < 0 || vi >= n) continue;
        if (vj < 0 || vj >= m) continue;
        if (T[vi][vj] != 0 && T[vi][vj] <= vt) continue;
        if (M[vi][vj] == '#')  continue;
        T[vi][vj] = vt;
    
        if (hero) {
            S[vi][vj] = dir; 
            if (vi == 0 || vj == 0 || vi == n - 1 || vj == m - 1) {
                std::string path; collect_path_dfs(vi, vj, path);
                std::reverse(path.begin(), path.end());
                std::cout << "YES\n" << path.size() << '\n' << path;
                return 0;
            }
        }

        Q.push({vi - 1, vj, vt + 1, hero, 'U'});
        Q.push({vi + 1, vj, vt + 1, hero, 'D'});
        Q.push({vi, vj - 1, vt + 1, hero, 'L'});
        Q.push({vi, vj + 1, vt + 1, hero, 'R'});
    }

    std::cout << "NO";
}