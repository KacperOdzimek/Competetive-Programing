#include <iostream>
#include <algorithm>
#include <climits>

// w zadaniu dla prostoty omijamy liczenie nowych kostek -
// te napewno da sie jakos przewrocic

using ull = unsigned long long;

constexpr int max_n = 2'000'000;
constexpr ull inf   = __UINT64_MAX__;

int n;
std::pair<ull, ull> C[max_n];

ull _N1, H1;
ull _N2, H2;

void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> C[i].first >> C[i].second;

    std::cin >> _N1 >> H1 >> _N2 >> H2;

    if (H1 > H2) {
        std::swap(_N1, _N2);
        std::swap(H1, H2);
    }
}

int back;  // tu zaczynamy wywracanie
int front; // tu konczymy  wywracanie

ull ans = 1;
ull max_ans;

ull N1, N2;

std::pair<ull, ull> U[max_n]; // uzyte klocki miedzy [i, i + 1], H1, H2

void clear_state() {
    back    = 0;
    front   = 0;

    ans     = 1;
    max_ans = 0;

    N1 = _N1;
    N2 = _N2;
}

bool front_max() {
    return (front == n - 1);
}

bool empty() {
    return (back == front);
}

ull mN1; // klocki uzyte
ull mN2;

bool can_push() {
    int next = front + 1;

    ull cx = C[front].first;
    ull nx = C[next].first;

    cx += C[front].second;

    // nie dziala reverse
    ull delta = nx - cx;

    // uzywamy wiekszych
    auto wieksze = std::min(
        N2, delta / H2
    );

    delta -= wieksze * H2;

    // patrzymy gdzie wiecej stracimy
    // na uzyciu dodatkowego duzego
    // czy na uzyciu samych malych

    ull strata_H2 = inf;
    if (N2 - wieksze) {
        strata_H2 = H2 - delta;
    }

    ull strata_H1 = inf;
    if (ull ilosc = (delta / H1 + (delta % H1 ? 1 : 0)); N1 >= ilosc) {
        strata_H1 = ilosc * H1 - delta;
    }

    if (strata_H1 == inf && strata_H2 == inf) return false;
    
    // uzyj wiekszego
    if (strata_H1 > strata_H2) {
        wieksze++;

        mN1 = 0;
        mN2 = wieksze;
    }
    // uzyj mniejszych dla dopelnienia
    else {
        wieksze++;  
    }

    return true;
}

void push_front() {
    front++;
    ans++;

    max_ans = std::max(max_ans, ans);

    N1 -= mN1;
    N2 -= mN2;
}

void pop_back() {
    N1 += U[back].first;
    N2 += U[back].second;

    back++;
    ans--;
}

void skip() {
    back++; front++;
}

ull solve() {
    clear_state();

    while (!front_max()) {
        while (true) {
            if (can_push()) break;
            if (empty()) skip();
            pop_back();
        }
        push_front();
    }

    return max_ans;
}

int main() {
    ull ans_forward = solve();

    // std::reverse(C, C + n);
    // ull ans_backward = solve();
    ull ans_backward = 0;

    std::cout << (std::max(ans_forward, ans_backward) + n);
}
