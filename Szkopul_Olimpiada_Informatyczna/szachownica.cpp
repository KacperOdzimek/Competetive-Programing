#include <iostream>
#include <vector>

// 1) zauwazmy ze pole biale mozna polaczyc kostka razem z polem czarnym
//  w szczegolnosci musimy zajac wszystkie pola
//  jest to wiec graf dwudzielny, a zadany problem to problem
//  istnienia skojarzenia doskonalego w grafie dwudzielnym
// 2) konstruujac graf, zakladamy iz numerujemy od lewego gornego rogu
//  wiec sasiedzi k to k - n, k + n, k - 1, k + 1
// 3) tym razem numerujemy od 1

constexpr int max_n = 50 * 50 + 1;
std::vector<int> D[max_n]; // graf dwudzielny
int              P[max_n]; // w drugim kolorze, sparowanie
std::vector<int> B; // pierwszy z kolorow
std::vector<int> C;

int timer = 1;
int vis[max_n];

bool skojarz(int v) {
    vis[v] = timer;

    // drugi kolor
    for (int u : D[v]) {
        // sparuj z soba
        if (!P[u]) {
            P[u] = v;
            return true;
        }
    }

    // przeparuj sasiadow
    for (int u : D[v]) {
        int  vo = P[u];

        if (vis[vo] == timer) continue;
        bool scc = skojarz(vo);

        if (scc) {
            P[u] = v;
            return true;
        }
    }

    return false;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, a, b, c; std::cin >> n >> a >> b >> c;

    auto good = [&](int v) {
        return !(v == a || v == b || v == c);
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int k = (i * n + j); // 0 idx
            int l = k + 1;       // 1 idx

            if (!good(l)) continue;

            if ((i + j) % 2 == 0) { // B
                B.push_back(l);
                if (k - n >= 0     && good(l - n)) D[l].push_back(l - n);
                if (k + n < n * n  && good(l + n)) D[l].push_back(l + n);
                if (k % n != 0     && good(l - 1)) D[l].push_back(l - 1);
                if (k % n != n - 1 && good(l + 1)) D[l].push_back(l + 1);
            } else { // C
                C.push_back(l);
            }
    }

    // sparuj kazde B
    for (int v : B) {
        if (vis[v] == timer) continue;
        timer++; bool scc = skojarz(v);
        if (!scc) {
            std::cout << "NIE\n";
            return 0;
        }
    }

    // sprawdz czy kazde C sparowane
    for (int v : C) {
        if (!P[v]) {
            std::cout << "NIE\n";
            return 0;
        }
    }

    // wypisz
    for (int v : C) {
        std::cout << v << ' ' << P[v] << '\n';
    }
}
