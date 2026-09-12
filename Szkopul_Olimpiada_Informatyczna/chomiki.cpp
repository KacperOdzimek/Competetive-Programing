// D = suma dlugosci imion
// W O(n*D) liczymy prefikso-sufiksy par imion (KMP), a nastepnie
// w polpierscieniu (min,+) potegujemy macierz przejsc, zeby
// znalezc optymalny "cykl" doklejania imion, maksymalizujacy
// pokrycie wzgledem dlugosci tekstu.

#include <bits/stdc++.h>

// Config
constexpr int max_n = 200;
constexpr long long inf = 2'000'000'000'000'000'000LL;

// Raw Input
int n; long long m;
std::string imiona[max_n];

// Prefikso-Sufiksy
std::vector<int> FT[max_n];

// Macierze
struct matrix {
    long long v[max_n][max_n];
};
matrix SP0; // Zero krawedzi pokonanych

static inline std::vector<int> ft(const std::string& p) {
    int lp = (int)p.size();
    std::vector<int> fail(lp, 0);
    for (int i = 1; i < lp; i++) {
        int j = fail[i - 1];
        while (j > 0 && p[i] != p[j]) j = fail[j - 1];
        if (p[i] == p[j]) j++;
        fail[i] = j;
    }
    return fail;
}

// Overlap p na koniec s
static inline int overlap(int s, int p) {
    int lp = (int)imiona[p].size();
    int j = 0;
    for (char c : imiona[s]) {
        while (j > 0 && c != imiona[p][j]) j = FT[p][j - 1];
        if (c == imiona[p][j]) j++;
        if (j == lp) {
            j = FT[p][j - 1];
        }
    }
    return j;
}

// Pomnoz macierze O(n^2)
static inline void dot(matrix& tar, const matrix& a, const matrix& b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tar.v[i][j] = inf;
            for (int v = 0; v < n; v++) {
                if (a.v[i][v] >= inf || b.v[v][j] >= inf) continue; // ochrona przed przepelnieniem
                tar.v[i][j] = std::min(tar.v[i][j], a.v[i][v] + b.v[v][j]);
            }
        }
    }
}

// Szybko potenguj macierze log(pow)
static inline matrix qpow(matrix base, long long pow) {
    matrix res;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res.v[i][j] = (i == j) ? 0 : inf;

    while (pow > 0) {
        if (pow % 2 == 1) {
            matrix temp;
            dot(temp, res, base);
            res = temp;
        }
        matrix temp_base;
        dot(temp_base, base, base);
        base = temp_base;
        pow /= 2;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);

    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> imiona[i];
        FT[i] = ft(imiona[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            SP0.v[i][j] = (long long)imiona[j].size() - overlap(i, j);
        }
    }

    matrix SPMM1 = qpow(SP0, m - 1);
    long long ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (SPMM1.v[i][j] >= inf) continue;
            ans = std::min(ans, (long long)imiona[i].size() + SPMM1.v[i][j]);
        }
    }

    std::cout << ans;
}