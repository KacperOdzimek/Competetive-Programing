#include <bits/stdc++.h>

// Wejscie
const int max_n = 200'000;
int n; int IN[max_n];
void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n; for (int i = 0; i < n; i++) {
        std::cin >> IN[i];
    }
}

// Zadanie 1,2) Suma i K-zbiór
void pdz_1_2() {
    int k = IN[0];
    std::multiset<int> naj;
    unsigned long long sum_naj = 0;
    unsigned long long sum_rst = 0;

    for (int i = 1; i < n; i++) {
        naj.insert(IN[i]); sum_naj += IN[i];
        if ((int)naj.size() > k) {
            int najmniejsza = *naj.begin();
            naj.erase(naj.begin());
            sum_naj -= najmniejsza;
            sum_rst += najmniejsza;
        }
    }

    std::cout << (sum_naj + sum_rst + k) << '\n';
    std::cout << ((sum_naj > sum_rst) ? "TAK" : "NIE") << '\n';
}

// Zadanie 3 i 4) Dzielona Pamiec
std::vector<int>    adj[max_n + 5]; // Adjacency grafu
int                 sub[max_n + 5]; // Subtree elementu/Indegree
int                 mx[max_n + 5];  // Maksymalna składowa/Najdlsza sciezka do

// Zadanie 3) Centroid
int                 m;              // Liczba wierzchołków drzewa = n/3+1
int                 centroid = 0;

void dfs(int v, int p) {
    sub[v] = 1; mx[v] = 0;
    for (int w : adj[v]) {
        if (w == p) continue;       // Nie zawracaj
        dfs(w, v);                  // Wejdź do dziecka
        sub[v] += sub[w];           // Sumuj subtree
        mx[v] = std::max(mx[v], sub[w]);
    }
    // Największa składowa <= połowa
    if (2 * std::max(mx[v], m - sub[v]) <= m) centroid = v;
}

void pdz_3() {
    m = n / 3 + 1;
    for (int i = 0; i < n / 3; i++) {   // n/3 krawędzi = pierwsze 2n/3 liczb
        int u = IN[2 * i], v = IN[2 * i + 1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    std::cout << centroid << '\n';
}

// Podzadanie 4) Najdluzsza sciezka
// Sub to indegree
void pdz_4() {
    for (int i = 0; i <= n; i++) { 
        adj[i].clear(); sub[i] = 0; mx[i] = 0; 
    }
    
    std::set<int> U;    // Unique
    for (int i = 0; i < n; i += 2) {
        int u = IN[i], v = IN[i + 1];
        U.insert(u); U.insert(v);
        if (u > v) std::swap(u, v);
        adj[u].push_back(v); sub[v]++;
    }

    std::vector<int> Q, nQ;
    for (int x : U) if (!sub[x]) Q.push_back(x);

    int len = -1; while (!Q.empty()) {
        for (int v : Q) for (int w : adj[v]) if (!--sub[w]) nQ.push_back(w);
        std::swap(Q, nQ); nQ.clear(); len++;
    }

    std::cout << std::max(0, len) << '\n';
}

// Podzadanie 5) Liczba inwersji (gdy wieksza przed mniejsza)
const int max_tree = max_n + 5;
int tree[max_tree];

// Dodaje +1 do wystąpień danej wartości
void add(int idx) {
    for (; idx < max_tree; idx += idx & -idx) {
        tree[idx]++;
    }
}

// Zwraca sumę elementów na przedziale [1, idx]
int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += tree[idx];
    }
    return sum;
}

void pdz_5() {
    unsigned long long inw = 0;
    for (int i = 0; i < n; i++) {
        int val = IN[i] + 1; 
        inw += i - query(val);
        add(val);
    }
    std::cout << inw << '\n';
}

// Podzadanie 6) Nadluzszy rozsnancy podciag
constexpr int bigger_two = 262'144;
int tree6[bigger_two * 2];

void set6(int pos, int val) {
    pos += bigger_two;
    tree6[pos] = val;
    pos /= 2; while (pos) {
        tree6[pos] = std::max(tree6[pos * 2], tree6[pos * 2 + 1]);
        pos /= 2;
    }
}

int query6(int beg, int end) {
    beg += bigger_two; end += bigger_two;
    int result = 0; while (beg < end) {
        if (beg & 1) result = std::max(result, tree6[beg++]);
        if (end & 1) result = std::max(result, tree6[--end]);
        beg /= 2; end /= 2;
    }
    return result;
}

void pdz_6() {
    for (int i = 0; i < n; i++) {
        int val = IN[i];
        int naj = query6(0, val);   // Najdluszy ciag mniejszy od val
        set6(val, naj + 1);
    }
    std::cout << tree6[1];
}


// Podzadanie 7) Sklejenie
void pdz_7() {
    std::vector<int> A, B;
    
    for (int i = 0; i < n / 2; i++) {
        std::string s = std::to_string(IN[i]);
        for (char c : s) A.push_back(c - '0');
    }

    for (int i = n / 2; i < n; i++) {
        std::string s = std::to_string(IN[i]);
        for (char c : s) B.push_back(c - '0');
    }

    std::vector<int> wynik(A.size() + B.size(), 0);
    
    for (int i = A.size() - 1; i >= 0; i--) {
        for (int j = B.size() - 1; j >= 0; j--) {
            wynik[i + j + 1] += A[i] * B[j];
        }
    }

    int carry = 0; for (int i = wynik.size() - 1; i >= 0; i--) {
        wynik[i] += carry;
        carry = wynik[i] / 10;
        wynik[i] %= 10;
    }

    int start = 0; while (start < wynik.size() - 1 && wynik[start] == 0) {
        start++;
    }

    for (int i = start; i < wynik.size(); i++) {
        std::cout << wynik[i];
    }
    std::cout << '\n';
}

// Call Site

int main() {
    load();
    pdz_1_2();
    pdz_3();
    pdz_4();
    pdz_5();
    pdz_6();
    pdz_7();
}
