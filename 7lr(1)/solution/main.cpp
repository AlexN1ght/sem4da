#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    int m;
    int mass;
    int value;
    std::cin >> n >> m;
    n++; 
    m++;
    std::vector<std::vector<std::vector<int>>> table(n, std::vector<std::vector<int>>(n, std::vector<int>(m, 0)));
    std::vector<int> shift(n);
    for(int i = 1; i < n; i++) {
        std::cin >> mass >> value;
        shift[i] = mass;
        for(int j = 1; j <= i; j++) {
            for(int k = 0; k < m; k++) {
                if (k - mass >= 0) {
                    if (table[i - 1][j - 1][k - mass] != 0 || j - 1 == 0) {
                        table[i][j][k] = std::max(table[i - 1][j][k], table[i - 1][j - 1][k - mass] + value);
                    } else {
                        table[i][j][k] = table[i - 1][j][k];
                    }
                    
                } else {
                    table[i][j][k] = table[i - 1][j][k];
                }
            }
        }
    }
    int i, j, k;
    i = n - 1;
    k = m - 1;
    j = 0;
    int max = 0;
    for (int l = 0; l < n; l++) {
        if(table[i][l][k] * l > max) {
            max = table[i][l][k] * l;
            j = l;
        }
    }
    std::cout << max << '\n';
    std::vector<int> ans;
    while (j > 0) {
        if (table[i][j][k] != table[i - 1][j][k]) {
            j--;
            k -= shift[i];
            ans.push_back(i);
        }
        i--;
    }
    for(int k = ans.size() - 1; k >= 0; k--) {
        std::cout << ans[k] << ' ';
    }
    std::cout << '\n';
    return 0;
}
