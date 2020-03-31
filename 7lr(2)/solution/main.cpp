#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    long long* table = new long long[n + 1]{0};
    for(long long i = n - 1; i > 0; i--) {
        if (i * 2 <= n) {
            if (i * 3 <= n) {
                table[i] = std::min(table[i + 1] + i + 1, std::min(table[i * 3] + i * 3, table[i * 2] + i * 2));
            } else {
                table[i] = std::min(table[i + 1] + i + 1, table[i * 2]+ i * 2);
            }
        } else {
            table[i] = table[i + 1] + i + 1;
        }
        if (table[i] > INT32_MAX) {
            table[i] = INT32_MAX;
        } 
    }

    int i = 1;
    std::cout << table[1] << '\n';
    std::vector<std::string> ans;
    while(table[i] > 0) {
        if(i * 3 <= n) {
            if(table[i * 3] + i * 3 == table[i]) {
                i *= 3;
                ans.push_back("/3");
            } else if (table[i * 2] + i * 2 == table[i]) {
                i *= 2;
                ans.push_back("/2");
            } else {
                i++;
                ans.push_back("-1");
            }
        } else if (i * 2 <= n) {
            if (table[i * 2] + i * 2 == table[i]) {
                i *= 2;
                ans.push_back("/2");
            } else {
                i++;
                ans.push_back("-1");
            }
        } else { 
            i++;
            ans.push_back("-1");
        }
    }
    for(int k = ans.size() - 1; k >= 0; k--) {
        std::cout << ans[k] << ' ';
    }
    std::cout << '\n';
    delete[] table;
    return 0;
}
