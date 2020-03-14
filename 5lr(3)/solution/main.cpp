#include <iostream>
#include <vector>
#include <string>
#include "SuffixTree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::string pattern;
    std::string text;
    
    getline(std::cin, pattern);
    int patSize = pattern.size();
    pattern += '{';
    TSuffTree test(pattern);
    getline(std::cin, text);
    std::vector<int> matchStat = test.matchStatistics(text);

    for (int i = 0; i < matchStat.size(); i++) {
        if(matchStat[i] == patSize) {
            std::cout << i + 1 << '\n';
        }
    }
    return 0;
}
