#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using ull = unsigned long long;
constexpr int max_n = 200'000;
constexpr ull mod   = 998244353;

int n; ull x;
ull A[max_n];

void solve() {
    std::cin >> n >> x;
    for (int i = 0; i < n; i++) std::cin >> A[i];

    // edge case
    if (x == 0) {
        ull komb = 1;
        while (n--) (komb *= 2) %= mod;
        komb--;

        std::cout << komb << '\n';
        return;
    }
    
    ull sig_mask   = 0;
    ull key_mask   = 0;
    ull insig_mask = 0;

    int przed;
    int po;

    {
        ull a = x;

        // zlicz ilosc pozycji przed pierwsza jedynka
        przed = 0;
        while (a != 1) {
            a >>= 1; przed++;
        }

        // ilosc pozycji po pierwszej jedynce
        po = 64 - przed - 1;

        // generuj sekwencje jedynek o dlugosci po
        for (int i = 0; i < po; i++) {
            sig_mask <<= 1;
            sig_mask++;
        }

        // przesun sekwencje do lewej
        sig_mask <<= (przed + 1);

        // bit pierwsza jedynka
        key_mask = 1ULL << przed;

        // maska koncowych bitow
        insig_mask = ~(sig_mask | key_mask);
    }

    struct grupa {
        int pierwszy        = -1;
        int ostatni         = -1;
        int pierwszy_key_1  = -1;
    };

    std::vector<grupa> G;

    // sort pozycyjny in fact
    std::sort(A, A + n);

    ull prev_key = 0;
    ull prev_sig = ULLONG_MAX;

    for (int i = 0; i < n; i++) {
        // zacznij nowa grupie
        if (prev_sig != (A[i] & sig_mask)) {
            if (G.size()) G.back().ostatni = i - 1;

            G.push_back({});
            auto& g = G.back();

            g.pierwszy = i;
            if (A[i] & key_mask) g.pierwszy_key_1 = i;
        }
        // wciaz w tej samej grupie
        else {
            // nie wykryo jegomoscia
            if (G.back().pierwszy_key_1 == -1) {
                auto key = A[i] & key_mask;
                if (key) G.back().pierwszy_key_1 = i;
            }
        }

        prev_key = A[i] & key_mask;
        prev_sig = A[i] & sig_mask;
    }

    G.back().ostatni = n - 1;

    ull komb = 1;
    ull insig_x = (x & (sig_mask | key_mask)) ^ x;

    for (auto g : G) {
        ull opcja_zadna = 1;

        // najwyzej 200'000
        ull opcja_jedna = g.ostatni - g.pierwszy + 1;

        // najwyzej 100'000 * 100'000 -> 1e10 -> 10^9 miesci sie
        ull opcja_dwie = 0;

        if (g.pierwszy_key_1 != g.pierwszy && g.pierwszy_key_1 != -1) {
            // A[u] ma kluczowy bit == 0, probujemy dobrac mu takie A[v] zeby xor ich byl wiekszy od x na koncowych bitach
            for (int u = g.pierwszy; u < g.pierwszy_key_1; u++) {
                // najpierw sortujemy po j tym bicie w xorze (u ^ v)
                // jezeli bit x jest 0, doliczamy i odrzucamy wszystkie co wyszly 1 (sa wieksze)
                // jezeli bit x jest 1, bierzemy tylko te co wyszly jeden i idziemy dalej
                
                int range_bottom = g.pierwszy_key_1;
                int range_top    = g.ostatni + 1; // exc

                // pierwsze bity naszego v
                // do konstrukcji kluczy wyszukiwac lower bound
                ull v_prec = (u & sig_mask) | key_mask;

                for (int j = przed; j != 0; j--) {
                    ull bit_mask = 1ULL << (j - 1);

                    std::sort(A + range_bottom, A + range_top, [&](ull a, ull b){
                        // bierzemy j tego bita z xora
                        ull ba = ((a ^ u) & bit_mask);
                        ull bb = ((b ^ u) & bit_mask);

                        // porownojemy
                        return ba < bb;
                    });

                    // takie v, co ma prefix od u, oraz ma tego bita j tego wlaczonego
                    ull v_first = v_prec | bit_mask;

                    // pierwszy taki co ma bita j tego wlaczonego
                    ull* ptr = std::lower_bound(A + range_bottom, A + range_top, v_first, [&](ull a, ull b){
                        // bierzemy j tego bita z xora
                        ull ba = ((a ^ u) & bit_mask);
                        ull bb = ((b ^ u) & bit_mask);

                        // porownojemy
                        return ba < bb;
                    });

                    // idx inc.
                    int idx = (ptr - A);

                    // j ty bit u x == 1
                    if (x & bit_mask) {
                        // odrzucamy te co maja bity 0, bo jak nic nie sa wieksze od x
                        range_bottom = idx;

                        // nie ma juz nic co moglo by spelnic warunki
                        if (range_bottom == range_top) break;
                    }
                    // j ty bit u x == 0
                    else {
                        // sa lepsze od x, wiec odrzucamy cwaniakow u piescimy sie z reszta
                        opcja_dwie += (range_top - idx);
                        range_top = idx;
                    }
                }

                // te co zostaly musialy spelniac warunek
                opcja_dwie += (range_top - range_bottom);
            }
        }

        ull opcje = opcja_zadna + opcja_jedna + opcja_dwie;
        opcje %= mod;

        (komb *= opcje) %= mod;
    }

    // zbior pusty to nie opcja
    komb--;

    std::cout << komb << '\n';
}

int main() {
    int t; std::cin >> t;
    while (t--) solve();
}

/*
1
3 3
0 1 2
*/
