/*
Rozwiazanie O(n2) - 28 punktow
    Dla kadzej pary indeksow sprawdzamy czy f(i, j, n - 1) (czy abs(P[i] - P[j]) dzieli sie przez n -1)
    To bedzie prawdziwe tylko dla nieuporzadkowanej pary (n, 1), wiec porzadkujac ja zapytaniem g dostajemy odpowiedz
    Powyzsze udowadnia nam iż M(n) - minimalna liczba zapytan g, to zawsze 1
Rozwiazanie O(nlogn) - 100 punktow
    Wiec musimy znalesc minimum i maksimum na zbiorze, jak udowodniono wyzej.
    Mozna to zrobic rekursywnie: dzielimy zbior na parzyste i nieparzyste elementy.
    Jako argument wszystkich operacji f w tych dzieleniach zawsze podajemy jakis indeks, ze zbioru, np ten pierwszy
    jako ze jest to stala, mimo iz moze zmienic parzystosc nie wplywa na dalsza poprawnosc.
    (Zmiennosc j miedzy pietrami jest potrzebna, bo jezeli cos nie dzieli sie przez 2, niepodzielio by sie przez 4 rowniez)
    W obu uzyskanych zbiorach mozemy wyznaczyc minimum i maksimum sprawdzajac f(i, j, max zakres dla podzbioru)
    Ale to znowu bylo by O(n2) w ramach podzbioru. Wiec dzielimy dalej na podzielne przez 4, 8, i tak dalej
    Za kazdym razem zwracamy pare {minimum, maksimum} wiec wyzsza warstwa wykonuje tylko 4 porownania, O(n2) na wynikach warstw nizszych
*/

#include <bits/stdc++.h>

#ifndef LOCAL
#include "cgdzlib.h"
int inicjuj();
int f(int i, int j, int d);
int g(int i, int j);
void odpowiedz(int i);
#else

std::vector<int> seq = {
    4, 3, 1, 2
};

int inicjuj() {
    return seq.size();
}

int f(int i, int j, int d) {
    if (i <= 0 || j <= 0)                 abort();
    if (i > seq.size() || j > seq.size()) abort();
    if (d <= 0)                           abort();
    i--; j--; return (std::abs(seq[i] - seq[j]) % d == 0);
}

int g(int i, int j) {
    if (i <= 0 || j <= 0)                 abort();
    if (i > seq.size() || j > seq.size()) abort();
    i--; j--; return (seq[i] > seq[j]);
}

void odpowiedz(int i) {
    if (i <= 0 || i > seq.size()) abort();
    std::cout << i;
}

#endif

int n;

// p2 - potega 2 w ktorej lamiemy, P - dany zbior
std::pair<int, int> rek(int p2, const std::vector<int>& P) {
    if (P.size() == 1) return {P[0], P[0]};
    if (P.size() == 2) return {P[0], P[1]};

    std::vector<int> d, nd;
    for (int i : P) {
        (f(i, P.front(), p2) ? d : nd).push_back(i);
    }

    auto [min_d,  max_d]  = rek(p2 * 2, d);
    auto [min_nd, max_nd] = rek(p2 * 2, nd);

    int diff = (int)(P.size() - 1) * (p2 / 2);   // max - min w tym zbiorze

#define CASE(x, y) if (x != y) if (f(x, y, diff)) return {x, y};
    CASE(min_d,  max_d);
    CASE(min_d,  min_nd);
    CASE(min_d,  max_nd);
    CASE(max_d,  min_nd);
    CASE(max_d,  max_nd);
    CASE(min_nd, max_nd);

    return {0, 0}; // naprawdę nieosiągalne
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // Jedyny wypadek gdzie mozna
    // nie uzywac zapytania g
    n = inicjuj(); if (n == 1) {
        odpowiedz(1);
        return 0;
    }

    std::vector<int> P;
    for (int i = 1; i <= n; i++) P.push_back(i);
    auto [l, r] = rek(2, P);

    if (g(l, r)) odpowiedz(r);
    else         odpowiedz(l);
}
