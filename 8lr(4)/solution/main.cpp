#include <iostream>
#include <vector>
#include <cfloat>
#include <cmath>
#include <algorithm>


struct TLine {
    TLine(int n):line(n) {}
    TLine(const TLine& in):pos(in.pos), cost(in.cost), nonZero(in.nonZero), line(in.line) {}
    int pos;
    int cost;
    int nonZero;
    std::vector<double> line;
    inline double& operator[](int i){
        return line[i];
    }
    inline TLine& operator-=(const TLine& a) {
        for(int i = 0; i < line.size(); i++) {
            line[i] -= a.line[i];
            if (abs(line[i]) < DBL_EPSILON * 10000) {
                line[i] = 0;
            }
        }
        return *this;
    }
    inline TLine operator*(const double a) {
        TLine out(*this);
        for(int i = 0; i < line.size(); i++) {
            out.line[i] = line[i] * a;
            if (abs(out.line[i]) < DBL_EPSILON * 10000) {
                line[i] = 0;
            }
        }
        return out;
    }
};

inline bool operator< (const TLine& a, const TLine& b) noexcept {
    return a.cost < b.cost;
}

int main() {
    std::ios::sync_with_stdio(false);
    int m;
    int n;
    std::cin >> m >> n;
    std::vector<TLine> matrix(n, TLine(n));
    std::vector<TLine> lines(m, TLine(n));
    for(int i = 0; i < m; i++) {
        lines[i].pos = i + 1;
        for(int j = 0; j < n; j++) {
            std::cin >> lines[i].line[j];
        }
        std::cin >> lines[i].cost;
    }
    std::sort(lines.begin(), lines.end());
    int lineCnt = 0;
    bool found = false;

    for(int i = 0; i < m && !found; i++) {
        matrix[lineCnt] = lines[i];
        for (int j = 0; j < lineCnt; j++) {
            if(abs(matrix[lineCnt][matrix[j].nonZero]) > DBL_EPSILON) {
                matrix[lineCnt] -= matrix[j] * matrix[lineCnt][matrix[j].nonZero];
            }
        }
        for (int j = 0; j < n; j++) {
            if(abs(matrix[lineCnt][j]) > DBL_EPSILON) {
                matrix[lineCnt].nonZero = j;
                matrix[lineCnt] = matrix[lineCnt] * (1 / matrix[lineCnt][j]);
                lineCnt++;
                if (lineCnt == n) {
                    found = true;
                }
                break;
            }
        }
    }
    if(lineCnt != n) {
        std::cout << -1 << '\n';
    } else {
        std::vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            ans[i] = matrix[i].pos;
        }
        std::sort(ans.begin(), ans.end());
        for(int i = 0; i < n; i++) {
            std::cout << ans[i] << ' ';
        }
        std::cout << '\n';
    }
    
    return 0;
}
