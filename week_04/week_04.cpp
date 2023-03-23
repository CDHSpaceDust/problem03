//https://github.com/CDHSpaceDust/problem_solving.git

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Node {
public:
    int value;
    vector<Node*> adj;
    bool visited;

    Node(int value) {
        this->value = value;
        this->visited = false;
    }
};

void dfs(Node* curr) {
    curr->visited = true;
    cout << curr->value << " ";
    for (Node* next : curr->adj) {
        if (!next->visited) {
            dfs(next);
        }
    }
}

void bfs(Node* start) {
    queue<Node*> q;
    q.push(start);
    start->visited = true;
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->value << " ";
        for (Node* next : curr->adj) {
            if (!next->visited) {
                next->visited = true;
                q.push(next);
            }
        }
    }
}

int main() {
    while (true) {
        cout << "노드 개수를 입력하세요 (종료하려면 0 입력): ";
        int n;
        cin >> n;
        if (n == 0) break;
        vector<Node*> nodes;
        for (int i = 1; i <= n; i++) {
            Node* node = new Node(i);
            nodes.push_back(node);
        }
        cout << "엣지 개수를 입력하세요: ";
        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cout << "엣지의 양 끝점을 입력하세요: ";
            cin >> u >> v;
            nodes[u - 1]->adj.push_back(nodes[v - 1]);
            nodes[v - 1]->adj.push_back(nodes[u - 1]);
        }
        for (Node* node : nodes) {
            sort(node->adj.begin(), node->adj.end(), [](Node* a, Node* b) {
                return a->value < b->value;
            });
        }
        cout << "시작 노드 값을 입력하세요: ";
        int startValue;
        cin >> startValue;
        Node* startNode = nodes[startValue - 1];
        dfs(startNode);
        cout << endl;
        for (Node* node : nodes) {
            node->visited = false;
        }
        bfs(startNode);
        cout << endl;
        // delete nodes;
    }
    return 0;
}
