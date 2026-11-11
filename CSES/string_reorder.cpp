#include <bits/stdc++.h>
int C[26]; int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    std::string s; std::cin >> s;

    for (char c : s) C[c - 'A']++;
    std::string ans;

    int prev = -1; int n = s.size();
    for (int pos = 0; pos < n; pos++) {
        int mx1 = 0, mx2 = 0, id = -1;
        for (int i = 0; i < 26; i++) {
            if (C[i] > mx1) {
                mx2 = mx1;
                mx1 = C[i];
                id = i;
            }
            else if (C[i] > mx2) {
                mx2 = C[i];
            }
        }

        bool found = false;
        int rem = n - pos - 1;
        for (int i = 0; i < 26; i++) {
            if (C[i] == 0 || i == prev) continue;
            int mx = std::max(C[i] - 1, i == id ? mx2 : mx1);

            // Check whether the remaining string is possible.
            if (mx > (rem + 1) / 2) continue;
            if (rem % 2 == 1 && C[i] - 1 == (rem + 1) / 2) continue;

            ans += char('A' + i);
            C[i]--; prev = i;
            found = true;
            break;
        }

        if (!found) {
            std::cout << "-1\n";
            return 0;
        }
    }

    std::cout << ans << '\n';
}
