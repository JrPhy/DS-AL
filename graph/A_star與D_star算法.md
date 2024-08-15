在真實情況中，想從地圖上的 A 走到 B，最短距離就是直線距離，但中間往往會有障礙物或有無法行走的部分，最簡單的想法就是用 BFS 去探索地圖，並且給予權重，探索到的時候就利用 Dijkstra 算法找出最短距離，即為 A* 算法。[此篇文章](https://paul.pub/a-star-algorithm/)有動圖演示，並且從 BFS 到 A* 算法，是非常好的參考資料。

## 1. A* 算法
此算法從 Dijkstra 做改進，加了一個啟發函數 H，也就是變成```w* = w + H```，其中 w 是原來的權重，w* 為加入啟發函數後的權重。所以當 H = 0 時就退回 Dijkstra 算法。而當 H 取太大時就是每個方向都要嘗試，就會變成 BFS。所以再取的時候最好是越接近實際解就會跑得很快。在圖的問題中有三種啟發函數的取法
1. H<sub>MD</sub> = |x<sub>2</sub> - x<sub>1</sub>| + |y<sub>2</sub> - y<sub>1</sub>|，稱為 Manhattan Distance，即為座標點的差值
2. H<sub>ED</sub> = sqrt(|x<sub>2</sub> - x<sub>1</sub>|<sup>2</sup> + |y<sub>2</sub> - y<sub>1</sub>|<sup>2</sup>)，為大家所熟知的 Euclidean Distance
3. 動態調整法

以下圖為例，S 為起點，G 為終點。所以先算出 S 周圍格點到 G 的距離 w(i)，稱為 OPENLIST，這邊採用 H<sub>MD</sub> 計算，再來算出 S 到鄰近格點的距離 H(i)，這邊採用 H<sub>ED</sub> 計算，最後就可以算出 w*(i)，如此一來就可以每個都算出來。接著就套用 Dijkstra 算法走訪，走訪後再做計算，直到計算到終點為止。\
而不同距離的取法效能可參考[這篇文章](http://admin.guyuehome.com/44306)。程式碼可[參考這篇](https://www.cnblogs.com/xxmmqg/p/12843900.html)。在此中間有不可經過的點，也就是障礙物，所以利用```NodeIsLegal```去檢查是否可經過。
```cpp
bool NodeIsLegal(int x, int y, int xx, int yy)
{
    if(x < 0 || x >= N || y < 0 || y >= N) return false; // 判断边界 
    if(qp[x][y]) return false; // 判断障碍物 
    // 两节点成对角型且它们的公共相邻节点存在障碍物 
    if(x != xx && y != yy && (qp[x][yy]|| qp[xx][y])) return false;
    return true;
}

void A_start(int x0, int y0, int x1, int y1)
{
    // 初始化起点 
    Node node(x0, y0);
    node.G = 0; 
    node.H = Manhuattan(x0, y0, x1, y1); 
    node.F = node.G + node.H;
    valF[x0][y0] = node.F; 
    // 起点加入open表 
    q.push(node); 
    
    while(!q.empty())
    {
        Node node_top = q.top(); q.pop(); 
        // 访问该点，加入closed表 
        visit[node_top.x][node_top.y] = true;
        if(node_top.x == x1 && node_top.y == y1) break;
        // 到达终点 
        // 遍历node_top周围的8个位置 
        for(int i=0; i<8; i++)
        {
            Node node_next(node_top.x + dir[i][0], node_top.y + dir[i][1]); // 
            // 创建一个node_top周围的节点，该节点坐标合法 且 未加入close表 
            if(NodeIsLegal(node_next.x, node_next.y, node_top.x, node_top.y)
                && !visit[node_next.x][node_next.y]) 
            {
                // 计算从起点并经过node_top节点到达该节点所花费的代价 
                node_next.G = node_top.G + int(sqrt(pow(dir[i][0],2)+pow(dir[i][1],2))*10); 
                // 计算该节点到终点的曼哈顿距离
                node_next.H = Manhuattan(node_next.x, node_next.y, x1, y1);  
                // 从起点经过node_top和该节点到达终点的估计代价
                node_next.F = node_next.G + node_next.H; 
                // node_next.F < valF[node_next.x][node_next.y] 说明找到了更优的路径，则进行更新
                // valF[node_next.x][node_next.y] == 0 说明该节点还未加入open表中，则加入 
                if(node_next.F < valF[node_next.x][node_next.y] || valF[node_next.x][node_next.y] == 0)
                {
                    // 保存该节点的父节点 
                    path[node_next.x][node_next.y][0] = node_top.x;
                    path[node_next.x][node_next.y][1] = node_top.y;
                    valF[node_next.x][node_next.y] = node_next.F; // 修改该节点对应的valF值 
                    q.push(node_next); // 加入open表
                }
            }
        }
    }
}
```

## 2. D* 算法
以上所講的算法都是要先將圖建立好才可以找出最短路徑，在實際應用上就是要一直去走訪空間的每個角落，如此一來就會花很多時間在這上面。所以再從 A* 算法作改良，得到一個 Dynamic A* 算法，簡稱為 D* 算法。此算法會從終點利用 A* 算法算道起點的最小路徑，當物體從起點開始移動時若途中有新的障礙，就會更新目前位置的權重然後再算出新的路徑。在[論文中給出 psuedo-code](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=4d95e5c7c3b7d8a2a8a273e69a5b4fb98557b912)，此算法主要有三個函數
1. PROCESS_STATE()
2. MODIFY_COST()
3. MOVE_ROBOT()

當機器人在行走時會去一直計算 PROCESS_STATE()，有新的障礙物時就會去計算 MODIFY_COST()，如果新的 w* 比較小就更新。

https://qiao.github.io/PathFinding.js/visual/
