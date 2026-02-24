#include <iostream>
#include <sstream>
#include <vector>

// 1) prosty dp - dla kazdego bloku, dla kazdej mozliwej temperatury
//      trzymamy poprzednia temperature i laczny koszt (delte)
// 2) tym samym mozemy sledzic sciezke a przy tym minimalizowac koszty

constexpr int max_n = 144;
constexpr int max_t = 20;

struct record {
    short prev  = -1; // temperatura w poprzednim bloku
    short delta = 0;  // delta dla calego przejscia
};

int n;

// dla kazdej temperatury poczatkowej
// dla kazdego bloku
// dla kazdej temperatury koncowej
record R[max_n][max_t]; 
std::vector<short> S[max_n]; // sciezki

void load_line(int i) {
    std::string str; std::getline(std::cin, str);
    std::stringstream ss; ss << str;

    auto& vec = S[i];

    while (true) {
        int x = 128;
        ss >> x;
        if (x == 128) break;
        vec.push_back(x);
    }
}

void dfs_wypisz(int t, int s, int t1) {
    if (s == 0) return;

    int prev = R[s][t1].prev;
    dfs_wypisz(t, s - 1, prev);

    int delta = t1 - prev;
    std::cout << delta << ' ';
}

void sim(short t) {
    // czyszczenie r
    for (int s = 0; s <= n; s++)
        for (int i = 0; i < max_t; i++)
            R[s][i] = record();

    R[0][t].delta = 0; // poczatkowy stan

    // przejscie z 0 do 1
    for (short p : S[0]) {
        short new_temp = t + p;
        if (new_temp < 0 || new_temp >= max_t) continue;

        R[1][new_temp].delta = std::abs(p);
        R[1][new_temp].prev  = t;
    }

    // przejscie z s do s + 1
    for (int s = 1; s < n; s++) {
        for (int ts = 0; ts < max_t; ts++) {
            if (R[s][ts].prev == -1) continue; // nieosiagniety

            for (short p : S[s]) {
                short new_temp = ts + p;
                short delta = R[s][ts].delta + std::abs(p);

                if (new_temp < 0 || new_temp >= max_t) continue;

                auto& cel = R[s + 1][new_temp];
                if (cel.prev != -1 && cel.delta <= delta) continue;

                cel.prev  = ts;
                cel.delta = delta;
            }
        }
    }

    // odpowiedz
    int min_delta = 10000;
    int temp = -1;

    for (int i = 0; i < max_t; i++) {
        if (R[n][i].prev != -1 && R[n][i].delta < min_delta) {
            min_delta = R[n][i].delta;
            temp = i;
        }
    }

    if (temp == -1) std::cout << "NIE";
    else dfs_wypisz(t, n, temp);

    std::cout << "\n" << std::flush;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n; std::string y; std::getline(std::cin, y);
    for (int i = 0; i < n; i++) load_line(i);
    for (short t = 0; t < max_t; t++) sim(t);
}
