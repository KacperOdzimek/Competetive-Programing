#include <iostream>
#include <set>

using ull = unsigned long long;

constexpr ull max_n = 1000;
ull p, n;

ull C[max_n];
ull D[max_n];

ull K; // koszt
ull SP; // suma calego paliwa
std::set<std::pair<ull, ull>> P; // cena, litry

// wypalamy najtansze paliwo
void pokonaj_dst(ull d) {
    while (d != 0) {
        auto itr = P.begin();
        ull used = std::min(itr->second, d);

        SP -= used;
        d  -= used;

        ull left = itr->second - used;
        ull cena = itr->first;

        P.erase(itr);
        if (left) P.insert({cena, left});
    }
}

// sprzedajemy kazde paliwo drosze od tutejszego
void tankuj(ull c) {
    auto itr = P.lower_bound({c, 0});

    while (itr != P.end()) {
        SP -= itr->second;
        K  -= (ull(itr->first) * itr->second);
        itr = P.erase(itr);
    }

    ull t = p - SP;
    SP = p;
    
    P.insert({c, t});
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
