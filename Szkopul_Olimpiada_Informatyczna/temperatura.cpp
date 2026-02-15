#include <iostream>
#include <cstring>

// 1) zawsze oplaca sie trzymac najmniejsza mozliwa
// 2) nigdy nie mozemy spasc ponizej najwiekszej na przedziale

using ll = long long;
constexpr ll  minf  = -__LONG_LONG_MAX__;
constexpr int two_n = 1 << 20;

// Tree

// drzewo low'sow
ll T[two_n * 2];

void set(int pos, ll val) {
    pos += two_n;

    T[pos] = val;
    pos /= 2;

    while (pos) {
        T[pos] = std::max(T[pos * 2], T[pos * 2 + 1]);
        pos /= 2;
    }
}

ll query() {
    return T[1];
}

// Monotonic

int beg = 0; // inc
int fro = 0; // exc
int max = 1;

bool can_push(ll U) {
    return U >= query();
}

void push_front(ll L) {
    set(fro, L); fro++;
    max = std::max(max, fro - beg);
}

void push_begin() {
    set(beg, minf);
    beg++;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    for (int i = 0; i < 2 * two_n; i++) T[i] = minf;

    int n; std::cin >> n;
    while (n--) {
        ll L, U; std::cin >> L >> U;
        while (!can_push(U)) push_begin();
        push_front(L);
    }

    std::cout << max;
}
