#include <iostream>

// O(d * g)

// dol jest mniejszy badz rowny
// odwracamy dol
// mozemy wybrac gdzie go przylozymy
// alfabet rozciaga sie na [0, 60]

constexpr int max = 20'000 + 3;

int  g, d;          // rozmiary
char G[max];        // gorny ciag
char D[max];        // dolny ciag
int  ans;           // odpowiedz

void czolg(int di, int gi) {
    int diff = 0;

    // na pierwszych d
    for (int i = 0; i < d; i++) {
        if (G[gi] != D[di]) diff++;
        (di += 1) %= d;
        gi++;
    }

    ans = std::min(ans, diff);

    // przenos poczatek na koniec
    while (gi != g) {
        // nie pasowal, wiec usuwamy jego inwersje
        if (G[gi - d] != D[di]) diff--;

        // przykladamy teraz
        if (G[gi] != D[di]) diff++;

        (di += 1) %= d;
        gi++;

        ans = std::min(ans, diff);
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> g >> d;

    // gora
    for (int i = 0; i < g; i++) {
        int x; std::cin >> x; x += 30;
        G[i] = char(x);
    }

    // dol
    for (int i = 0; i < d; i++) {
        int x; std::cin >> x; x += 30;
        D[i] = char(x);
    }

    ans = d;
    for (int di = 0; di < d; di++) czolg(di, 0);
    std::cout << ans;
}
