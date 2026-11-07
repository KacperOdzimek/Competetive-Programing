#include <bits/stdc++.h>
using ll = long long;

constexpr int max_n = 100000 + 1;
int n; int k; ll A[max_n];

bool sprawdz(ll X) {
    int taxi = 0; ll curr = 0;
    for (int i = 0; i < n; i++) {
        if (curr + A[i] > X) {
            taxi++; curr = 0;
        } 
        else {
            curr += A[i];
        }
    }
    return taxi <= k;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> k;

    ll sum_A = 0; ll max_A = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
        sum_A += A[i]; max_A = std::max(max_A, A[i]);
    }

    ll low = 1, high = sum_A;
    ll ans = sum_A;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (sprawdz(mid)) {
            ans = mid; high = mid - 1;
        } 
        else {
            low = mid + 1;
        }
    }

    std::cout << ans << "\n";
}
