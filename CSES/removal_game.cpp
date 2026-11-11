#include <bits/stdc++.h>
constexpr int max_n = 5000;
using ll = long long;

// Max score = max(Choose Left + Game that follows, Choose Right + Game that follows)

// Best score for Player 1 for game 
// on range [i, j] where Player 1 starts
// In game DP[x][x] it is the x'th value                                (p1 gains all)
// In game DP[i][j] it is Range Sum - min(DP[i + 1][j], DP[i][j - 1])   (we force p2 to play worst game for them)

ll PF[max_n];           // Prefix sums
ll DP[max_n][max_n];    // Dynamic state

ll range_sum(ll i, ll j) {
    ll pf = i - 1 >= 0 ? PF[i - 1] : 0;
    return PF[j] - pf;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0); 
    int n; std::cin >> n; for (int i = 0; i < n; i++) {
        if (i > 0) PF[i] += PF[i - 1];
        ll x; std::cin >> x; PF[i] += x; DP[i][i] = x;
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i != j) DP[i][j] = range_sum(i, j) - std::min(DP[i + 1][j], DP[i][j - 1]);
        }
    }

    std::cout << DP[0][n - 1];
}
