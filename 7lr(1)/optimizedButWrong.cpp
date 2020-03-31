#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

struct TValue {
    TValue(): size(0), value(0){}
    TValue(int size, int value): size(size), value(value) {}
    int size;
    int value;
};

inline bool cmp(const TValue &a, const TValue &b) {
    return a.value * a.size < b.value * b.size;
}

template<class a>
inline void insertionSort(a begin, int n) {  
    int i, j; 
    TValue key; 
    for (i = 1; i < n; i++) 
    {  
        key = *(begin + i);  
        j = i - 1;  
        while (j >= 0 && cmp(*(begin + j), key)) 
        {  
            *(begin + j + 1) = *(begin + j);  
            j--;  
        }  
        *(begin + j + 1) = key;  
    }  
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    int m;
    std::cin >> n >> m;
    n++;
    m++;
    //TValue table[100][5000][10];
    //std::array<int, 10> h;
    std::vector<std::vector<std::array<TValue, 5001>>> table(101, std::vector<std::array<TValue, 5001>>(101));
    //std::array<std::array<std::array<TValue, 3>, 100>, 100> table;
    // for(int i = 0; i < 1000; i++) {
    //     table[i].resize(5000, );
    //     for(int j = 0; j < 5000; j++) {
    //         table[i][j].resize(10);
    //     }
    // }
    std::vector<TValue> shift(n);
    int mass;
    int value;
    int max_size;
    int l;
    int k;
    int i;
    int j;
    int p;
    std::vector<TValue> tmp(n);
    for(i = 1; i < n; i++) {
        std::cin >> mass >> value;
        shift[i].size = mass;
        shift[i].value = value;
        for(j = 0; j < m; j++) {
            if(j - mass >= 0) {
                l = 0;
                k = 0;
                tmp[l].size = table[i - 1][k][j - mass].size + 1;
                tmp[l].value = table[i - 1][k][j - mass].value + value;
                l++;
                k++;
                while(table[i - 1][k][j - mass].size != 0 || table[i - 1][k][j - mass].value != 0) {
                    tmp[l].size = table[i - 1][k][j - mass].size + 1;
                    tmp[l].value = table[i - 1][k][j - mass].value + value;
                    l++;
                    k++;
                }
                k = 0;
                while(table[i - 1][k][j].size != 0 || table[i - 1][k][j].value != 0) {
                    tmp[l] = table[i - 1][k][j];
                    k++;
                    l++;
                }
                insertionSort(tmp.begin(), l);
                max_size = tmp[0].size;
                p = 0;
                table[i][p][j] = tmp[0];
                p++;
                for(k = 1; k < l; k++) {
                    if(tmp[k].size > max_size) {
                        max_size = tmp[k].size;
                        table[i][p][j] = tmp[k];
                        p++;
                    }
                }
                
            } else {
                k = 0;
                table[i][k][j] = table[i - 1][k][j];
                k++;
                while(table[i - 1][k][j].size != 0 || table[i - 1][k++][j].value != 0) {
                    table[i][k][j] = table[i - 1][k][j];
                    k++;
                }
            }
        }
    }
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         //std::cout << table[i][j].value << ' ' << table[i][j].size <<  '\t';
    //         std::cout << table[i][j].size() << '\t';
    //     }
    //     std::cout << '\n';
    // }
    int max;
    int curr_val = table[n - 1][0][m - 1].value;
    int curr_size = table[n - 1][0][m - 1].size;
    max = curr_val * curr_size;
    i = 1;
    while(table[n - 1][i][m - 1].size != 0 || table[n - 1][i][m - 1].value != 0) {
        if (table[n - 1][i][m - 1].value * table[n - 1][i][m - 1].size > max) {
            curr_val = table[n - 1][i][m - 1].value;
            curr_size = table[n - 1][i][m - 1].size;
            max = curr_val * curr_size;
        }
        i++;
    }
    std::cout << max << '\n';
    i = n - 1;
    j = m - 1;
    bool up = false;
    std::vector<int> ans;
    ans.reserve(100);
    while(curr_size > 0) {
        up = false;
        k = 0;
        while(table[i - 1][k][j].size != 0 || table[i - 1][k][j].value != 0) {
            if(curr_size == table[i - 1][k][j].size && curr_val == table[i - 1][k][j].value) {
                up = true;
                break;
            }
            k++;
        }

        if(!up) {
            ans.push_back(i);
            j -= shift[i].size;
            curr_size--;
            curr_val -= shift[i].value;
        }
        i--;
    }

    for(k = ans.size() - 1; k >= 0; k--) {
        std::cout << ans[k] << ' ';
    }
    std::cout << '\n';
    return 0;
}
