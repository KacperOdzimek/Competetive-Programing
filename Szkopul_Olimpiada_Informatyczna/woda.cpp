/*
    1) Poziom wody w polu = max(H, najnizszy poziom sasiada), liczony od brzegu (Dijkstra)
    2) Brzeg trzyma wode na poziomie swojej wysokosci
*/

#include <bits/stdc++.h>

/*
    Dane
*/

constexpr char  max_dim = 100;
constexpr short max_num = 10'000;

int     n, m;
short   H[max_dim][max_dim];

/*
    Arytmetyka
*/

using pos = std::pair<char, char>;

pos operator+(pos a, pos b) {
    return {a.first + b.first, a.second + b.second};
}

const std::vector<pos> dirs = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

static inline bool ok(pos a) {
    if (a.first < 0  || a.first  >= n) return false;
    if (a.second < 0 || a.second >= m) return false;
    return true;
}

template<class TA>
static inline auto& at(TA& f, pos p) {
    return f[p.first][p.second];
}

/*
    Dijkstra od brzegu
*/

short P[max_dim][max_dim];      // Poziom wody w polu
bool  VIS[max_dim][max_dim];    // Czy poziom jest juz ostateczny

using state = std::pair<short, pos>;    // (poziom, pole)

static inline bool on_border(pos v) {
    return v.first == 0 || v.first == n - 1 || v.second == 0 || v.second == m - 1;
}

/*
    Logika
*/

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n >> m;
    std::priority_queue<state, std::vector<state>, std::greater<state>> Q;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> H[i][j];
        }
    }

    // Pola brzegowe - woda nie moze stac wyzej niz ich wysokosc
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pos v = {i, j};
            if (!on_border(v)) continue;
            at(P, v) = at(H, v);
            at(VIS, v) = true;
            Q.push({at(P, v), v});
        }
    }

    // Zawsze rozlewamy z najnizszego znanego poziomu
    while (Q.size()) {
        auto [lvl, v] = Q.top(); Q.pop();
        for (auto d : dirs) {
            pos u = v + d;
            if (!ok(u) || at(VIS, u)) continue;
            at(VIS, u) = true;
            at(P, u) = std::max(lvl, at(H, u));
            Q.push({at(P, u), u});
        }
    }

    int score = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            score += at(P, {i, j}) - at(H, {i, j});
        }
    }

    std::cout << score << '\n';
}
