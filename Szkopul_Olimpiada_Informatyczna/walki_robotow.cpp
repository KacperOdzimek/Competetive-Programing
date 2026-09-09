#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n; if (!(std::cin >> n)) return 0;

    std::vector<int> z_of_s(n + 1);
    for (int i = 0; i < n; i++) {
        int s, z; std::cin >> s >> z;
        z_of_s[s] = z;
    }

    int max_z = 0;
    int count_maximals = 0;
    
    int min_S_max = n + 1;
    int min_Z_max = n + 1;
    
    int max_S_non = 0;
    int max_Z_non = 0;

    for (int s = n; s >= 1; s--) {
        int z = z_of_s[s];
        
        if (z > max_z) {
            // Znaleźliśmy element maksymalny
            count_maximals++;
            max_z = z;
            min_S_max = std::min(min_S_max, s);
            min_Z_max = std::min(min_Z_max, z);
        } 
        else {
            // Element zdominowany
            max_S_non = std::max(max_S_non, s);
            max_Z_non = std::max(max_Z_non, z);
        }
    }

    if (count_maximals % 2 == 0) {
        std::cout << "TAK\n";
    } 
    else {
        if (max_S_non < min_S_max && max_Z_non < min_Z_max) std::cout << "NIE\n";
        else std::cout << "TAK\n";
    }

    return 0;
}
