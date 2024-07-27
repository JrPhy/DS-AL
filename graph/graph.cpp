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
  
    void kruskalsMST() { 
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
    
    void primMST() {  
        vector<int> parent(V, -1); // To store the parent of each vertex in the MST  
        vector<int> key(V, INT_MAX); // To store the minimum key value for each vertex  
        vector<bool> inMST(V, false); // To track whether a vertex is included in MST  
      
        // Create a priority queue (min-heap) to select edges with minimum weight  
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  
      
        // Start with the first vertex (vertex 0) as the initial vertex  
        key[0] = 0;  
        pq.push({0, 0});  
      
        while (!pq.empty()) {  
            int u = pq.top().second;  
            pq.pop();  
      
            // Mark the current vertex as included in MST  
            inMST[u] = true;  
      
            // Explore all adjacent vertices of u  
            for (auto edge : edgelist) { 
                if(edge[1]!=u) continue;
                int w = edge[0]; 
                int y = edge[2]; 
      
                // If v is not in MST, there is an edge from u to v, and the weight is smaller than the current key of v  
                if (!inMST[y] && w < key[y]) {  
                    // Update key value and parent of v  
                    key[y] = w;  
                    parent[y] = u;  
      
                    // Add v to the priority queue  
                    pq.push({key[y], y});  
                }  
            }  
        }  
      
        // Print the MST edges  
        cout << "Edges of Minimum Spanning Tree:" << endl;  
        for (int i = 1; i < V; ++i) {  
            cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << endl;  
        }  
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
    void shortestPath(int src) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
        // Create a vector for distances and initialize all
        // distances as infinite (INF)
        vector<int> dist(V, INT_MAX);
    
        // Insert source itself in priority queue and initialize
        // its distance as 0.
        pq.push({0, src});
        dist[src] = 0;
    
        /* Looping till priority queue becomes empty (or all
        distances are not finalized) */
        while (!pq.empty()) {
            // The first vertex in pair is the minimum distance
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted distance (distance must be first item
            // in pair)
            int u = pq.top().second;
            pq.pop();
    
            // 'i' is used to get all adjacent vertices of a
            // vertex
            for (auto edge : edgelist) { 
                if(edge[1]!=u) continue;
                int w = edge[0]; 
                int y = edge[2];
                // If there is shorted path to v through u.
                if (dist[y] > dist[u] + w) {
                    // Updating distance of v
                    dist[y] = dist[u] + w;
                    pq.push({dist[y], y});
                }
            }
        }
    
        // Print shortest distances stored in dist[]
        printf("Vertex Distance from Source\n");
        for (int i = 0; i < V; ++i)
            printf("%d \t\t %d\n", i, dist[i]);
    }
}; 

int main() {
    Graph g(5);
    vector<int> a = {0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    vector<int> b = {1, 2, 4, 0, 2, 3, 0, 1, 3, 4, 1, 2, 4, 0, 2, 3};
    vector<int> w = {2, 1, 3, 2, 2, 3, 1, 2, 1, 4, 3, 1, 2, 3, 4, 2};
    for(int i = 0; i < a.size(); i++) g.addEdge(a[i], b[i], w[i]);
    g.primMST();
    printf("\n");
    g.kruskalsMST();
    printf("\n");
    g.shortestPath(0);
    return 0;
}
