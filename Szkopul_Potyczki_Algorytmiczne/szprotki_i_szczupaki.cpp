/*
    Zadanie rozwiazujemy z użyciem struktury drzewa kopcowego (treapa)
    Kolejne zapytania tlumacza się na:
    - Typ 1: 
        Skoro szczupak zje minimalna liczbe szprotek do celu,
        to zawsze będzie zjadał największą szprotkę jaką może zjeść.
        Zawsze więc istnieje wybór - zjeść dużo mniejszych i osiągnąć wagę, czy zjeść tylko tyle by odblokować większe szprotki.
        Drzewo będziemy więc łamać wobec masy szprotek - najpierw wobec masy indywidualnej (jemy tylko te mniejsze od szczupaka)
        A potem wobec sumy poddrzewa (będzie nam potrzebne tylko k największych)
    - Typ 2: Dodanie do kopcodrzewa   (log n)
    - Typ 3: Usuniencie z kopcodrzewa (log n)
*/

#include <bits/stdc++.h>
using ull = unsigned long long;
std::mt19937 rng{};
 
// Fundament
 
struct node {
    int     rank  = rng();
    node*   left  = nullptr;
    node*   right = nullptr;
    ull     wielkosc;
    ull     suma;
    int     liczba;
    node(ull _wielkosc)
        : wielkosc(_wielkosc), suma(_wielkosc), liczba(1)
    {};
};
 
void pull(node* root) {
    if (root == nullptr) return;
    root->suma = root->wielkosc;
    root->liczba = 1;
    if (root->left) {
        root->suma += root->left->suma;
        root->liczba += root->left->liczba;
    }
    if (root->right) {
        root->suma += root->right->suma;
        root->liczba += root->right->liczba;
    }
}
 
node* join(node* left, node* right) {
    if (left  == nullptr) return right;
    if (right == nullptr) return left;
 
    if (left->rank >= right->rank) {
        left->right = join(left->right, right);
        pull(left); return left;
    }
    else {
        right->left = join(left, right->left);
        pull(right); return right;
    }
}
 
template<typename comparator>
std::pair<node*, node*> split(node* root, ull masa) {
    if (root == nullptr) return {nullptr, nullptr};
 
    // Root mniejszy : Porzadek bst wiec prawo nie wiadomo
    if (comparator{}(root->wielkosc, masa)) {
        auto [l, r] = split<comparator>(root->right, masa);
        root->right = l; // Na prawo zostaje tylko przedzial [root->wielkosc, masa]
        pull(root); return {root, r};
    }
    // Root wiekszy : Porzadek bst wiec lewo nie wiadomo
    else {
        auto [l, r] = split<comparator>(root->left, masa);
        root->left = r; // Na lewo zostaje tylko przedzial [masa, root->wielkosc]
        pull(root); return {l, root};
    }
}
 
// Zlozenia
 
node* insert(node* root, ull wielkosc) {
    auto [l, r] = split<std::less<ull>>(root, wielkosc);
    node* n = new node{wielkosc};
    return join(join(l, n), r);
}
 
std::tuple<node*, node*, node*> separate(node* root, ull wielkosc) {
    auto [l, xr] = split<std::less<ull>>(root, wielkosc);
    auto [x, r]  = split<std::less_equal<ull>>(xr, wielkosc);
    return {l, x, r};
}
 
node* erase_one(node* root, ull wielkosc) {
    auto [l, x, r] = separate(root, wielkosc);
    if (x != nullptr) {
        auto* d = join(x->left, x->right);
        delete x; x = d;
    }
    return join(join(l, x), r);
}
 
node* erase_all(node* root) {
    if (root != nullptr) {
        erase_all(root->left);
        erase_all(root->right);
        delete root;
    }
    return nullptr;
}
 
// Logika zadania

// Minimalna wartosc w drzewie
ull min_in_tree(node* root) {
    if (root == nullptr) return ULLONG_MAX / 2;
    while (root->left) root = root->left;
    return root->wielkosc;
}

// Wez plus minus wartosc sum z drzewa
// Lewe to niewziete pozostawione nody
// Prawe to wziete nody
// Spelnia wlasnosc ze kazda wartosc w L <= P
// Wykorzystujemy wlasnosc BST ze na lewo sa mniejsze
// A na prawo wieksze
std::pair<node*, node*> take_sum(node* root, ull sum) {
    if (root == nullptr) return {nullptr, nullptr};

    ull right_sum = (root->right != nullptr) ? root->right->suma : 0;

    // Przypadek 1: Prawe poddrzewo ma wystarczającą sumę.
    // Szukamy cięcia wewnątrz prawego poddrzewa, a korzeń i lewe poddrzewo zostają nietknięte.
    if (right_sum >= sum) {
        auto [l, r] = take_sum(root->right, sum);
        root->right = l;
        pull(root);
        return {root, r};
    }
    // Przypadek 2: Prawe poddrzewo + aktualny korzeń dają wystarczającą sumę.
    // Bierzemy cały prawy korzeń i prawą stronę, a odcinamy lewe poddrzewo jako "niewzięte".
    else if (right_sum + root->wielkosc >= sum) {
        node* l = root->left;
        root->left = nullptr;
        pull(root);
        return {l, root};
    }
    // Przypadek 3: Prawe poddrzewo i korzeń to za mało.
    // Musimy dobrać brakującą część sumy z lewego poddrzewa.
    else {
        ull needed = sum - right_sum - root->wielkosc;
        auto [l, r] = take_sum(root->left, needed);
        root->left = r;
        pull(root);
        return {l, root};
    }
}
 
int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n; node* root = nullptr;
    for (int i = 0; i < n; i++) {
        ull w; std::cin >> w;
        root = insert(root, w);
    }
 
    int q; std::cin >> q; while (q--) {
        int type; std::cin >> type;
        if (type == 1) {
            ull s, k; std::cin >> s >> k;

            std::vector<std::pair<node*, ull>> zjedzone;
            ull count = 0;
            while (s < k) {
                auto [A, B] = split<std::less<ull>>(root, s);
                if (A == nullptr) { root = B; break; }

                ull sum = std::min(k, min_in_tree(B) + 1) - s;

                auto [L, P] = take_sum(A, sum);
                zjedzone.push_back({P, s});      // zapamiętaj s SPRZED fazy
                s += P->suma; count += P->liczba;

                root = join(L, B);
            }

            if (s >= k) std::cout << count << '\n';
            else        std::cout << "-1\n";

            // Cofamy fazy od ostatniej do pierwszej
            for (int i = (int)zjedzone.size() - 1; i >= 0; i--) {
                auto [L, B] = split<std::less<ull>>(root, zjedzone[i].second);
                root = join(L, join(zjedzone[i].first, B));
            }
        }
        else if (type == 2) {   // Dodajemy szprotke o wadze w
            ull w; std::cin >> w;
            root = insert(root, w);
        }
        else if (type == 3) {   // Usuwamy jedna szprotke o wadze w
            ull w; std::cin >> w;
            root = erase_one(root, w);
        }
    }
 
    erase_all(root);
}
