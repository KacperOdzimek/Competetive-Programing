#include <iostream>
#include <vector>
#include <set>

constexpr int max = 5 * 100'000;

std::vector<int>   G[max]; // krawedzie z wiercholka
std::set<int>      T[max]; // szpiedzy  w wiercholku
std::vector<int>   S;      // odpowiedz

bool vis[max];
void dfs(int v) {
    vis[v] = true;

    auto& my = T[v];
    bool bedziemy_strzelac = false;

    for (int u : G[v]) {
        if (vis[u]) continue;
        dfs(u);
        
        // nie ma co
        if (bedziemy_strzelac) continue;

        // laczymy zbiory
        auto& oth = T[u];

        // optymalizacja na sciezkach:
        if (my.size() == 0) {
            my = std::move(oth);
            continue;
        }

        auto* a1 = &my;
        auto* a2 = &T[u];

        // niech a1 bedzie zawsze wiekszym zbiorem
        if (a1->size() < a2->size()) std::swap(a1, a2);

        // przenosimy a2 (mniejszy) do a1 (wiekszego)
        for (auto e : *a2) {
            bool scc = a1->insert(e).second;
            if (!scc) {
                bedziemy_strzelac = true;
                break;
            }
        }

        if (a1 == &my) oth = {};  // oczysc pamiec
        else my = std::move(*a1); // przenies zbior goscia do siebie
    }

    if (bedziemy_strzelac) {
        my.clear();
        S.push_back(v);
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // info
    int n, q; std::cin >> n >> q;

    // krawedzie
    for (int i = 0; i < n - 1; i++) {
        int a, b; std::cin >> a >> b; a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // szpiedzy
    for (int i = 0; i < q; i++) {
        int c, d; std::cin >> c >> d; c--; d--;
        T[c].insert(i);
        T[d].insert(i);
    }

    dfs(0);

    std::cout << S.size() << '\n';
    for (auto s : S) std::cout << (s + 1) << ' ';
}
