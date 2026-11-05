// Liczba rund = liczba takich inwersji ze roznia sie o jeden co do wartosci
// A mniejsza jest po wiekszej; No i plus jeden bo jakies przejscie musi byc

#include <bits/stdc++.h>
constexpr int max_n = 2 * 100000 + 1;

int n, q;

int V[max_n];   // Values
int P[max_n];   // Values positions

int lesser_inversion(int value) {
    int lesser = value - 1;
    if (lesser > 0 && P[value] < P[lesser]) return 1;
    return 0;
}

int greater_inversion(int value) {
    int greater = value + 1;
    if (greater <= n && P[greater] < P[value]) return 1;
    return 0;
}

int main() {
    std::cin >> n >> q; 
    for (int i = 0; i < n; i++) {
        std::cin >> V[i]; P[V[i]] = i;
    }; 

    int inw = 0;
    for (int i = 0; i < n; i++) {
        inw += greater_inversion(i + 1);    // Inw of each pair (a, b) unique
    }

    while (q--) {
        int pa, pb; std::cin >> pa >> pb; pa--; pb--;
        int a = V[pa]; int b = V[pb];
        if (a > b) {    // let a be lesser
            std::swap(a, b);
            std::swap(pa, pb);
        }
        
        if (b - a != 1) {   // a, ..., b
            inw -= lesser_inversion(a) + greater_inversion(a);
            inw -= lesser_inversion(b) + greater_inversion(b);
        }
        else {              // a, b, ...
            inw -= lesser_inversion(a) + greater_inversion(a);
            inw -= greater_inversion(b);
        }

        std::swap(V[pa], V[pb]);
        std::swap(P[a], P[b]);

        if (b - a != 1) {
            inw += lesser_inversion(a) + greater_inversion(a);
            inw += lesser_inversion(b) + greater_inversion(b);
        }
        else {
            inw += lesser_inversion(a) + greater_inversion(a);
            inw += greater_inversion(b);
        }

        std::cout << inw + 1 << '\n';
    }
}
