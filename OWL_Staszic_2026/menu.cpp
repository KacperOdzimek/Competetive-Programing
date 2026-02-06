#include <iostream>
#include <climits>

using ull = unsigned long long;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    uint n, m;
    std::cin >> n >> m;

    ull max_color_1 = UINT_MAX;
    ull max_value_1 = 0;

    ull max_color_2 = UINT_MAX;
    ull max_value_2 = 0;

    for (int i = 0; i < n; i++) {
        uint a; short v; std::cin >> a >> v;
        
        ull max_base;
        if (a != max_color_1) max_base = max_value_1;
        else max_base = max_value_2;

        // wyjscie na minus nigdy nie jest oplacalne
        if (v < 0 && (ull)(-v) > max_base) continue;
        max_base += (ull)v;

        // detronizujemy 1
        if (max_base > max_value_1) {
            // niepozwalamy na 2 takie same kolory
            if (max_color_1 != a) {
                max_color_2 = max_color_1;
                max_value_2 = max_value_1;
            }

            max_color_1 = a;
            max_value_1 = max_base;
        }
        // detronizujemy 2, jezeli inny kolor niz 1
        else if (a != max_color_1 && max_base > max_value_2) {
            max_color_2 = a;
            max_value_2 = max_base;
        }
    }

    std::cout << max_value_1;
}
