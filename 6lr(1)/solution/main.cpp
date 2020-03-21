#include <iostream>
#include <vector>
#include <string>
#include "LongArifm.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    TULongInteger a;
    TULongInteger b;
    char oper;
    while (std::cin >> a >> b >> oper) {
        switch (oper) {
        case '+':
            try {
                std::cout << a + b << '\n';
            } catch(...) {
                std::cout << "Error\n";
            }
            break;
        case '-':
            try {
                std::cout << a - b << '\n';
            } catch(...) {
                std::cout << "Error\n";
            }
            break;
        case '*':
            try {
                std::cout << a * b << '\n';
            } catch(...) {
                std::cout << "Error\n";
            }
            break;
        case '/':
            try {
                std::cout << a / b << '\n';
            } catch(...) {
                std::cout << "Error\n";
            }
            break;
        case '^':
            try {
                std::cout << (a ^ b) << '\n';
            } catch(...) {
                std::cout << "Error\n";
            }
            break;
        case '=':
            a == b ? std::cout << "true\n" : std::cout << "false\n";
            break;
        case '>':
            a > b ? std::cout << "true\n" : std::cout << "false\n";
            break;
        case '<':
            a < b ? std::cout << "true\n" : std::cout << "false\n";
            break;
        }
    }
    return 0;
}
