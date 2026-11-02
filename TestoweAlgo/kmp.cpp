#include <iostream>
#include <vector>

// Dlugosc najdluzszego prefiksu właściwego w punkcie
// Ktory jednoczesnie jest sufiksem w tym samym punkcie
// CO?
// A widzisz przyjmijmy napis "abaCabaC"
// Widzimy ze w punkcie 6 (ostatnim a)
// Dlugosc prefiksu == 3 (aba sie powtarza)
// Ergo jest on tez SUFIKSEM fragmentu "abaCaba"
std::vector<int> lps(const std::string& s) {
	std::vector<int> tab(s.size());
    tab[0] = 0; // pierwsza litera ofc nie moze byc prefiksem

    int j = 0; // iterator prefiksu
    int i = 1; // pozycja w lps / tekscie, jeden, bo zero juz rozwazlismy

	while (i < tab.size()) {
        if (s[i] == s[j]) { // znak pasuje, wiec prefiks rosnie
            j++;
            tab[i] = j;
            i++;
        }
        else if (j != 0) {  // probujemy mniejszego prefiksu
            j = tab[j - 1];
        }
        else {              // to wogole nie jest prefiks, wiec ustawiamy 0
            tab[i] = 0;
            i++;
        }
    }

    return tab;
}

std::vector<int> match(
    const std::string& s,
    const std::string& ptr, 
    const std::vector<int>& lps
) {
    std::vector<int> res;

    int i = 0; // iterator w tekscie
    int j = 0; // iterator we wzorcu

    while (i < s.size()) {
        // pasuja, wiec przesuwamy i wzorzec i tekst
        if (s[i] == ptr[j]) {
            i++; j++;

            if (j == ptr.size()) {
                res.push_back(i - j); // i to teraz koniec wzorca wiec cofamy sie
                j = lps[j - 1];
            }
        }
        // nie pasuja
        else {
            if (j != 0) { // probujemy przylozyc tekst "wczesciej"
                j = lps[j - 1]; 
            }
            else {  // nie da rady idziemy dalej
                i++;
            }
        } 
    }

    return res;
}

void solve() {
    int n; std::cin >> n;
    std::string ptr, str; std::cin >> ptr >> str;

    auto tab = lps(ptr);
    for (int pos : match(str, ptr, tab)) {
        std::cout << pos << '\n';
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int T; std::cin >> T;
    while (T--) solve();
}
