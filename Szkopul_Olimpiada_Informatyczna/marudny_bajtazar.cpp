#include <bits/stdc++.h>

// 1) Zauwazamy ze dla n = 100'000 (max) tylko podslowa o dlugosci < 17 moga wystapic wszystkie
// 2) Sledzimy ilosc kazdego podslowa poprzez aktualizacje. Śledzimy ilość podsłów o ilości > 0 per długość.

int n, m;
constexpr int max_n = 100'000 + 12;
char str[max_n];

constexpr int max_d     = 16;
constexpr int max_d_pow = std::pow(2, max_d) + 12;

int  count[max_d][max_d_pow];   // Ilosc danego podslowa
int  mcount[max_d];             // Ilosc istniejacych typow podslow (dla kazdego count[x] ilosc y ze count[x][y] != 0)

void generate() {
    uint16_t maska = 1;
    for (int d = 1; d <= max_d; d++) {
        uint16_t slowo = 0;

        for (int i = 0; i < n; i++) {
            slowo <<= 1;        // Przesun
            slowo &= maska;     // Utnij stare
            slowo |= str[i];    // Dodaj znak

            if (i < d - 1) continue; // Nie cale d uzyskane

            count[d - 1][slowo]++;                          // Podslowo powstalo
            if (count[d - 1][slowo] == 1) mcount[d - 1]++;  // Nowe podslowo powstalo
        }

        maska <<= 1; maska |= 1;
    }
}

void toggle(int x) {
    for (int d = 1; d <= max_d; d++) {
        // Zakres podslow +/- d zawierajacych x
        int L = std::max(0, x - d + 1);
        int R = std::min(x, n - d);

        // Dla poczatko slowa
        for (int start = L; start <= R; start++) {
            uint16_t slowo = 0;

            // Generuj slowo
            for (int j = 0; j < d; j++) {
                slowo <<= 1;
                slowo |= str[start + j];
            }

            // Skasuj stare slowo
            count[d - 1][slowo]--;
            if (count[d - 1][slowo] == 0) mcount[d - 1]--;

            // Znajdz slowo ze zmienionym x
            uint16_t changed = slowo;
            int bit = d - 1 - (x - start);  // x jest na pozycji d-1-(x-start) od LSB
            changed ^= (1 << bit);

            // Dodaj slowo ze zmienionym x
            count[d - 1][changed]++;
            if (count[d - 1][changed] == 1) mcount[d - 1]++;
        }
    }

    str[x] = !str[x];
}

void odpowiedz() {
    int all = 1; for (int d = 1; d <= max_d; d++) {
        all *= 2; if (mcount[d - 1] != all) {
            std::cout << d << '\n'; return;
        }
    } std::cout << 17 << '\n';
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m; std::cin >> str;

    for (int i = 0; i < n; i++) {
        if (str[i] == '0')  str[i] = 0;
        else                str[i] = 1;
    }

    generate();
    odpowiedz();

    for (int i = 0; i < m; i++) {
        int x; std::cin >> x; x--;
        toggle(x); odpowiedz();
    }
}
