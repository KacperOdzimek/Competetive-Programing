#include <bits/stdc++.h>
using ll = long long;

constexpr int max_n = 100000;
int n; ll m; int T[max_n]; ll R[max_n];

bool test(ll H){
    if (H == 0) return true;

    ll moves = 0, rem = 0;
    for(int i = 0; i < n; i++){
        ll cur = (H + T[i] - 1) / T[i] - 1;
        bool last = (i == n - 1);

        moves += 1 + 2 * rem - (last && cur < rem);
        if (moves > m) return false;

        rem = std::max(cur - rem, 0LL);
    }

    return moves + 2 * rem <= m;
}

ll solve(){
    std::cin >> n >> m;
    for(int i = 0; i < n; i++){
        std::cin >> T[i];
    }

    ll low = 0, upp = ll(2e18); ll ans = 0;
    while(low <= upp){
        ll mid = low + (upp - low) / 2;
        if (test(mid)) {
            ans = mid;
            low = mid + 1;
        }
        else {
            upp = mid - 1;
        }
    }

    return ans;
}

int main(){
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    int Z; std::cin >> Z;
    while(Z--) std::cout << solve() << '\n';
}
