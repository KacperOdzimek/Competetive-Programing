#include <bits/stdc++.h>

constexpr int max_c = 'z' - 'a' + 1;
constexpr int max_n = 1500;

int  n; 
char M[max_n][max_n][max_c];
int  O[max_n][max_n];

long long sweep(int v) {
    static int next_R[max_n][max_n];
    static int next_C[max_n][max_n];
    
    int last_r[max_n];
    for(int j = 0; j < n; ++j) {
        last_r[j] = n;
    }
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < n; ++j) {
            next_R[i][j] = last_r[j];
            if (O[i][j] >= v) {
                last_r[j] = i;
            }
        }
    }
    
    for(int i = 0; i < n; ++i) {
        int last = n;
        for(int j = n - 1; j >= 0; j--) {
            next_C[i][j] = last;
            if (O[i][j] >= v) {
                last = j;
            }
        }
    }

    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (O[i][j] < v) continue; 
            int M_val = next_R[i][j];
            int end_c = next_C[i][j];
            for (int c = j + 1; c < end_c; c++) {
                int r2 = next_R[i][c];
                if (r2 >= M_val) continue;
                if (std::min(O[i][j], O[r2][c]) == v) count++;
                M_val = r2;
            }
        }
        }
    return count;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n; for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; std::cin >> c; c -= 'a'; O[i][j] = c;
            for (char ci = c; ci < max_c; ci++) {
                M[i][j][ci] = 1;
            }
        }
    }

    long long wynik = 0; for (char c = 1; c < max_c; c++) {
        wynik += sweep(c);
    }

    std::cout << wynik;
}
