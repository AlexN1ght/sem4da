#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>

class TGraph {
public:
    TGraph(const int size): size(size), nodes(size) {}
    void changeEdge(int from, int to, int waight) {
        if (waight == 0) {
            nodes[from].edges.erase(to);
        } else {
            nodes[from].edges[to] = Edge(&nodes[to], waight);
        }
        
    }

    std::pair<std::vector<int>, int> BFS(const int from,const int to) {
        std::vector<int> pre(size, -1);
        std::vector<bool> viseted(size, false);
        std::queue<std::pair<int, Node*>> q;
        std::pair<int, Node*> cur;
        std::pair<std::vector<int>, int> out({}, 0);

        q.push(std::pair<int, Node*>(from, &nodes[from]));
        viseted[from] = true;
        
        while(!q.empty()) {
            cur = q.front();
            q.pop();
            for(std::pair<int, Edge> edge : (*cur.second).edges) {
                if(!viseted[edge.first]) {
                    viseted[edge.first] = true;
                    pre[edge.first] = cur.first;
                    if(edge.first == to) {
                        out.first.push_back(to);
                        out.second = __INT_MAX__;
                        while(out.first.back() != from) {
                            if(nodes[pre[out.first.back()]].edges[out.first.back()].waight < out.second) {
                                out.second = nodes[pre[out.first.back()]].edges[out.first.back()].waight;
                            }
                            out.first.push_back(pre[out.first.back()]);
                        }
                        std::reverse(out.first.begin(), out.first.end());
                        return out;
                        break;
                    } else {
                        q.push(std::pair<int, Node*>(edge.first, edge.second.node));
                    }
                }
            }
        }
        return out;
    }

    int getWaight(const int from, const  int to) {
        if(nodes[from].edges.find(to) != nodes[from].edges.end()) {
            return nodes[from].edges[to].waight;
        }
        return 0;
    }

    void print() {
        for(int i = 0; i < size; i++) {
            std::cout << i << ": ";
            for(std::pair<int, Edge> edge : nodes[i].edges) {
                std::cout << edge.first << "(" << edge.second.waight << "), ";
            }
            std::cout << "\n";
        }
    }

private:
    struct Node;
    struct Edge {
        Edge(){}
        Edge(Node* node,const int waight): node(node), waight(waight){}
        Node* node;
        int waight;
    };
    struct Node {
        std::unordered_map<int, Edge> edges;
    };

    int size;
    std::vector<Node> nodes;

};
