/*
    Dojscie mrowek do wiercholka zajmie n tur
    Bedzie to odleglosc najblizszej mrowki do rozgalezienia
*/

#include <bits/stdc++.h>
constexpr short max_n = 5001; // Max wierzcholkow
constexpr short max_e = 10000;// Max krawedzi
constexpr short max_k = 1001; // Max mrowek

// Skompresowane drzewo

short HD[max_n];    // Edge Head
short TO[max_e];    // Edge To
short NE[max_e];    // Next edge
short EC = 0;       // Edge count

void add_edge(int a, int b) {
    TO[EC] = b;
    NE[EC] = HD[a];
    HD[a] = EC++;
}

short M[max_n];  // Mrowka w wierzcholku
short P[max_k];  // Pozycja mrowki
short W[max_k];  // Wynik   mrowki

int tin[max_n], tout[max_n], timer_;

short D[max_n];
std::vector<short> Q, nQ;
void skieruj(short v, short p) {
    D[v] = p;
    tin[v] = timer_++;
    if (M[v]) {
        tout[v] = timer_;
        Q.push_back(v);
        return;
    }
    for (int e = HD[v]; e != -1; e = NE[e]) {
        int u = TO[e]; if (u != p) skieruj(u, v);
    }
    tout[v] = timer_;
}

int vitr;
int visi[max_n];
short srcu[max_n];
void porusz() {
    vitr++; nQ.clear(); for (short v : Q) {
        short p = D[v];
        if (visi[p] == vitr) continue;
        visi[p] = vitr;

        short m = INT16_MAX;
        short s = 0;
        for (int e = HD[p]; e != -1; e = NE[e]) {
            int u = TO[e]; if (M[u] && M[u] < m) { m = M[u]; s = u; }
        }
        nQ.push_back(p); srcu[p] = s;
    }

    // Aplikuj zmiany
    for (short p : nQ) {
        M[p] = M[srcu[p]];
        M[srcu[p]] = 0;
        P[M[p]] = p;
    }

    // Nowy front: tylko te, które nie mają przodka w nQ
    std::sort(nQ.begin(), nQ.end(), [](short a, short b) { return tin[a] < tin[b]; });
    Q.clear();
    int end = -1;
    for (short p : nQ) {
        if (tin[p] < end) continue;   // zablokowana przez mrówkę wyżej
        Q.push_back(p);
        end = tout[p];
    }
}

void symuluj(short v) {
    Q.clear(); nQ.clear(); timer_ = 0;
    skieruj(v, v);
    while (!M[v]) porusz();
    W[M[v]]++;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::fill(HD, HD + max_n, -1);

    // Laduj drzewo
    short n; std::cin >> n; for (short i = 0; i < n - 1; i++) {
        short a, b; std::cin >> a >> b;
        add_edge(a, b); add_edge(b, a);
    }

    // Laduj mrowki
    short k; std::cin >> k; for (short i = 1; i <= k; i++) {
        short a; std::cin >> a; M[a] = i; P[i] = a;
    }

    // Laduj biedronke
    short l; std::cin >> l; while (l--) {
        short a; std::cin >> a; symuluj(a);
    }

    // Odpowiedz
    for (short i = 1; i <= k; i++) {
        std::cout << P[i] << ' ' << W[i] << '\n';
    }
}
