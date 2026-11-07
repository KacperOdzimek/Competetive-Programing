#include <bits/stdc++.h>
int C[12][12]; // Macierz [ilosc nastepstw i->j]

int sprawdz_kolorowanie(const std::vector<char>& X) {
    int res = 1;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (X[i] == X[j]) continue;
            res += C[i][j];
        }
    }
    return res;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0); 
    int n; std::cin >> n; char p = '\0'; for (int i = 0; i < n; i++) {
        char c; std::cin >> c;
        if (c == p) continue;
        if (p == 0) {p = c; continue;}
        C[p - 'A'][c - 'A']++; p = c;
    }

    int wszystkie_kolorowania = 531441; // 3^12
    int ans = 0; for (int mask = 0; mask < wszystkie_kolorowania; mask++) {
        std::vector<char> X(12); int temp = mask;
        for (int i = 0; i < 12; i++) {
            X[i] = temp % 3;
            temp /= 3;
        }
        ans = std::max(ans, sprawdz_kolorowanie(X));
    }

    std::cout << ans;
}
