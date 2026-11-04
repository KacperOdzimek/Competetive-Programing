#include <bits/stdc++.h>
char C[8][8];

int main() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cin >> C[i][j];
        }
    }

   int ans = 0; std::vector<int> J = {0, 1, 2, 3, 4, 5, 6, 7}; do {
        // Check valid permutation
        for (int i = 0; i < 8; i++) {
            if (C[i][J[i]] == '*') goto _next_perm;
        }

        // Ensure no diagonals
        for (int i1 = 0; i1 < 8; i1++) {
            for (int i2 = i1 + 1; i2 < 8; i2++) {
                int dist_i = i2 - i1;
                int dist_j = J[i2] - J[i1];
                if (std::abs(dist_i) == std::abs(dist_j)) goto _next_perm;
            }
        }

        // Valid permutation
        ans++; _next_perm: continue;
    } while (std::next_permutation(J.begin(), J.end()));

    std::cout << ans;
}
