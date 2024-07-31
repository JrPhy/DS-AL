在圖中很常會有環，也就是從某個點出發去走訪會回到原點，所以會希望檢測圖中是否有環，更進一步希望那些點形成環找出來，可以使用連線(union find)的方式來尋找。下方我們先將某一邊的兩頂點做連線，若最後 f1 的母節點與 f2 相同，那就表示有環存在。也可以用走訪的方式或是用拓樸排序的方式來找出。
```cpp
#include <vector>
#include <iostream>
using namespace std;
class Unite {
    vector<int> parent;
    public:
    Unite(int V) 
    {parent.resize(V+1, -1);}
    
    int find(int x) 
    {return parent[x] == -1 ? x : find(parent[x]);}
    
    bool isCycle(vector<vector<int>>& edges) {
        for (vector<int> edge : edges) {
            int f1 = find(edge[0]);
            int f2 = find(edge[1]);
            if (f1 != f2) parent[f1] = f2;
            else {
                cout << "a cycle in graph";
                return true;
            }
        }
        return false;
    }
};

bool isCycle(vector<vector<int>>& adj, 
            int s, int V, vector<int>& visited){
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (visited[v])  {
            cout << "a cycle in graph";
            return true;
        }
        visited[v] = 1; // Mark as visited
        // Visit adjacent nodes
        for (auto it : adj[v]) {
            if (visited[it] == 0) {
                q.push(it);
            }
        }
    }
    return false;
}

int main() {
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 1}};
    int n = 3;
    Unite u(n);
    u.isCycle(edges);
    // for bfs
    vector<vector<int>> adj(n+1);
    vector<int> visit(n+1, -1);
    for(auto e:edges) {
        adj[e[0]].push_back(e[1]);
    }
    isCycle(adj, edges[0][0], n, visit);
    return 0;
}
```
