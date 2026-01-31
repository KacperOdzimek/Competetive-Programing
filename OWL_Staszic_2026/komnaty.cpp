#include <iostream>
#include <cstring>
#include <climits>

using ull = unsigned long long;

constexpr ull inf   = ULLONG_MAX;
constexpr int max_n = 1000;

int         n, m;
ull         k;
std::string seq;

// czy bylismy juz tutaj po pelnym okrazeniu?
ull                 occ[max_n];
std::pair<int, int> adj[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        int l, p; std::cin >> l >> p; l--; p--;
        adj[i] = {l, p};
        occ[i] = inf;
    }

    std::cin >> seq;

    bool time_travel_used = false;
    int  where_am = 0;

    ull okrazenie = 0;
    while (okrazenie < k) {
        // juz tu bylismy!
        if (occ[where_am] != inf && !time_travel_used) {
            // tyle minelo
            ull delta_k = okrazenie - occ[where_am];

            ull missing = k - okrazenie;
            ull skiped  = (missing / delta_k) * delta_k;

            // podroz w czasie
            okrazenie += skiped;

            // ale nie do momentu zakonczenia!
            if (okrazenie == k) okrazenie -= delta_k;

            time_travel_used = true;
        }
        // nie bylsimy tu jeszczse
        else {
            occ[where_am] = okrazenie;
        }

        for (int i = 0; i < m; i++) {
            bool lewo = (seq[i] - 'P');
            int  next = lewo ? adj[where_am].first : adj[where_am].second;
            where_am = next;
        }

        okrazenie++;
    }

    std::cout << (where_am + 1);
}

/*
6 2 1001
2 1
3 1
4 1
5 1
6 1
4 1
LL
*/

/*
2 1 1001
2 -1
1 -1
L
*/