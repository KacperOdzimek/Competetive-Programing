#include <bits/stdc++.h>
constexpr int max_n = 200000;
constexpr int two_n = 1 << 18;
using ll = long long;

int T[two_n * 2];

// [beg, end)
void update(int pos, int val) {
    pos += two_n; while (pos) {
        T[pos] = std::max(T[pos], val); pos /= 2;
    }
}

// [0, end)
int query(int end) {
    int ans = 0;
    int beg = two_n; end += two_n;
    while (beg < end) {
        if (beg & 1) ans = std::max(ans, T[beg--]);
        if (end & 1) ans = std::max(ans, T[--end]);
        beg /= 2; end /= 2;
    }
    return ans;
}

int main() {
    // Load raw data
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; std::vector<std::pair<ll, int>> V(n);
    for (int i = 0; i < n; i++) {std::cin >> V[i].first; V[i].second = i; }
    std::sort(V.begin(), V.end());

    // Scale data
    int itr = -1; ll v = 0; std::vector<int> S(n);
    for (int i = 0; i < n; i++) {
        if (V[i].first != v) {
            v = V[i].first; itr++;
        } S[V[i].second] = itr;
    }

    // Answer
    for (int i = 0; i < n; i++) {
        std::cout << query(S[i]) << ' ' << std::flush;
        update(S[i], i + 1);
    }
}
