/*
    Oplaca sie odciac przeciwnika od pol, zeby ograniczyc liczbe jego rochow.
    Dlatego gracze beda "biec do siebie" zeby jak najszybciej sie zetknac.
    Wowczas wygrywa gracz ktory w swojej czesci drzewa ma wiecej pol (lub gracz 2 jezeli rowno).
    Gracz pierwszy wygra jezeli zerezerwuje sobie wiecej niz polowe drzewa, tj centroid, lub oba centroidy.

    O(n log n) - budowa lca
    O(n)       - poznanie centroidow
    O(log n)   - sprawdzenie pary (a, b)
*/

#include <bits/stdc++.h>

constexpr int max_n = 500'000;
constexpr int log_n = 19;

// ===========================
// Drzewo

int              n;
std::vector<int> T[max_n];

// ===========================
// LCA

int LCA_D[max_n];
int LCA_U[max_n][log_n];

void lca_build(int v, int p, int d) {
    LCA_D[v] = d;

    LCA_U[v][0] = p; for (int i = 1; i < log_n; i++) {
        LCA_U[v][i] = LCA_U[LCA_U[v][i - 1]][i - 1];
    }

    for (int u : T[v]) {
        if (u == p) continue;
        lca_build(u, v, d + 1);
    }
}

int lca_get(int v, int u) {
    if (LCA_D[v] > LCA_D[u]) std::swap(v, u);

    for (int i = log_n - 1; i >= 0; i--) {
        if (LCA_D[LCA_U[u][i]] < LCA_D[v]) continue; // Za duzy skok
        u = LCA_U[u][i];
    }

    if (v == u) return v;

    for (int i = log_n - 1; i >= 0; i--) {
        int nv = LCA_U[v][i];
        int nu = LCA_U[u][i];
        if (nv == nu) continue;
        v = nv; u = nu;
    }

    return LCA_U[v][0];
}

int lca_dist(int v, int u) {
    return LCA_D[v] + LCA_D[u] - 2 * LCA_D[lca_get(v, u)];
}

// ===========================
// Centroid

int              CENT_S[max_n];
std::vector<int> CENT_V;

void cent_subtree(int v, int p) {
    CENT_S[v] = 1;
    for (int u : T[v]) {
        if (u == p) continue;
        cent_subtree(u, v);
        CENT_S[v] += CENT_S[u];
    }
}

std::vector<int> cent_find(int v, int p) {
    for (int u : T[v]) {
        if (u == p) continue;
        if (CENT_S[u] > n / 2) return cent_find(u, v);
    }

    std::vector<int> res = {v};

    if (n % 2 == 0 && p != v && n - CENT_S[v] == n / 2) res.push_back(p);

    for (int u : T[v]) {
        if (u == p) continue;
        if (n % 2 == 0 && CENT_S[u] == n / 2) res.push_back(u);
    }

    return res;
}

void cent_build() {
    cent_subtree(0, 0);
    CENT_V = cent_find(0, 0);
}

// ===========================
// Main

bool sprawdz(int a, int b) {
    if (a == b) return false;
    if (CENT_V.size() == 1) {
        return lca_dist(a, CENT_V[0]) <= lca_dist(b, CENT_V[0]);
    }
    else {
        int a0 = lca_dist(a, CENT_V[0]);
        int a1 = lca_dist(a, CENT_V[1]);
        int b0 = lca_dist(b, CENT_V[0]);
        int b1 = lca_dist(b, CENT_V[1]);
        if (a0 < a1 && b0 < b1) return a0 <= b0;
        if (a1 < a0 && b1 < b0) return a1 <= b1;
        if (a0 > a1) std::swap(a0, a1);
        if (b0 > b1) std::swap(b0, b1);
        return a0 < b0; // Gracz pierwszy zajmuje blizszy mu centroid szybciej, o conajmniej jeden ruch, moze wziac tez drugi
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n; for (int i = 0; i < n - 1; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        T[x0].push_back(x1); T[x1].push_back(x0);
    } lca_build(0, 0, 0); cent_build();

    int sa, sb, q; std::cin >> sa >> sb >> q;
    std::vector<int> A; while (sa--) { A.push_back(0); std::cin >> A.back(); A.back()--; }
    std::vector<int> B; while (sb--) { B.push_back(0); std::cin >> B.back(); B.back()--; }

    int sum = 0; for (int a : A) for (int b : B) if (sprawdz(a, b)) sum++;
    std::cout << sum;
}

/*
6
1 2
2 3
3 4
3 5
5 6
2 2 0
1 2
5 6
*/