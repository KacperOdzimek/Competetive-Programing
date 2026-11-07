#include <bits/stdc++.h>
char C[3][3];
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> C[i][j];
        }
    }
    // Sprawdz rzedy
    for (int i = 0; i < 3; i++) {
        if (C[i][0] != '.' && C[i][0] == C[i][1] && C[i][1] == C[i][2]) {
            std::cout << C[i][0]; return 0;
        }
    }
    // Sprawdz kolumny
    for (int j = 0; j < 3; j++) {
        if (C[0][j] != '.' && C[0][j] == C[1][j] && C[1][j] == C[2][j]) {
            std::cout << C[0][j]; return 0;
        }
    }
    // Sprawdz przekatne
    if (C[0][0] != '.' && C[0][0] == C[1][1] && C[1][1] == C[2][2]) {
        std::cout << C[0][0]; return 0;
    }
    if (C[2][0] != '.' && C[2][0] == C[1][1] && C[1][1] == C[0][2]) {
        std::cout << C[2][0]; return 0;
    }
    std::cout << "R";
}
