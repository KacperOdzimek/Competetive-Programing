#include <bits/stdc++.h>
int main() {
    std::string str; std::cin >> str;
    int ans = 0; int len = 0; char type = 0;
    for (char c : str) {
        if (c == type) len++;
        else {
            ans  = std::max(ans, len);
            type = c; len = 1;
        }
    }
    ans = std::max(ans, len);
    std::cout << ans;
}