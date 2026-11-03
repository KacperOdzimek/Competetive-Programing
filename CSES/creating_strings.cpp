#include <bits/stdc++.h>
using ull = unsigned long long;
char C[27];

ull newton(ull n, ull k) {
    ull count = 1;
    for (int i = n - k + 1; i <= n; i++) count *= i;
    ull kfct = 1;
    for (int i = 1; i <= k; i++) kfct *= i;
    return count / kfct;
}

int main() {
    std::string str; std::cin >> str;
    for (int i = 0; i < str.size(); i++) C[str[i] - 'a']++;
    
    ull cnt = 1; int spots = str.size();
    for (int i = 0; i < 27; i++) {
        if (!C[i]) continue;
        cnt *= newton(spots, C[i]);
        spots -= C[i];
    }

    std::cout << cnt << '\n';
    std::sort(str.begin(), str.end());
    do {
        std::cout << str << '\n';
    } while(std::next_permutation(str.begin(), str.end()));
}