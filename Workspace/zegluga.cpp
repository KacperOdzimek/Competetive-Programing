#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

constexpr int max_n = 25'000;
constexpr int max_c = 2500;

int n;

struct wyspa {
    int i, j;
    int idx;
};

bool operator<(const wyspa& a, const wyspa& b) {
    if (a.i < b.i) return true;
    return (a.j < b.j);
}

wyspa            C  [max_n];
std::vector<int> adj[max_n];
long long        ans[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n;
    for (int itr = 0; itr < n; itr++) {
        int i, j; std::cin >> i >> j;
        C[itr] = {i, j, itr};
    }

    // od najmniejszej, od najmniejszej
    // O(n log n)
    std::sort(C, C + n);

    for (int i = 0; i < n; i++) {
        
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << '\n';
    }
}
