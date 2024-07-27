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

