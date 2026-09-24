#include <bits/stdc++.h>

// Config
using ull = unsigned long long;
constexpr int N = 1'000'000 + 5;
constexpr ull M = 1'000'000'000 + 7;

// Wartosc; Ilosc
using para =  std::pair<ull, int>;
std::vector<para> V;

// Potegi 2
ull PO2[N];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // Wylicz potegi 2
    PO2[0] = 1; for (int i = 1; i < N; i++) {
        PO2[i] = (PO2[i - 1] * 2);
        PO2[i] %= M;
    }

    // Laduj i kompresuj dane
    int n; std::cin >> n; ull x; std::cin >> x; int l = 1;
    for (int i = 0; i < n - 1; i++) {
        ull nx; std::cin >> nx;
        if (nx == x) l++;
        else {
            V.push_back({x, l});
            x = nx; l = 1;
        }
    }
    V.push_back({x, l});

    // Odpowiedz
    ull wynik = 0;
    for (int i = 0; i < V.size(); i++) {
        wynik += (PO2[V.size() - i - 1] * V[i].second);
        wynik %= M;
    } std::cout << wynik;
}
