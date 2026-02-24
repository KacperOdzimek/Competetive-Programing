#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

// 1) zauwazamy ze anagramy musza miec taki sam "sklad literowy"
// 2) bedziemy wiec utożsamiać słowo z ilosciami liter w nim
// 3) potem posortujemy w kluczu składu - poznamy klasy
// 4) słowa w klasach posortujemy alfabetycznie - poznamy porzadek wewnatrz klas
// 5) klasy posortujemy po pierwszych - poznamy porzadek klas

constexpr int max_n = 3000;
constexpr int alpha = 26; // rozmiar alfabetu

struct slowo {
    std::string oryginalne;
    char litery[alpha];
};

slowo                            S[max_n];  // slowa
std::vector<std::vector<slowo*>> K;         // klasy

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;
    for (int i = 0; i < n; i++) {
        auto& s = S[i];
        std::cin >> s.oryginalne;
        for (int j = 0; j < s.oryginalne.size(); j++) {
            int idx = s.oryginalne[j] - 'a';
            s.litery[idx]++;
        }
    }

    // porzadek leksykograficzny po skladzie liter; l < r
    std::sort(S, S + n, [](const slowo& l, const slowo& r) {
        for (int i = 0; i < alpha; i++) {
            if (l.litery[i] != r.litery[i]) return l.litery[i] < r.litery[i];
        }
        return false; // identyczne
    });

    K.push_back({&S[0]});

    // wyznaczamy klasy
    for (int i = 1; i < n; i++) {
        auto& prev = S[i - 1];
        auto& curr = S[i];

        // czy takie same sklady
        bool takie_same = true;
        for (int j = 0; j < alpha; j++) {
            if (prev.litery[j] != curr.litery[j]) {
                takie_same = false;
                break;
            }
        }

        // nowa klasa jezeli nie takie same
        if (!takie_same) K.push_back({});
        K.back().push_back(&curr);
    }

    // sortujemy kazda klase
    for (auto& k : K) {
        std::sort(k.begin(), k.end(), [](const slowo* l, const slowo* r) {
            return l->oryginalne < r->oryginalne;
        });
    }

    // sortujemy klasy
    std::sort(K.begin(), K.end(), [](const std::vector<slowo*>& l, const std::vector<slowo*>& r) {
        return l[0]->oryginalne < r[0]->oryginalne;
    });

    // wypisz bez duplikatow
    for (auto& k : K) {
        std::cout << k[0]->oryginalne;

        for (int i = 1; i < k.size(); i++) {
            if (k[i - 1]->oryginalne == k[i]->oryginalne) continue;
            std::cout << ' ' << k[i]->oryginalne;
        }

        std::cout << '\n';
    }
}
