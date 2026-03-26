#include <iostream>

using ull = unsigned int;

constexpr ull max_n = 1'000'000 + 100;
ull p, n;

ull C[max_n];
ull D[max_n];

ull                 K;         // koszt
std::pair<ull, ull> P[max_n];  // cena, litry, manualny deque
ull                 SP;        // suma calego paliwa

// manualna implemetancja deque na P
// ciasne limity na szkopule sa

int front = 0; // inclusive
int back  = 0; // exclusive

inline std::pair<ull, ull>& Dfront() {
    return P[front];
}

inline std::pair<ull, ull>& DBack() {
    return P[back - 1];
}

inline int DSize() {
    return back - front;
}

inline void DPushBack(std::pair<ull, ull>&& p) {
    P[back] = p;
    back++;
}

inline void DPopFront() {
    front++;
}

inline void DPopBack() {
    back--;
}

// wypalamy najtansze paliwo
void pokonaj_dst(ull d) {
    while (d != 0) {
        auto& p = Dfront();
        ull uzyte = std::min(p.second, d);

        SP       -= uzyte;
        d        -= uzyte;
        p.second -= uzyte;

        if (!p.second) DPopFront();
    }
}

// sprzedajemy kazde paliwo drosze od tutejszego
// takie dodawanie wymusza porzadek
void tankuj(ull c) {
    while (DSize()) {
        auto& p = DBack();

        // niedrozsze, przestan
        if (p.first <= c) break;

        SP -= p.second;
        K  -= (ull(p.first) * p.second);
        DPopBack();
    }

    ull t = p - SP;
    SP = p;
    
    DPushBack({c, t});
    K += ull(c) * t;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> p >> n;
    for (ull i = 0; i < n; i++) { std::cin >> C[i] >> D[i]; }
    
    for (ull i = 0; i < n; i++) {
        tankuj(C[i]);
        pokonaj_dst(D[i]);
    }

    tankuj(0); // odsprzedajemy reszte paliwa
    std::cout << K;
}
