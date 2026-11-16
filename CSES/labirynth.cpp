#include <bits/stdc++.h>
constexpr int max_dim = 1000;

int n, m;
char M[max_dim][max_dim];
bool V[max_dim][max_dim];

struct Prev {
    int x, y;
    char dir;
};

Prev P[max_dim][max_dim];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char moves[] = {'U', 'D', 'L', 'R'};

int main() {
    std::cin >> n >> m;

    std::pair<int, int> start, finish;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> M[i][j];

            if (M[i][j] == 'A') start = {i, j};
            if (M[i][j] == 'B') finish = {i, j};
        }
    }

    std::queue<std::pair<int, int>> q;

    q.push(start);
    V[start.first][start.second] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (std::make_pair(x, y) == finish) break;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= n) continue;
            if (ny < 0 || ny >= m) continue;
            if (M[nx][ny] == '#') continue;
            if (V[nx][ny]) continue;

            V[nx][ny] = true;
            P[nx][ny] = {x, y, moves[k]};

            q.push({nx, ny});
        }
    }

    if (!V[finish.first][finish.second]) {
        std::cout << "NO\n";
        return 0;
    }

    std::string path;

    int x = finish.first;
    int y = finish.second;

    while (std::make_pair(x, y) != start) {
        path += P[x][y].dir;

        int px = P[x][y].x;
        int py = P[x][y].y;

        x = px;
        y = py;
    }

    std::reverse(path.begin(), path.end());

    std::cout << "YES\n";
    std::cout << path.size() << '\n';
    std::cout << path << '\n';
}