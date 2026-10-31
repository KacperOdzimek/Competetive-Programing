/*
1)  Dwa sklejone teksty sa palindromem jezeli
    ten krotszy dopelnia ten dluzszy 
    to znaczy jest odpowiednio jego prefikso-sufiksem
2) Mozemy wiec wiazc krotsze slowo na trie
    Wszystkie slowa nizej w poddrzewie, jezli sciezka do nich
    jest palindromem to zlepienie tez jest
    (palindrom + palindrom + palindrom daje palindrom)
3) Idac w dol od slowa do innego slowa wiemy:
    - Ze jest jego prefiksem
    - Trzeba sprawdzic czy jest sufiksem
    - Trzeba sprawdzic czy srodek jest palindromem
4) Trzeba by znac hasze prefikosowe w kazdym slowie 
    zeby sprawdzac palindromicznosc srodka
5) Sprawdzanie czy jest sufiksem rowniez robimy haszem
6) Najlepiej napisac podwojne hasze
7) Wobec tego zlozonosc haszowania:         O(S)
8) Wobec tego zlozonosc sprawdzenia pary:   O(1)
8) Wobec tego zlozonosc przejscia:          O(S)
*/

#include <bits/stdc++.h>
constexpr int max_s = 2'000'000;

// Trie
struct node {
    bool is_word;
    int  child[26];
};
int  TI = 1;
node T[max_s + 1];

void laduj() {
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n; for (int i = 0; i < n; i++) {
        int l; std::cin >> l; std::string s; std::cin >> s;

        // Wepchnij w trie
        int t = 0; for (auto c : s) {
            int child = T[t].child[c - 'a'];
            if (!child) {
                child = TI++;
                T[t].child[c - 'a'] = child;
                t = child;
            }
            t = child;
        } T[t].is_word = true;

        // Generuj hashe

    }
}

int main() {
    laduj();
    
}
