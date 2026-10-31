/*
    1) Wybrany ciag jest lepszy od innego jezeli jest leksykograficznie wyzszy od konkurenta
    2) Kolejnosc projektow musi byc zgodna z kolejnoscia wejscia
    3) Ciag musi zawierac k elementow
    4) Tak dlugo jak nasz wybrany ciag jest malejaco/rowny nie chcemy nic wyrzucac
        (Po co wyrzucac wyzsze elementy na rzecz nizszych?)
    5) Koniec tej monotoniczosci wyznacza punkt gdzie nalezy wyrzucac; 
        Gdy ciag zaczyna rosnac warto uciac ostatni element malejacego ciagu
*/

#include <bits/stdc++.h>

#ifdef LOCAL

int seq_k = 3;

std::vector<int> seq = {
    //12, 5, 8, 3, 15, 8
    5, 5, 6, 5, 5, 7
};

int inicjuj() {
    return seq_k;
}

int wczytaj() {
    static int itr = 0;
    if (itr == seq.size()) return 0;
    return seq[itr++];
}

void wypisz(int jakosc) {
    std::cout << jakosc << ' ';
}

#else
#include "arc.h"
int inicjuj();
int wczytaj();
void wypisz(int jakosc);
#endif

int main() {
    // Struktury
    int k = inicjuj();
    std::stack<int> M;  // Nie rosanacy (malejacy i rowny) prefiks
    std::queue<int> U;  // Niekoniecznie monotoniczna reszta; M.top() < U.front()

    // Ladowanie elementow online
    int e; int i = -1; do { // Petla nawet 15'000'000 razy
        // Zaladuj projekt
        e = wczytaj(); i++; if (!e) break;

        // Poczatkowe zapelnianie
        if (M.size() + U.size() < k) {
            if (U.empty() && (M.empty() || M.top() >= e))   M.push(e);
            else                                            U.push(e);
        }
        // Podmienianie
        else {
            // M ma caly ciag, oraz e nie warto wstawiac
            if (U.empty() && M.top() >= e) continue;
            else {
                M.pop();    // Wywal najmniejszy element monotonii (zawsze warto bo M.top() < U.front())
                U.push(e);  // Dodaj nowy element

                // Napraw stan; M.top() < U.front()
                while (U.size() && (M.empty() ? INT32_MAX : M.top()) >= U.front()) {
                    M.push(U.front());
                    U.pop();
                }
            }
        }
    } while (true);

    // Wypisz
    std::vector<int> A;
    while (M.size()) {A.push_back(M.top()); M.pop();}
    std::reverse(A.begin(), A.end());
    while (U.size()) {A.push_back(U.front()); U.pop(); };
    for (int i : A) wypisz(i);
}
