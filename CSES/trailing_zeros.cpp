// A zero appears when we mul by 10; 10 = 2 * 5
// There are more 2 that 5 so we dont care about 2
#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    ull n; std::cin >> n;
    ull ans = 0; for (ull i = 5; i <= n; i += 5) {
        ull v = i; while (v != 0 && v % 5 == 0) {
            v /= 5; ans++;
        }
    }
    std::cout << ans;
}
