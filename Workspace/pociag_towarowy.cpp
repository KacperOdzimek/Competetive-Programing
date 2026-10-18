/*
    Wagon nie mogl byc odnotowany jezeli po nim pojawiaja
    sie nieistniejace w ciagu Bajtka elementy ciagu Bitka.

    Wagon nie mogl tez byc odnotowany jezeli na jego prefiksie (ciag Bajtka)
    Nie pojawiaja sie wszystkie wagony z ciagu Bitka
*/

#include <bits/stdc++.h>
constexpr int max_d = 300'000 + 3;

int k;
int n; int N[max_d];
int m; int M[max_d];

int IM[max_d];
int IN[max_d];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n >> m >> k;
    for (int i = 0; i < n; i++) std::cin >> N[i];
    for (int i = 0; i < m; i++) std::cin >> M[i];

    // O(mn) oblicz ktore najdalej indeks w M (+1)
    // Moze zajac indeks w N od lewej czytajac
    for (int im = 0; im < m; im++) {
        int idx = im + 1; int prf = 0;
        for (int in = 0; in < n; in++) {
            int prev = IM[in];
            if (prf + 1 >= idx && N[in] == M[im]) IM[in] = idx;
            prf = std::max(prf, prev);
        }
    }

    // for (int i = 0; i < n; i++) std::cout << IM[i] << ' ';
    // std::cout << std::flush << '\n';
    
    // Zeby pole moglo spelniac warunek musi ono byc elementem
    // Ciagu malejacego: m, m-1, m-2, ..., 1
    // Ciag musi malec dokladnie o jeden (nie mozna ominac elementow)
    std::bitset<max_d> S;
    for (int in = n - 1; in >= 0; in--) {
        if (IM[in] == m || S[IM[in] + 1]) { // Poczatek lub kolejny element
            if (IM[in] == 0) continue;      // Ten element jest niemozliwy
            S.set(IM[in], true);            // Widziano taka pozycje w ramach ciagu
            IN[in] = 1;
        }
    }

    for (int i = 0; i < n; i++) std::cout << IN[i] << ' ';
}

/*
8 2 1000
5 4 4 5 4 5 5 4
4 5
*/
