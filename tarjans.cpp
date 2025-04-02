#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Tarjan_algorithm {
    int V;
    vector<vector<int>> adjlist;
    vector<int> ids;
    vector<int> low;
    vector<bool> onStack;
    stack<int> stack_visited;
    int id;
    vector<vector<int>> sccs;
    unordered_map<char, int> vertex_map;
    vector<char> vertices;

    void printStack() {
        stack<int> temp = stack_visited;
        cout << "Stack elements: ";
        while (!temp.empty()) {
            cout << (char)(temp.top() + 'A') << " ";
            temp.pop();
        }
        cout << endl;
    }

    void dfs(int i) {
        stack_visited.push(i);
        onStack[i] = true;
        ids[i] = low[i] = id++;

        for (int j : adjlist[i]) {
            if (ids[j] == -1) {
                dfs(j);
                low[i] = min(low[i], low[j]);
            } else if (onStack[j]) {
                low[i] = min(low[i], ids[j]);
            }
        }

        if (ids[i] == low[i]) {
            cout << "Before popping, ";
            printStack();

            vector<int> scc;
            vector<int> scc_low_values;
            while (!stack_visited.empty()) {
                int node = stack_visited.top();
                stack_visited.pop();
                onStack[node] = false;
                scc.push_back(node);
                scc_low_values.push_back(low[node]);
                if (node == i) break;
            }
            sccs.push_back(scc);

            cout << "After popping, ";
            printStack();

            cout << "SCC found: ";
            for (int node : scc) {
                cout << (char)(node + 'A') << " ";
            }
            cout << endl;

            cout << "Low-link values for this SCC: ";
            for (int low_val : scc_low_values) {
                cout << low_val << " ";
            }
            cout << endl;
        }
    }

public:
    Tarjan_algorithm(int V) : V(V), adjlist(V), ids(V, -1), low(V, -1), onStack(V, false), id(0) {
        for (int i = 0; i < V; ++i) {
            vertices.push_back((char)(i + 'A'));
            vertex_map[vertices[i]] = i;
        }
    }

    void addEdge(char u, char v) {
        adjlist[vertex_map[u]].push_back(vertex_map[v]);
    }

    void findSCCs() {
        for (int i = 0; i < V; ++i) {
            if (ids[i] == -1) {
                dfs(i);
            }
        }
    }
};

int main() {
    int V = 10;
    Tarjan_algorithm tarjan(V);

    tarjan.addEdge('A', 'B');
    tarjan.addEdge('B', 'C');
    tarjan.addEdge('C', 'A');
    tarjan.addEdge('B', 'D');
    tarjan.addEdge('D', 'E');
    tarjan.addEdge('E', 'F');
    tarjan.addEdge('F', 'E');
    tarjan.addEdge('G', 'E');
    tarjan.addEdge('H', 'F');
    tarjan.addEdge('G', 'H');
    tarjan.addEdge('J', 'H');
    tarjan.addEdge('J', 'G');
    tarjan.addEdge('I', 'J');
    tarjan.addEdge('H', 'I');

    tarjan.findSCCs();

    return 0;
}
