#include <bits/stdc++.h>
constexpr int max_n = 2 * 100000 + 1;
using ull = unsigned long long;

int n;
ull V[max_n];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    ull sum = 0; std::cin >> n; for (int i = 0; i < n; i++) {
        std::cin >> V[i]; sum += V[i];
    } std::sort(V, V + n);
    
    int ji = -1; int ki = n;
    ull jf = 0;  ull kf = 0;
    ull jr = 0;  ull kr = 0; // Time read; whole books
    ull wt = 0; while (true) {
        if (jf < kf) {
            kf -= jf; 
            if (ji != -1) jr += V[ji]; ji++;
            if (ji == ki) {
                wt = kr > kf ? 0 : kf - kr;
                break;
            }
            jf = V[ji];
        }
        else {
            jf -= kf;
            if (ki < n) kr += V[ki]; ki--; 
            if (ki == ji) {
                wt = jr > jf ? 0 : jf - jr; 
                break;
            }
            kf = V[ki];
        }
    }

    std::cout << (sum + wt);
}
