#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// 1) stan w wiercholku to obrot samochodu i dystans
// 2) obrot ogranicza nasze mozliwosci ruchu
// 3) przy takich ograniczeniach robimy BFS

struct thread {
    int x, y;
    int dir; // 0=up, 1=right, 2=down, 3=left
};

int xs, ys;
bool tile[100][100];

int ax, ay;
int bx, by;

// odwiedzone [x][y][dir]
bool V[100][100][4]; 

// poprzedni
thread parent_thread[100][100][4];

// offsety
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool valid_coord(int x, int y) {
    return x >= 0 && x < xs && y >= 0 && y < ys;
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

    std:: cin >> xs >> ys;
    for (int i = 0; i < xs; i++) {
        std::string row; std::cin >> row;
        for (int j = 0; j < ys; j++) {
            tile[i][j] = (row[j] == '1'); // 1 = zablokowane
        }
    }

    std::cin >> ax >> ay;
    ax--; ay--;

    std::cin >> bx >> by;
    bx--; by--;

    if (tile[ax][ay] || tile[bx][by]) {
        std::cout << "NIE\n";
        return 0;
    }

    std::queue<thread> Q;

    // startujemy we wszystkich 4 kierunkach
    for (int d = 0; d < 4; d++) {
        V[ax][ay][d] = true;
        parent_thread[ax][ay][d] = {-1, -1, -1};
        Q.push({ax, ay, d});
    }

    thread end_thread = {-1, -1, -1};

    while (!Q.empty()) {
        thread s = Q.front();
        Q.pop();

        if (s.x == bx && s.y == by) {
            end_thread = s;
            break;
        }

        // mozliwe ruchy:
        // 1. prosto
        // 2. w prawo (dir+1)%4
        int moves[2] = { s.dir, (s.dir + 1) % 4 };

        for (int m = 0; m < 2; m++) {
            int ndir = moves[m];
            int nx = s.x + dx[ndir];
            int ny = s.y + dy[ndir];
            if (valid_coord(nx, ny) && !tile[nx][ny] && !V[nx][ny][ndir]) {
                V[nx][ny][ndir] = true;
                parent_thread[nx][ny][ndir] = {s.x, s.y, s.dir};
                Q.push({nx, ny, ndir});
            }
        }
    }

    if (end_thread.x == -1) {
        std::cout << "NIE\n";
        return 0;
    }

    // odtwarzanie ścieżki
    std::vector<std::pair<int,int>> path;

    thread cur = end_thread;

    while (cur.x != -1) {
        path.push_back({cur.x, cur.y});
        thread p = parent_thread[cur.x][cur.y][cur.dir];
        cur = {p.x, p.y, p.dir};
    }

    std::reverse(path.begin(), path.end());

    std::cout << path.size() << "\n";
    for (auto &p : path) {
        std::cout << p.first + 1 << " " << p.second + 1 << "\n";
    }

    return 0;
}
