在電腦科學中，圖代表由頂點(Vertex)與邊(Edges)所連成的形狀，其中的頂點即為樹與串列中的 node，邊也有可能有權重，樹和串列就是圖的一種特例，就圖的種類還可以分成以下幾種去做組合
![image](https://github.com/JrPhy/DS-AL/blob/master/pic/graph.jpg)
| 方向 | 環 | 權重 | 
| --- | --- | --- | 
| 有向 | 有環 | 有 |
| 無向 | 無環 | 有 |

## 1. 資料表示
一般來說會給兩個相同大小的陣列，或是給 [n][2] 的陣列，來表示各個點之間的關係，以上左圖為例
```c++
vector<int> a = [0, 0, 2, 2, 3, 4]
vector<int> b = [1, 3, 3, 4, 5, 1]
vector<vector<int>> c = [[0, 1], [0, 3], [2, 3], [2, 4], [3, 5], [4, 1]]
```
意思就是說若為有向圖，則 a 中相同 index 的點可以走向 b，也就是 0->1, 0->3, ..., 4->1。若是無向則可以來回。若有權重可能就會在多個 w。此時我們就可以建一個鄰接表 (Adjacency list) 來表示每個頂點與其他頂點的連接狀況。
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
```
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
    vector<int> w = {2, 1, 3, 2, 2, 3, 1, 2, 1, 4, 3, 1, 2, 3, 4, 1};
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

## 3. 最小生成樹 Minimum-Spanning Tree
若是每個邊的**權重**不一，例如每個村莊到其他村莊的距離會有不同，就是權重不同的一種，走訪全部村莊的路徑也不只一種。如果希望每個村莊只經過一次，並走訪每個村莊，而且不限定走訪方向，那麼就會生成一棵樹，若再要求走的距離是最短的，那麼此時生成的樹就稱為最小生成樹 MST，如下圖所示。
![image](https://github.com/JrPhy/DS-AL/blob/master/pic/MST.jpg)\
當然根據不同的權重不同，也有可能產生不同的最小生成樹，所以並不保證此種樹只有一顆。而最小生成樹一般有兩種算法，分別是 Kruskal 與 Prim 算法。所以最小生成樹的條件為**有權重、互相連接的無向圖**。\
可參考[此網站](https://visualgo.net/en/mst)看看各種 MST 是怎麼生成的
#### 1. Kruskal 算法 O(ElogE + ElogV)
[程式碼參考此篇](https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/)。從直覺上來想，我們只要將每個邊權重最小的值找出來在連起來就好了。所以算法一開始我們先對權重做排列，再來判斷兩個頂點是否直接或間接相連，即是否**連通(connected)**，如果有的話就將他連起來即可得到所求。
```cpp
void kruskals_mst() { 
    // Sort all edges 
    sort(edgelist.begin(), edgelist.end()); 
    // Initialize the DSU 
    DSU s(V); 
    int ans = 0; 
    cout << "Following are the edges in the "
            "constructed MST" << endl; 
    for (auto edge : edgelist) { 
        int w = edge[0]; 
        int x = edge[1]; 
        int y = edge[2]; 
        // Take this edge in MST if it does 
        // not forms a cycle 
        if (s.find(x) != s.find(y)) { 
            s.unite(x, y); 
            ans += w; 
            cout << x << " -- " << y << " == " << w << endl; 
        } 
    } 
    cout << "Minimum Cost Spanning Tree: " << ans; 
} 
```
而要判斷兩個點是否連通，只需一從其中一個點出發，看最後是否能抵達另一個點即可。而我們要找的是樹狀結構，也就是不會形成環的結構，所以將任意點丟進去尋找，如果最後等於自己，那就表示該節點為根節點，最後再將找到的點連起來即為最小生成樹。
```cpp
class DSU { 
    int *parent, *rank; 
  
public: 
    DSU(int n)  { 
        parent = new int[n]; 
        rank = new int[n]; 
        for (int i = 0; i < n; i++) { 
            parent[i] = -1; 
            rank[i] = 1; 
        } 
    } 
  
    // Find function 
    int find(int i) {return (parent[i] == -1)
                    ? i : parent[i] = find(parent[i]);}
  
    // Union function 
    void unite(int x, int y)  { 
        int s1 = find(x); 
        int s2 = find(y); 
        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) { 
                parent[s1] = s2; 
            } 
            else if (rank[s1] > rank[s2]) { 
                parent[s2] = s1; 
            } 
            else { 
                parent[s2] = s1; 
                rank[s1] += 1; 
            } 
        } 
    } 
}; 
```
其中的 rank 代表要經過幾個節點才能從 a 到 b。當然最一開始每個點都是各自獨立的，所以當我們丟任意兩點進去後，我們就將其中一個點當作另一點的父節點，當然順序反過來也沒差。最後在合併和，rank 越小表示越靠近根節點，所以應該要讓離根節點比較遠的接在離根比較近的後面。以這個例子來說，最後就是走了距離為 5 單位就可以走訪全部節點，[範例可參考這篇](https://github.com/JrPhy/DS-AL/blob/master/List_and_Tree/MST.cpp)。
```
Following are the edges in the constructed MST
0 -- 2 == 1
2 -- 3 == 1
4 -- 3 == 1
0 -- 1 == 2
Minimum Cost Spanning Tree: 5
```
可看到裡面計算量最大的就是做排序O(E log E)與連線O(E log V)，所以複雜度為 O(ElogE + ElogV)
#### 2. Prim 算法
```cpp
void primMST()
{
    // Array to store constructed MST
    int parent[V] = {0}, graph[V][V] = {0}, key[V] = {0};

    // To represent set of vertices included in MST
    bool mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first
    // vertex.
    key[0] = 0;
  
    // First node is always root of MST
    parent[0] = -1;
    for (auto edge : edgelist) 
        graph[edge[1]][edge[2]] = edge[0];

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int min = INT_MAX, min_index;

        for (int v = 0; v < V; v++)
            if (mstSet[v] == false && key[v] < min)
                min = key[v], min_index = v;
    
        int u = min_index;

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)

            // graph[u][v] is non zero only for adjacent
            // vertices of m mstSet[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Print the constructed MST
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}
```
