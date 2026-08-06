#include <bits/stdc++.h>

// Dla zapytania liczy sie moment w ktorym weszlismy na pole
// + o ile blokow przesunal sie wzorzec w wezu od tego czasu (stad zmienne "czas")

// Gdy przekaska - kolor = z zadania
// Gdy zapytanie - kolor = w moencie wejscia, index w wenzu
//                 czas  = numer ruchu
struct pozycje {
    int wiersz, kolumna, kolor, czas;
};

// Po pozycji
bool operator<(const pozycje& a, const pozycje& b) {
    if (a.wiersz != b.wiersz) return a.wiersz < b.wiersz;
    return a.kolumna < b.kolumna;
}

int m, p, n;
std::set<pozycje> Przekaski;
std::set<pozycje> Zapytania;

struct komenda {
    int czy_zapytanie;
    int kierunek_lub_wiersz;
    int kolumna;
};

std::vector<komenda> Komendy;

int czas = 0;
std::vector<int> Kolory = {0}; // Ostatni to glowa
int wiersz_glowa = 0, kolumna_glowa = 1; // Pozycja glowy, trzeba ruszyc w dol

void wykonaj_ruch(komenda k) {
    if (k.kierunek_lub_wiersz == 'P') kolumna_glowa++;
    if (k.kierunek_lub_wiersz == 'L') kolumna_glowa--;
    if (k.kierunek_lub_wiersz == 'G') wiersz_glowa--;
    if (k.kierunek_lub_wiersz == 'D') wiersz_glowa++;

    // Szukamy przekaski
    auto pitr = Przekaski.find({wiersz_glowa, kolumna_glowa});
    if (pitr != Przekaski.end()) {
        Kolory.push_back(pitr->kolor);
        Przekaski.erase(pitr);
    }
    else {
        czas++; // Kolory shiftuja w wezu tylko gdy nic nie zjadl
    }

    // Szukamy zapytania
    auto itr = Zapytania.find({wiersz_glowa, kolumna_glowa, 0}); // Szukaj po pozycji
    if (itr != Zapytania.end()) {
        pozycje p = *itr; Zapytania.erase(itr);
        p.czas = czas; p.kolor = Kolory.size() - 1; 
        Zapytania.insert(p);
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> m >> p >> n;
    for (int i = 0; i < p; i++) {   // Przekaski
        pozycje p; std::cin >> p.wiersz >> p.kolumna >> p.kolor;
        Przekaski.insert(p);
    }

    for (int i = 0; i < n; i++) {   // Ruchy
        komenda komenda = {.czy_zapytanie = 0};
        char k; std::cin >> k;
        if (k == 'Z') {
            komenda.czy_zapytanie = 1;
            std::cin >> komenda.kierunek_lub_wiersz >> komenda.kolumna;
            Zapytania.insert({komenda.kierunek_lub_wiersz, komenda.kolumna, -1, -1});
        }
        else {
            komenda.kierunek_lub_wiersz = k;
        }
        Komendy.push_back(komenda);
    }

    wykonaj_ruch((komenda){.kierunek_lub_wiersz = 'D'});
    for (auto k : Komendy) {
        if (k.czy_zapytanie) {
            auto itr = Zapytania.find({k.kierunek_lub_wiersz, k.kolumna, 0}); // szukaj po pozycji
            if (itr->czas == -1) {
                std::cout << "-1" << '\n';
                continue;
            }
            int mineo    = czas - itr->czas;
            int poczatek = itr->kolor;
            int index    = poczatek - mineo;
            if (index < 0) std::cout << "-1\n";
            else std::cout << Kolory[index] << '\n';
        }
        else {
            wykonaj_ruch(k);
        }
    }
}
