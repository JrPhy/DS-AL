// Kruskal's algorithm in C++
#include <bits/stdc++.h> 
using namespace std; 
  
// DSU data structure 
// path compression + rank by union 
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
    
    void dfs(int start) {
        cout << start << " ";
        visited[start] = 1;
        for (int neighbor : edgelist[start]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
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
    g.bfs(a[0]);
    printf("\n");
    g.dfs(a[0]);
    printf("\n");
    g.kruskals_mst();
    return 0;
}
