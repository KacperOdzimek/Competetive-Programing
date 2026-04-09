#include <iostream>
#include <stack>

constexpr int max_n = 2000;

int n;
int D[max_n][max_n];
int H[max_n]; // ile jest zer w serii w kolumnie

int najwieksze_pole(int n) {
    std::stack<int> st;
    int max_area = 0;

    for (int i = 0; i <= n; i++) {
        int h = (i == n ? 0 : H[i]);

        while (!st.empty() && H[st.top()] > h) {
            int h = H[st.top()];
            st.pop();

            int l = st.empty() ? 0 : st.top() + 1;
            int r = i - 1;

            int width = r - l + 1;
            max_area = std::max(max_area, h * width);
        }

        st.push(i);
    }

    return max_area;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    std::cin >> n;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            std::cin >> D[x][y];
        }
    }

    int result = 0;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (D[x][y] == 0)   H[x] += 1;
            else                H[x] = 0;
        }
        result = std::max(result, najwieksze_pole(n));
    }

    std::cout << result << '\n';
}
