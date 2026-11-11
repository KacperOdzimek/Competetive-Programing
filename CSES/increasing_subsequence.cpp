// This is in fact longest decreasing subsequence

#include <bits/stdc++.h>
constexpr int max_n = 2 * 100000;
constexpr int log_n = 1 << 18;
using ll = long long;

// Segment tree; Int Range
int T[2 * log_n];
void update(int pos, int val) {
    pos += log_n; while (pos) {
        T[pos] = std::max(T[pos], val); pos /= 2;
    }
}
int query(int beg, int end) {
    beg += log_n; end += log_n;
    int result = 0; while (beg < end) {
        if (beg & 1) result = std::max(result, T[beg++]);
        if (end & 1) result = std::max(result, T[--end]);
        beg /= 2; end /= 2;
    } return result;
}

// Main Logic
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; std::vector<std::pair<ll, int>> US(n);
    for (int i = 0; i < n; i++) {
        std::cin >> US[i].first; US[i].second = i;
    } std::sort(US.begin(), US.end());

    std::vector<int> S(n);
    int sv = 0; ll usv = 0; for (auto [v, i] : US) {
        if (v != usv) {sv++; usv = v;} S[i] = sv;
    }

    // Left To Right
    for (int i = 0; i < n; i++) {
        int max_prefix = query(0, S[i]);
        update(S[i], max_prefix + 1);
    } 
    
    std::cout << T[1];
}