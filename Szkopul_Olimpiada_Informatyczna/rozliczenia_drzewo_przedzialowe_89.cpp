#include <iostream>

using ll = long long;

/*
    Drzewo Przedzialowe
*/

constexpr int two_m = 1 << 19;
ll T[2 * two_m];

void set(int pos, ll val) {
    pos += two_m;

    T[pos] = val;
    pos /= 2;

    while (pos) {
        T[pos] = T[pos * 2] + T[pos * 2 + 1];
        pos /= 2;
    }
}

void change(int pos, ll val) {
    ll cur = T[pos + two_m];
    set(pos, cur + val);
}

// inc, exc
ll query(int beg, int end) {
    beg += two_m; end += two_m;

    ll sum = 0;
    while (beg < end) {
        if (beg & 1) sum += T[beg++];
        if (end & 1) sum += T[--end];
        beg /= 2; end /= 2;
    }

    return sum;
}

/*
    System
*/

int m;
int itr;

// init, sledzimy tylko m ostanich wartosci
void inicjuj(int nm) {
    m = nm;
}

// push back na liste
void dodaj(int x) {
    set(itr, x);
    (itr += 1) %= m;
}

// T[n - i] += x
void koryguj(int i, int x) {
    int pos = itr - i;
    if (pos < 0) pos = m + pos;
    change(pos, x);
}

// Suma i ostatnich (i moze byc za duze)
ll suma(int i) {
    int first = itr - i;
    if (first >= 0) return query(first, itr);

    ll nowe  = query(0, itr);
    ll stare = query(m + first, m);

    return nowe + stare;
}

// gdy kompiluje lokalnie
#ifdef LOCAL
    int main() {
        std::cin.tie(0); std::ios_base::sync_with_stdio(0);

        inicjuj(3);

        dodaj(-6);
        dodaj(1);
        dodaj(1);
        std::cout << suma(3) << '\n' << std::flush; // -4
        std::cout << suma(2) << '\n' << std::flush; // 2

        dodaj(-30);
        dodaj(-30);
        std::cout << suma(3) << '\n' << std::flush; // -59
        std::cout << suma(2) << '\n' << std::flush; // -60
    }
#endif
