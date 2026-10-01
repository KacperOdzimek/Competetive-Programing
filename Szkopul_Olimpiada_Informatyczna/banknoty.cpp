#include <bits/stdc++.h>
constexpr int max_n = 200;
constexpr int max_k = 20'001;

int B[max_n];
int C[max_n];

int DS[max_k];  // Dynamic state    : minimalna liczba monet by uzyskac kwote i
int DP[max_k];  // Dynamic previous : stan poprzedni
int I[max_n];   // Ilosc monet

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> B[i];
    for (int i = 0; i < n; i++) std::cin >> C[i];

    int k; std::cin >> k;
    std::fill(DS + 1, DS + max_k, max_k);

    // Dla kazdego nominalu
    for (int i = n - 1; i >= 0; i--) {
        // Dla kazdego stanu
        for (int j = k - 1; j >= 0; j--) {
            if (DS[j] == max_k) continue;
            int ilo = C[i];
            int tar = j;
            while (ilo--) {
                int prv = tar; tar += B[i]; if (tar > k)   break;
                if (DS[tar] <= DS[prv] + 1) break;
                DS[tar] = DS[prv] + 1;
                DP[tar] = prv;
            }
        }
    }

    // Znajdz monety
    int ki = k; while (ki != 0) {
        int prv = DP[ki];
        I[std::distance(B, std::lower_bound(B, B + n, ki - prv))]++;
        ki = prv;
    }

    // Odpowiedz
    std::cout << DS[k] << '\n';
    for (int i = 0; i < n; i++) std::cout << I[i] << ' ';
}

/*
3
1 3 5
5 5 5
9
*/
