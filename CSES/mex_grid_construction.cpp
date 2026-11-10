#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << (i ^ j) << " ";
        } std::cout << "\n";
    }
}