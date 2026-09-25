#include <bits/stdc++.h>
using ll = long long;
std::mt19937 rng;

struct node {
    ll      rank = rng();
    node*   left;
    node*   right;
    ll      val;
    node(ll _val) : val(_val) {};
};

struct less_comparator {
    bool operator()(ll a, ll b) const {
        return a < b;
    }
};

struct lseq_comparator {
    bool operator()(ll a, ll b) const {
        return a <= b;
    }
};

// Zlacz drzewa
// TO NIE JEST przemienna operacja
// Musi trzymac niezmiennik treapa o kopcowym porzadku; Patrz insert
// Wszystko w p musi byc <= wartosci w q
node* join(node* p, node* q) {
    // Edge case'y:
    if (!p) return q;
    if (!q) return p;

    // Porzadek kopcowy po rank:
    // Rodzic ma wieksza wartosc od dzieci
    if (p->rank >= q->rank) {
        p->right = join(p->right, q);
        return p;
    }
    else {
        q->left = join(p, q->left);
        return q;
    }
}

// Rozlacz drzewa kopcowo; 
// Spelniajace operator z val na lewo
// Reszta na prawo
template<typename comparator>
std::pair<node*, node*> split(node* root, ll val) {
    if (root == nullptr) return {nullptr, nullptr};

    // Operator tutaj moze byc dowolny (przyjmijmy scisle mniejszy)
    // Jezeli korzen spelnia warunek comparatora, to korzen
    // oraz cale jego lewe poddrzewo musza trafic do lewej czesci.
    // Prawe rozwiazujemy rekurencynie i laczymy.
    if (comparator{}(root->val, val)) {
        auto [l, r] = split<comparator>(root->right, val);
        root->right = l;
        return {root, r}; // R to ta czesc prawego poddrzewa ktora okazala sie spelniac warunek
    }
    // Korzen NIE spelnia warunku, wiec korzen musi trafic
    // do prawej czesci. Pozostaje lewe poddrzewo:
    // jego elementy moga nalezec do obu czesci.
    else {
        auto [l, r] = split<comparator>(root->left, val);
        root->left = r;
        return {l, root};
    }
}

// Dodaj element do treapa
node* insert(node* root, ll val) {
    // Rozlam drzewo na mniejsze i wieksze do val
    // Dzieki temu mozna zakladac w split o porzadku nodow
    auto [l, r] = split<less_comparator>(root, val);
    node* n = new node(val);    // Allokuj nowy node
    return join(join(l, n), r); // Lacz drzewo razem
}

// Sksauj jeden element rowny val jezeli istnieje
// Przyklad szukania po wartosci
node* erase_one(node* root, ll val) {
    // Oszacuj b, c przez kolejno: 
    // Wykonanie rozlamu na mniejsze (b teraz blisko na prawo)
    // Wykonanie rozlamu na mniejsze rowne (b teraz z poddrzewem rownych na lewo w b)
    auto [a, bc] = split<less_comparator>(root, val);
    auto [b, c]  = split<lseq_comparator>(bc, val);
    
    // Mozemy skasowac wszystkie lub tylko jeden; Tutaj tylko jeden
    // Jezeli istnieje, kasujemy jego, laczymy poddrzewo w jeden node
    if (b != nullptr) {
        node* d = join(b->left, b->right);
        delete b;
        b = d;
    }
    
    // Skladamy drzewo z powrotem razem
    // Z mniejszych, rownych val oraz wiekszych
    return join(a, join(b, c));
}

// Rekursywne zwalnianie nodow
void free_tree(node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
} 

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
}
