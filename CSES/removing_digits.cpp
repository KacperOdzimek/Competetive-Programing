#include <bits/stdc++.h>

struct state {
    int moves;
    int number;
};

bool operator<(const state& a, const state& b) {
    if (a.moves != b.moves) return a.moves > b.moves;
    return a.number > b.number;
}

int main() {
    int n; std::cin >> n;
    
    std::vector<int> DP(n + 1, INT32_MAX); DP[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 9; j++) {
            if (i + j >= n + 1) break;
            int  sum = i + j;
            bool has = false;
            for (int i = 0; i < 7; i++) {
                int dgt = sum % 10;
                if (dgt == j) has = true;
                sum /= 10;
            }
            if (!has) continue;
            DP[i + j] = std::min(DP[i + j], DP[i] + 1);
        }
    }

    std::cout << DP[n];
}
