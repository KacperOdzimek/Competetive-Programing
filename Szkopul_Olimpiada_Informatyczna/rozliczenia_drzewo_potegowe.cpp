#include <iostream>

using ll = long long;

/*
    Drzewo Potegowe
*/

constexpr int max_m = 1'000'000 + 1;
ll S[max_m];

void change(int pos, ll val) {
    int idx = pos + 1;

    while (idx < max_m) {
        S[idx] += val;
        idx += (idx & -idx);
    }
}

// suma [0, pos)
ll query(int pos) {
    pos++;
    ll res = 0;
    while (pos > 0) {
        res += S[pos];
        pos -= (pos & -pos);
    }
    return res;
}

// suma [beg, end)
ll query(int beg, int end) {
    if (beg == 0) return query(end - 1);
    return query(end - 1) - query(beg - 1);
}

void set(int pos, ll val) {
    change(pos, -query(pos, pos + 1)); // skasuj obecna wartosc
    change(pos, val);                  // dodaj nowa wartosc
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
