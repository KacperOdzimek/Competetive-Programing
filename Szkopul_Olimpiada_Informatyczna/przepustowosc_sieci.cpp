#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

// 1) przy uzyciu bfs zwiedzamy wszystkie wiercholki, tak dlugo jak mozemy poprawiac wyniki
// 2) jako iz moze byc wiele pytan dla tego samego poczatkowego wiercholka,
//      uzywamy optymalizacji zapytan offline

constexpr int max_n = 100;
constexpr int max_q = max_n * (max_n - 1);

struct edge {
    int x1, p;
};

struct quest {
    int x0, x1;
    int idx;
};

std::vector<edge> G[max_n]; // graf
int               M[max_n]; // maksymalna przepustowosc w sciezce [x0, v]

quest             Z[max_q]; // zapytania
int               A[max_q]; // odpowiedz dla i'tego zapytania

// generuje M
void bfs(int x0) {
    std::fill(M, M + max_n, 0);

    std::set<int> Q, nQ;
    Q.insert(x0);
    M[x0] = __INT_MAX__;

    while (Q.size()) {
        for (int v : Q) {
            for (edge e : G[v]) {
                int p = std::min(e.p, M[v]);
                if (M[e.x1] >= p) continue;
                M[e.x1] = p;
                nQ.insert({e.x1});
            }
        }

        Q.swap(nQ);
        nQ.clear();
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // laduj graf
    int n; std::cin >> n;
    for (int x0 = 0; x0 < n; x0++) {
        int lp; std::cin >> lp; G[x0].resize(lp);
        for (int i = 0; i < lp; i++) { 
            std::cin >> G[x0][i].x1 >> G[x0][i].p; 
            G[x0][i].x1--; 
        }
    }

    // laduj zapytania
    int q; std::cin >> q;
    for (int i = 0; i < q; i++) {
        std::cin >> Z[i].x0 >> Z[i].x1;  
        Z[i].x0--; Z[i].x1--;
        Z[i].idx = i;
    }

    // sortuj zapytania
    std::sort(Z, Z + q, [](const quest& l, const quest& r) {
        return l.x0 < r.x0;
    });

    // wygeneruj M pierwszy raz
    bfs(Z[0].x0);
    A[Z[0].idx] = M[Z[0].x1];

    // kolejne zapytania i potencjalne generowanie M
    for (int i = 1; i < q; i++) {
        if (Z[i - 1].x0 != Z[i].x0) bfs(Z[i].x0);
        A[Z[i].idx] = M[Z[i].x1];
    }

    // wypisz odpowiedzi
    for (int i = 0; i < q; i++) std::cout << A[i] << '\n';
}
