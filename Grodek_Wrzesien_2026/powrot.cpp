#include <bits/stdc++.h>

// Config
constexpr int max_dim = 1000;
constexpr int max_k   = 20 + 1;
using ull = unsigned long long;

// Dane
int n, m, k, x;
int T[max_dim][max_dim];
ull S[max_dim][max_dim][max_k];

void prawo_gora_pass(int k) {
    S[n - 1][m - 1][k] = T[n - 1][m - 1];   // Koncowy
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (i + 1 <= n - 1) {           // Z dolnego
                S[i][j][k] = std::min(S[i][j][k], S[i + 1][j][k] + T[i][j]);
            }
            if (j + 1 <= m - 1) {           // Z prawego
                S[i][j][k] = std::min(S[i][j][k], S[i][j + 1][k] + T[i][j]);
            }
        }
    }
}

struct sliding_hold {
private:
    std::deque<std::pair<ull, int>> Q; // {Wartość, Indeks}

public:
    void push(ull val, int index) {
        // Kasujemy starsze i wieksze
        while (!Q.empty() && Q.back().first >= val) Q.pop_back();
        Q.push_back({val, index});
    }

    ull min(int index) {
        // Usuwamy te z poza zakresu
        while (!Q.empty()) {
            int idx = Q.front().second;
            if (idx > index ? (idx - index > x) : (index - idx > x)) {
                Q.pop_front();
            } else {
                break;
            }
        }
        return Q.front().first;
    }
};

void sliding_pass(int pk) {
    // Zbuduj sliding w [n-1, m-1]
    // Uzyj starej pamieci, gdyz nie bedzie juz potrzebna

    // Przejscia horyzontalne
    for (int i = 0; i < n; i++) {
        sliding_hold hold;
        
        int set_j = 0;
        int add_j = x;

        for (int l = 0; l < std::min(x, m); l++) {
            hold.push(S[i][l][pk - 1], l);
        }
        
        while (set_j != m) {
            if (add_j < m) hold.push(S[i][add_j][pk - 1], add_j);
            S[i][set_j][pk - 1] = hold.min(set_j);
            set_j++; add_j++;
        }
    }
    
    // Przejscia wertykanlne
    for (int j = 0; j < m; j++) {
        sliding_hold hold;

        int set_i = 0;
        int add_i = x;

        for (int l = 0; l < std::min(x, n); l++) {
            hold.push(S[l][j][pk - 1], l);
        }
        
        while (set_i != n) {
            if (add_i < n) hold.push(S[add_i][j][pk - 1], add_i);
            S[set_i][j][pk - 1] = hold.min(set_i);
            set_i++; add_i++;
        }
    }

    // Przemierz macierz
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            S[i][j][pk] = std::min(S[i][j][pk], S[i][j][pk - 1] + T[i][j]);
        }
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // Ladowanie
    std::cin >> n >> m >> k >> x;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> T[i][j];
            for (int l = 0; l <= k; l++) S[i][j][l] = ULONG_LONG_MAX;
        }
    }

    // Przejscia DP
    ull minans = ULONG_LONG_MAX;
    prawo_gora_pass(0); minans = std::min(minans, S[0][0][0]);
    for (int i = 1; i <= k; i++) {
        sliding_pass(i);    // Generuj z poprzedniego
        prawo_gora_pass(i);
        minans = std::min(minans, S[0][0][i]);
    }

    // Odpowiedz
    std::cout << minans;
}
