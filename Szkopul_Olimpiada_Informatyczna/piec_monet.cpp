#include "mon.h"
#include <utility>

char P[5] = {'A', 'B', 'C', 'D', 'E'};

void sortuj_pozycje(int l, int r) {
    if (!lzejsza(P[l], P[r])) std::swap(P[l], P[r]);
}

void sortujMonety() {
    for (int l = 0; l < 5; l++) {
        for (int r = l + 1; r < 5; r++) {
            sortuj_pozycje(l, r);
        }
    }

    wynik(P[0], P[1], P[2], P[3], P[4]);
}
