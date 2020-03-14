#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

const int MAX_CHAR = 27;
const int aASCIIcode = 97;

class TSuffTree {
public:
    TSuffTree(std::string& text_in): text(text_in) {
        lastNewNode = NULL;
        activeNode = NULL;
        activeEdge = -1;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = -1;

        int* rootEnd = new int;
        *rootEnd = -1;
        root = new Node(-1, rootEnd, NULL);
        activeNode = root;
        for (int i = 0; i < text.size(); i++) {
            extendSuffixTree(i);
        }
        root->setSuffixIndexes(text.size(), 0);
    }

    void printSuffixesTest() {
        printSuffixes(root, 0);
    }
    void printt() {
        root->printt(text, 0);
    }

    std::vector<int> matchStatistics(std::string& text_m) {

        activeNode = root;
        activeEdge = -1;
        activeLength = 0;
        std::vector<int> matchStat(text_m.size());
        if (text_m.size() == 0) {
            return matchStat;
        }
        int pos = 0;
        matchStat[0] = findMatchStatI(text_m, pos, 0, 0);
        for(int curPos = 1; curPos < text_m.size(); curPos++) {
            matchStat[curPos] = findMatchStatI(text_m, pos, curPos,  matchStat[curPos - 1]);
        }
        return matchStat;

    }
    int findMatchStatI(std::string& text_m, int& pos, int i, int last_ms) {
        int matchStat;
        if (last_ms == 0) {
            matchStat = 0;
            pos = i;
        } else {
            matchStat = last_ms - 1;
        }
        Node *next;
        while (true) {
            if (pos >= text_m.size()) {
                break;
            }
            if (activeLength == 0) {
                activeEdge = pos; 
            }
            if (activeNode->children[(int)text_m[activeEdge] - aASCIIcode] == NULL) {
                break;
            } else {
                next = activeNode->children[(int)text_m[activeEdge] - aASCIIcode];
                if (walkDown(next)) {
                    continue;
                }
                if (text[next->start + activeLength] == text_m[pos]) {
                    matchStat++;
                    activeLength++;
                    pos++;
                } else {
                    break;
                }
            }
        }
        if (activeNode == root && activeLength > 0) {
            activeEdge = pos - activeLength + 1;
            activeLength--;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink;
        }
        return matchStat;
    }

    ~TSuffTree() {
        delete root;
    }


private:
    struct Node {

        Node(int start, int *end, Node *suffixLink) : children{NULL}, suffixLink(suffixLink),  start(start), end(end){
            suffixIndex = -1;
        }
        int edgeLength()
        {
            return *end - start + 1;
        }

        void printt(std::string& text, int deep) {
            
            for(int i = 0; i < deep; i++) {
                std::cout << '\t';
            }
            for(int i = start; i <= *end; i++) {
                std::cout << text[i];
            }
            for (int i = 0; i < MAX_CHAR; i++) {
                if (children[i] != NULL) {
                    std::cout << '\n' << (char)i;
                    children[i]->printt(text, deep + 1);
                }
            }
        }

        void setSuffixIndexes(int size, int labelHeight){
            int leaf = 1;

            for (int i = 0; i < MAX_CHAR; i++) {
                if (children[i] != NULL) {
                    leaf = 0;
                    children[i]->setSuffixIndexes(size, labelHeight + children[i]->edgeLength());
                }
            }
            if (leaf == 1) {
                suffixIndex = size - labelHeight;
            }
        }

        ~Node() {
            for (int i = 0; i < MAX_CHAR; i++) {
                if (children[i] != NULL) {
                    delete children[i];
                }
            }

            if (suffixIndex == -1) {
                delete end;
            }
        }

        

        Node* children[MAX_CHAR];
        Node* suffixLink;

        int start;
        int* end;
        int suffixIndex;
    };

    int walkDown(Node* currNode) {

        if (activeLength >= currNode->edgeLength()) {
            activeEdge += currNode->edgeLength();
            activeLength -= currNode->edgeLength();
            activeNode = currNode;
            return 1;
        }

        return 0;
    }

    void extendSuffixTree(int pos) {
        leafEnd = pos;
        remainingSuffixCount++;
        lastNewNode = NULL;

        Node *next;
        int* splitEnd;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0) {
                activeEdge = pos;
            }


            if (activeNode->children[(int)text[activeEdge] - aASCIIcode] == NULL) {

                activeNode->children[(int)text[activeEdge] - aASCIIcode] = new Node(pos, &leafEnd, root);
                if (lastNewNode != NULL) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
            } else {
                next = activeNode->children[(int)text[activeEdge] - aASCIIcode];
                if (walkDown(next)) {
                    continue;
                }

                if (text[next->start + activeLength] == text[pos]) {
                    if (lastNewNode != NULL && activeNode != root) {
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = NULL;
                    }

                    activeLength++;
                    break;
                }

                splitEnd = new int;
                *splitEnd = next->start + activeLength - 1;
                Node *split = new Node(next->start, splitEnd, root);
                activeNode->children[(int)text[activeEdge] - aASCIIcode] = split;
                split->children[(int)text[pos] - aASCIIcode] = new Node (pos, &leafEnd, root);
                next->start += activeLength;
                split->children[(int)text[next->start] - aASCIIcode] = next;

                if (lastNewNode != NULL) {
                    lastNewNode->suffixLink = split;
                }

                lastNewNode = split;
            }

            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }

    void print(int i, int j) {
        for (int k = i; k <= j; k++) {
            std::cout << text[k];
        }
    }


    
    void printSuffixes(Node *n, int labelHeight)
    {
        if (n == NULL)
            return;

        if (n->start != -1) {
            print(n->start, *(n->end));
        }

        for (int i = 0; i < MAX_CHAR; i++)

        {

            if (n->children[i] != NULL)

            {

                if (n->suffixIndex != -1) {
                    std::cout << '[' << n->suffixIndex << "]\n";
                }

                printSuffixes(n->children[i], labelHeight + n->children[i]->edgeLength());
            }
        }
        if (n->suffixIndex != -1) {
            std::cout << '[' << n->suffixIndex << "]\n";
        }
    }

    std::string& text;
    Node *root;

    Node* lastNewNode = NULL;
    Node* activeNode = NULL;

    int activeEdge = -1;
    int activeLength = 0;

    int remainingSuffixCount = 0;
    int leafEnd = -1;
};
