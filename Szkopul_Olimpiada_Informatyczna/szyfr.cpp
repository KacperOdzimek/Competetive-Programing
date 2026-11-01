/*
    1) Jezli szyfr to suma kolejnych wartosci razy bity, a odpowiedz jest jednoznaczna
        To musimy wyznaczyc jaki podzbior a sumuje sie do szyfru
    2) 2'000'000'000 to za duzo na bitset DP, robimy jakas mape [suma : sciezka]
    3) To da nam 2^n stanow co tez nie dobre
    4) Mozna probowac je ciac kasujac te ktore napewno juz nie zadzialaja (bo suma elementow do rozwazania jest za mala)
*/

#include <bits/stdc++.h>
using ull = unsigned long long;
constexpr int max_n = 40;
constexpr int max_d = 1 << (max_n / 2);

int n;
ull A[max_n];
ull S;

std::pair<ull, int> P[max_d];
std::pair<ull, int> Q[max_d];

// Tablica, Pierwszy Bit, Liczba Bitow
void generuj(std::pair<ull, int>* T, int fb, int count) {
    int limit = 1 << count;
    for (int m = 0; m < limit; m++) {   
        T[m].second = m; T[m].first = 0;
        for (int i = 0; i < count; i++) {
            if (m & (1 << i)) T[m].first += A[i + fb];
        }
    }
    std::sort(T, T + limit);
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n; for (int i = 0; i < n; i++) std::cin >> A[i]; 
    std::cin >> S;

    int m1 = n / 2;
    int m2 = n - m1;
    int d1 = 1 << m1;
    int d2 = 1 << m2;

    generuj(P, 0, m1);
    generuj(Q, m1, m2);

    ull w = 0;  
    for (int i = 0; i < d1; i++) {
        if (S  < P[i].first) break;    
        if (S == P[i].first) {
            w = P[i].second;
            break;
        }

        ull missing = S - P[i].first;
        auto sec = std::lower_bound(Q, Q + d2, std::make_pair(missing, 0));

        if (sec != Q + d2 && sec->first == missing) {
            w = P[i].second | ((ull)sec->second << m1);
            break;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (w & (1ULL << i)) std::cout << '1';
        else std::cout << '0';
    }
}
