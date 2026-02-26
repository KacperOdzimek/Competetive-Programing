#include <iostream>
#include <vector>

// 1) zauwazmy ze niemoziwe jest istnienie ciagów arytmetycznych:
//      parzysta-parzysta-nieparzysta
//      parzysta-nieparzysta-nieparzysta
// 2) zloz generuje wiec najpierw parzyste liczby a potem nieparzyste
// 3) w parzystych i nieparzystych nie ma ciagów indukcyjnie

std::vector<int> zloz(int n) {
    if (n == 1) return {0};

    int parzyste_ilosc = (n + 1) / 2;
    int nieparzyste_ilosc = n / 2;

    std::vector<int> pp = zloz(parzyste_ilosc);
    std::vector<int> np  = zloz(nieparzyste_ilosc);

    std::vector<int> result;
    result.reserve(n);

    // najpierw liczby parzyste, z przenumerowaniem
    for (int x : pp) {
        result.push_back(2 * x);
    }

    // potem liczby nieparzyste, z przenumerowaniem
    for (int x : np) {
        result.push_back(2 * x + 1);
    }

    return result;
}

int main() {
    int n; std::cin >> n;
    auto ans = zloz(n);
    for (int x : ans) std::cout << x << "\n";
    return 0;
}
