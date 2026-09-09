#include <bits/stdc++.h>

int main(){
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n, h; std::string str;
    std::cin >> n >> h >> str;

    long long depth = 0, cost = 0;
    for (int i = 0; i < n; i++){
        if (str[i] == '(') {
            if (depth < h) depth++;
            else { depth--; cost++; }
        } 
        else {
            if (depth > 0) depth--;
            else { depth++; cost++; }
        }
    }

    std::cout << cost;
}

// 20 1
// (((((((((())))))))))
