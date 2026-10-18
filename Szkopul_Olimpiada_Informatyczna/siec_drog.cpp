/*
    Warunek sasiedztwa to nie krawedz - chodzi o to 
    żeby bezposrednia krawedz była ściśle krótsza niż jakakolwiek inna ścieżka.
    W szczegolnosci najkrotsza bedzie sciezka przez tylko jedno miasto C (nieujemne wagi).
*/

#include <bits/stdc++.h>
constexpr int max_n = 200;

int n;                  // Liczba miast
int D[max_n][max_n];    // Dystans miasta i do j

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n; for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> D[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) continue;
            bool sasiedzi = true;
            for (int x = 0; x < n; x++) {
                if (x == i || x == j)               continue;
                if (D[i][j] < D[i][x] + D[j][x])    continue;
                sasiedzi = false; break;
            }
            if (sasiedzi) std::cout << (i + 1) << ' ' << (j + 1) << '\n';
        }
    }
}
