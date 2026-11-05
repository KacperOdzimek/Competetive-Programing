#include <bits/stdc++.h>

std::string s;
bool vis[9][9];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

char dirs[] = {'U', 'D', 'L', 'R'};
int  ans = 0;

void dfs(int y, int x, int step) {
    if (y == 7 && x == 1) {
        if (step == 48) ans++;
        return;
    }

    if (vis[y-1][x] && vis[y+1][x] && !vis[y][x-1] && !vis[y][x+1]) return;
    if (vis[y][x-1] && vis[y][x+1] && !vis[y-1][x] && !vis[y+1][x]) return;
    if (step == 48) return;
    
    for (int d = 0; d < 4; d++) {
        if (s[step] != '?' && s[step] != dirs[d]) continue;
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (vis[ny][nx]) continue;
        vis[ny][nx] = true;
        dfs(ny, nx, step + 1);
        vis[ny][nx] = false;
    }
}

int main() {
    std::cin >> s;

    for (int i = 0; i < 9; i++) {
        vis[0][i] = true;
        vis[8][i] = true;
        vis[i][0] = true;
        vis[i][8] = true;
    }

    vis[1][1] = true;
    dfs(1, 1, 0);
    std::cout << ans << '\n';
}
