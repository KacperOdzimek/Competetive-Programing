#include <bits/stdc++.h>
int L[27];
int main() {
    std::string str; std::cin >> str;
    for (char c : str) L[c - 'A']++;

    char odd = '\0';
    for (int i = 0; i < 26; i++) {
        if (L[i] % 2) {
            if (odd) {
                std::cout << "NO SOLUTION";
                return 0;
            }
            odd = i + 'A';
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < L[i] / 2; j++) {
            std::cout << char('A' + i);
        }
    }

    if (odd) std::cout << odd;

    for (int i = 26; i >= 0; i--) {
        for (int j = 0; j < L[i] / 2; j++) {
            std::cout << char('A' + i);
        }
    }
}
