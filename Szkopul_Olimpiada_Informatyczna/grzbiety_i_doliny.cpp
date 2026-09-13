#include <bits/stdc++.h>

using ull = unsigned long long;
constexpr int max_n = 1000;

int  n;
ull  W[max_n][max_n];
bool V[max_n][max_n];
int grzbiety, doliny;

constexpr std::pair<int, int> delta[8] = {
    {-1,  1}, {0,  1}, {1,  1},
    {-1,  0},          {1,  0},
    {-1, -1}, {0, -1}, {1, -1}
};

static inline std::pair<int, int> add(const std::pair<int, int>& l, const std::pair<int, int>& r) {
    return {l.first + r.first, l.second + r.second};
}

static inline bool valid(std::pair<int, int> p) {
    if (p.first < 0  || p.first >= n)  return false;
    if (p.second < 0 || p.second >= n) return false;
    return true;
}

void traverse(int vi, int vj) {
    // Dane dla pierwszego pola
    ull w = W[vi][vj];
    bool grzbiet = true;
    bool dolina  = true;

    // Eksploruj reszte regionu
    std::vector<std::pair<int, int>> Q, nQ; 
    Q.push_back({vi, vj}); V[vi][vj] = true;
    while (Q.size()) {
        for (auto v : Q) {
            // Eksloruj sasiadow
            for (int i = 0; i < 8; i++) {
                std::pair<int, int> s = add(v, delta[i]);
                if (!valid(s)) continue;
                ull wd = W[s.first][s.second];
                if (wd == w && !V[s.first][s.second]) {
                    V[s.first][s.second] = true;
                    nQ.push_back(s);
                }
                if (wd > w)  grzbiet = false;
                if (wd < w)  dolina  = false;
            }
        } Q.swap(nQ); nQ.clear();
    }

    // Dolicz jezeli
    if (grzbiet) grzbiety++;
    if (dolina)  doliny++;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0); std::cin >> n;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) std::cin >> W[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (!V[i][j]) traverse(i, j);
    std::cout << grzbiety << ' ' << doliny;
}
