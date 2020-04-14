#include <iostream>
#include <vector>
#include "Graph.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    int m;
    std::cin >> n >> m;
    TGraph G(n + 1);

    int from;
    int to;
    int waight;
    for(int i = 0; i < m; i++) {
        std::cin >> from >> to >> waight;
        G.changeEdge(from, to, waight);
    }

    unsigned long long ans = 0;
    std::pair<std::vector<int>, int> path;
    path = G.BFS(1, n);
    while(path.second != 0) {
        ans += path.second;
        for(int i = 1; i < path.first.size(); i++) {
            G.changeEdge(path.first[i - 1], path.first[i], G.getWaight(path.first[i - 1], path.first[i]) - path.second);
            G.changeEdge(path.first[i], path.first[i - 1], G.getWaight(path.first[i], path.first[i - 1]) + path.second);
        }
        path = G.BFS(1, n);
    }
    std::cout << ans << '\n';
    return 0;
}
