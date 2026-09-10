#include <bits/stdc++.h>

// Kazda skarbonka i ma dokladnie jeden klucz do niej -> parent[i] = skarbonka,
// ktora trzeba otworzyc, zeby zdobyc klucz i (a wiec zeby otworzyc i).
// To jest graf funkcyjny (kazdy wezel ma dokladnie jedna krawedz wychodzaca).
// Kazda spojna skladowa takiego grafu to "ogony" wchodzace w dokladnie jeden cykl.
// Zeby odblokowac cala skladowa, trzeba rozbic dokladnie jedna skarbonke z jej cyklu.
// Odpowiedz = liczba cykli.

int main() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n;

    std::vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x; x--; // Klucz i lezy w skarbonce x
        parent[i] = x;
    }

    // 0 = nieodwiedzony, 1 = na biezacej sciezce, 2 = zakonczony
    std::vector<uint8_t> color(n, 0);
    std::vector<int> path(n); // Tymczasowy stos sciezki, wielokrotnego uzytku

    long long ans = 0; for (int start = 0; start < n; start++) {
        if (color[start] != 0) continue;

        int len = 0; int v = start;
        while (color[v] == 0) {
            color[v] = 1;
            path[len++] = v;
            v = parent[v];
        }

        if (color[v] == 1) {
            ans++;  // Trafilismy na wezel z biezacej sciezki -> nowy cykl
        }

        for (int k = 0; k < len; k++) color[path[k]] = 2;
    }

    std::cout << ans << "\n";
}
