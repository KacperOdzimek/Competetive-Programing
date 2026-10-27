/*
    Ciekawe rozwiazanie:
    Zauwazamy ze xor to to samo co reszta modulo 2 na bicie
    Rozwiazuje nam to prostszy problem "ktora liczba wystepuje pojedynczo, gdy reszta dwukrotnie"
    bo powtorzenia sie z xoruja i nie wplna na rozwiazanie, a ta pojedyncza pozostanie w rejestrze.
    (Przechodzimy wszystkie liczby i robimy xor z jednym globalnym intem).
    Tutaj robimy cos podobnego ale liczebnosc kazdego bitu dzielimy modulo oczekiwana liczba wystapien.
    Jezeli w danym bicie liczebnosc pozostala nie zerowa (nie dzieli sie przez wystapienia), to znaczy ze bit
    jest uwzgledniony w zapisie binarnym szukanej wartosci.
*/

#include <bits/stdc++.h>
using ull = unsigned long long;

// Biblioteka
#ifndef LOCAL

#include "ckollib.h"
int  karta();
void odpowiedz(int wynik);

#else

std::vector<int> data = {
    1, 2, 3, 0
};

int karta() {
    static int pos = 0;
    return data[pos++];
}

void odpowiedz(int wynik) {
    std::cout << wynik;
}

#endif

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    
    // Ilosc wystapien bitu
    ull cpb[32]; std::memset(cpb, 0, 32 * sizeof(ull));
    
    // Pierwsza sledzona liczba
    int x1 = -1; ull c1 = 0;

    // Druga sledzona liczba
    int x2 = -1; ull c2 = 0;
    
    // Laduj dane
    int k; do {
        k = karta(); if (!k) break;
        for (int i = 0; i < 32; i++) cpb[i] += ((k & (1 << i)) ? 1 : 0);
        if (x1 == -1 || x1 == k) {
            x1 = k; c1++;
        }
        else if (x2 == -1 || x2 == k) {
            x2 = k; c2++;
        }
    } while(true);

    // Wypadek szczegolny : tylko jedna liczba
    if (x2 == -1) {
        odpowiedz(x1); return 0;
    }

    // Wypadki szczegolne : akurat x1 lub x2 sa odpowiedzia
    // Inaczej c1 i c2 rowne i sa liczba wystapien "nieokradziona", oczekiwana
    if (c1 < c2) {
        odpowiedz(x1); return 0;
    }
    if (c2 < c1){
        odpowiedz(x2); return 0;
    }
 
    // Dzielimy liczbe wystapien bitu per reszta
    for (int i = 0; i < 32; i++) cpb[i] %= c1;

    // Interpretujemy jako liczba
    int ans = 0; ull w = 1; for (int i = 0; i < 32; i++) {
        ans += (cpb[i] ? 1 : 0) * w; w *= 2;
    }

    // Wypadek szczegolny : rowno
    if (ans == 0) {
        odpowiedz(x1); return 0;
    }

    odpowiedz(ans);
}
