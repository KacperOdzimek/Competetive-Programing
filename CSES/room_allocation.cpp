#include <bits/stdc++.h>
constexpr int max_n = 200001;
using ll = long long;
int CR[max_n];  // Customer Room
int main() {
    std::vector<std::tuple<ll, bool, int>> E; // Departures later so they true
    int n; std::cin >> n; for (int i = 0; i < n; i++) {
        ll a, b; std::cin >> a >> b;
        E.push_back({a, false, i}); E.push_back({b, true, i});
    } std::sort(E.begin(), E.end());

    std::stack<int> R;  // Spare rooms
    int Ri = 0;         // Rooms iterator
    for (auto [x, d, i] : E) {
        if (CR[i] == 0) {
            if (R.empty()) R.push(++Ri);
            CR[i] = R.top(); R.pop();
        }
        else {
            R.push(CR[i]);
        }
    }
    
    std::cout << Ri << '\n';
    for (int i = 0; i < n; i++) std::cout << CR[i] << ' ';
}