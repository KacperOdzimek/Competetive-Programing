#include <iostream>
#include <string>
#include <algorithm>

// 1) jako iz liczby sa bardzo duze implementujemy dodawanie pisemne na ciagach charow
// 2) dla prostoty trzymamy w buferach liczby co do wartosci, dopiero przy wypisywaniu enkodujemy
// 3) po prostu symulujemy program

constexpr int max = 67;
int buf1[max];
int buf2[max];

int* buf_cur  = buf1;
int* buf_next = buf2;

// true jezeli 1 lub 4
bool wypisz() {
    int itr = 66;

    // zera wiodace
    while (buf_cur[itr] == 0) itr--;

    // 1 lub 4
    if (itr == 0 && (buf_cur[itr] == 1 || buf_cur[itr] == 4)) {
        std::cout << buf_cur[itr] << '\n';
        return true;
    }

    while (itr >= 0) {
        std::cout << char('0' + buf_cur[itr]);
        itr--;
    }

    std::cout << ' ';
    return false;
}

void zestaw() {
    // wyczysc obecny buffer
    std::fill(buf1, buf1 + max, 0);

    // ustaw konfiguracje
    buf_cur  = buf1;
    buf_next = buf2;

    // wypelnij pierwszy bufer, tak ze pierwsza wartosc -> pierwsza cyfra
    std::string str; std::cin >> str;
    for (int i = 0; i < str.size(); i++) buf_cur[str.size() - i - 1] = (str[i] - '0');

    // tak dlugo az nie 1 lub 4
    while (!wypisz()) {
        // wyczysc next
        std::fill(buf_next, buf_next + max, 0);

        // dodawaj pisemnie
        for (int i = 0; i < max; i++) {
            // najwyzej dwucyfrowa
            int kwadrat  = buf_cur[i] * buf_cur[i];

            int jednosci = kwadrat % 10;
            buf_next[0] += jednosci;

            int dziesiatek = kwadrat / 10;
            if (buf_next[0] >= 10) {
                buf_next[0] -= 10;
                dziesiatek++;
            }

            int cargo = dziesiatek;
            int pos   = 1;

            while (cargo) {
                buf_next[pos] += cargo;
                cargo = buf_next[pos] / 10;
                buf_next[pos] %= 10;
                pos++;
            }
        }

        std::swap(buf_cur, buf_next);
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int t; std::cin >> t; 
    while (t--) zestaw();
}
