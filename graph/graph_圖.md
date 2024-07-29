在電腦科學中，圖代表由頂點(Vertex)與邊(Edges)所連成的形狀，其中的頂點即為樹與串列中的 node，邊也有可能有權重，樹和串列就是圖的一種特例，就圖的種類還可以分成以下幾種去做組合
![image](https://github.com/JrPhy/DS-AL/blob/master/pic/graph.jpg)
| 方向 | 環 | 權重 | 
| --- | --- | --- | 
| 有向 | 有環 | 有 |
| 無向 | 無環 | 無 |

## 1. 資料表示
一般來說會給兩個相同大小的陣列，或是給 [n][2] 的陣列，來表示各個點之間的關係，以上左圖為例
```c++
vector<int> a = [0, 0, 2, 2, 3, 4]
vector<int> b = [1, 3, 3, 4, 5, 1]
vector<vector<int>> c = [[0, 1], [0, 3], [2, 3], [2, 4], [3, 5], [4, 1]]
```
意思就是說若為有向圖，則 a 中相同 index 的點可以走向 b，也就是 0->1, 0->3, ..., 4->1。若是無向則可以來回。若有權重可能就會在多個 w。此時我們就可以建一個鄰接表 (Adjacency list) 或是鄰接矩陣 (Adjacency matrix) 來表示每個頂點與其他頂點的連接狀況。
```c++
unordered_map<int, vector<int>> adj;
for(int i = 0; i < a.size(); i++) {
    adj[a[i]].push_back(b[i]);
    // adj[b[i]].push_back(a[i]); // 無向圖需多這個
}
//adj[0]->1->3
//adj[2]->3->4
//adj[3]->5
//adj[4]->1
/* 0 1 0 1 0 0
   1 0 0 0 1 0
   0 0 0 1 1 0
   1 0 1 0 0 1
   0 1 1 0 0 0
   0 0 0 1 0 0 */
```
可以看到矩陣需要多花費更多記憶體，但是矩陣的表示在很多情況下會比較方便使用。
## 2. 圖的走訪
與樹一樣，有廣度優先(BFS)與深度優先(DFS)，在此我們會多一個 visit 來記錄該點是否已走訪過。
#### 1. BFS
與樹的 Level order 走訪非常類似，但因為圖的連接情況較複雜，可以從任意節點進入，不像樹一定從根結點。
```c++
#include <bits/stdc++.h>
// also include other .h
using namespace std;
class Graph { 
    vector<vector<int>> edgelist;
    vector<int> visited; 
    int V; 
  
public: 
    Graph(int V) {
        this->V = V;
        visited.resize(V);
    } 
    // Function to add edge in a graph 
    void addEdge(int x, int y, int w) 
    {edgelist.push_back({ w, x, y });} 
    
    void bfs(int start) {
        queue<int> q;
        vector<int> visited(edgelist.size(), 0);
        visited[start] = 1;
        q.push(start); // 也可以從其他節點進入
        int node;
        while (!q.empty()) {
            node = q.front();
            q.pop();
            cout << node << " ";
                
            for (int neighbor : edgelist[node]) {
            // 若 n = 0，neighbor = 1, 3
                if (!visited[neighbor]) {
            // 一開始都為 0，之後有經過就會設成 1
                    visited[neighbor] = true;
                    q.push(neighbor);
            // 再把其他 node 放進 queue
                }
            }
        }
    }
};

int main() {
    Graph g(5);
    vector<int> a = {0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    vector<int> b = {1, 2, 4, 0, 2, 3, 0, 1, 3, 4, 1, 2, 4, 0, 2, 3};
    vector<int> w = {2, 1, 3, 2, 2, 3, 1, 2, 1, 4, 3, 1, 2, 3, 4, 2};
    for(int i = 0; i < a.size(); i++) {
        g.addEdge(a[i], b[i], w[i]);
    }
    g.bfs(a[0]); // 0 2 1 3 4
    return 0;
}
```
與樹的 BFS 差異在下個節點的尋找，因為樹的節點是上下關係，而圖不是。

#### 2. DFS
dfs 通常會另外寫一個函數遞迴呼叫，當然也有迭代呼叫的方式，只是程式碼會變得比較複雜。
```c++
void dfs(int start) {
    cout << start << " ";
    visited[start] = 1;
    for (int neighbor : edgelist[start]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}
// 0 2 3 1 4
```
可以看到 bfs/dfs 中有個引數 start，就是告訴函數要從哪個點開始，進入之後再去走訪跟他相鄰的節點，結束條件就是迴圈跑完，表示每個**有連結**的節點都走過了。當然有些節點的 visit 還是 0，就代表該點與起始節點沒有相連。

## 3. 拓樸排序法
若一張圖為**有向無環圖 DAG**，也就是只能朝著限定方向走，且不會形成環的圖。而這種圖一定有個是只出不進的點，也有只進不出的點，可當作起點與終點。而對應到現實例子，就是一定要先做某件事才能做接下來的事。例如修課一定要先修完某些課才能繼續往下修，此時就可使用拓樸排序法來排出先後順序。會將圖排呈線性如下圖表示
![image](https://github.com/JrPhy/DS-AL/blob/master/pic/topo_sort.jpg)\
此排序算法可以用 bfs 與 dfs 的方法
#### 1. [topo sort bfs(Kahn)](https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)
BFS 的作法是先計算每個節點有多少進入的邊，若是某個節點沒有進入，則表示**可能**為起始點，也就是最優先要做的事。當然也有可能是不進也不出，也就是沒與其他點相連，可以檢查 in 與 out 的數量，如果都是 0 則表示沒有相連。
```cpp
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
int main() {
    vector<int> a = {0, 0, 1, 1, 2, 3, 3, 4, 6};
    vector<int> b = {1, 2, 2, 3, 4, 4, 5, 6, 5};
    int V = 9;
    vector<vector<int>> adj(V);
    vector<int> indegree(V), outdegree(V);

    for (int i = 0; i < a.size(); i++) {
        adj[a[i]].push_back(b[i]);
        indegree[b[i]]++;
        // adj list
    }
        
    for (int i = 0; i < V; i++) {
        outdegree[i] = adj[i].size();
        // 從 adj[i] 出去
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (!indegree[i] && outdegree[i]) q.push(i);
        // 先把只出不進的點放入
    }
    vector<int> result;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        result.push_back(node);
        cout << node << ", ";
        // 減少進入的次數做排序。
        for (int it : adj[node]) {
            // indegree[it] 為零，表示進入的次數沒其他節點多
            if (--indegree[it] == 0)
                q.push(it);
        }
    }
    return 0;
}
// 0, 1, 2, 3, 4, 6, 5,
```
可以看到在此例子中，0 為只出不進的點，而 5 為只進不出的點，所以 0 被排在最前面，5 被排在最後面。7, 8 兩點因為與其他點沒有連接所以被排除在外。如果把 0, 1, 2 三點接起來形成環，則形成環的點無法排序，因為那些點都是有進有出，而其他仍可排序，可嘗試以下例子。
```
vector<int> a = {0, 1, 2, 3, 3, 4, 6};
vector<int> b = {1, 2, 0, 4, 5, 6, 5};
int V = 9;
// 3, 4, 6, 5,
```
而此排序的順序也不唯一，因為進入的點有可能個數一樣，此時若換成 dfs 則會有不同的結果。
#### 2. [topo sort dfs](https://www.geeksforgeeks.org/all-topological-sorts-of-a-directed-acyclic-graph/)
同樣的，一樣不顯示與圖不相連的點
```cpp
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

// Function to perform DFS and topological sorting
void topologicalSortUtil(int v, vector<vector<int> >& adj,
                         vector<bool>& visited,
                         stack<int>& st) {
    visited[v] = true;
    for (int i : adj[v]) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, st);
    }
    st.push(v);
}


int main() {
    vector<int> a = {0, 0, 1, 1, 2, 3, 3, 4, 6};
    vector<int> b = {1, 2, 2, 3, 4, 4, 5, 6, 5};
    int V = 9;
    vector<vector<int>> adj(V);
    vector<int> indegree(V), outdegree(V);
    for (int i = 0; i < a.size(); i++) {
        adj[a[i]].push_back(b[i]);
        indegree[b[i]]++;
        // adj list
    }
    for (int i = 0; i < V; i++) {
        outdegree[i] = adj[i].size();
        // 從 adj[i] 出去
    }
    stack<int> st; // st to store the result
    vector<bool> visited(V, false);

    // Call the recursive helper function to store
    // Topological Sort starting from all vertices one by
    // one
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, st);
    }

    // Print contents of st
    while (!st.empty()) {
        if (indegree[st.top()] || outdegree[st.top()])
            cout << st.top() << " ";
        st.pop();
    }
    return 0;
}
// 0 1 3 2 4 6 5
```
可以看到 2, 3 順序交換了，因為走訪的方式不同。
