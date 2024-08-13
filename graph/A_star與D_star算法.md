Dijkstra 雖然能很快地找出最短路徑，但限制其實也不少，例如權重不能為負數，另一個就是途中不能有無法經過的點，如果有的話就不一定找的到最短路徑。此時就可使用 A* 算法。[此篇文章](https://paul.pub/a-star-algorithm/)有動圖演示，並且從 BFS 到 A* 算法，是非常好的參考資料。

## 1. A* 算法
此算法從 Dijkstra 做改進，加了一個啟發函數 H，也就是變成```w* = w + H```，其中 w 是原來的權重，w* 為加入啟發函數後的權重。所以當 H = 0 時就退回 Dijkstra 算法。而當 H 取太大時就是每個方向都要嘗試，就會變成 BFS。所以再取的時候最好是越接近實際解就會跑得很快。在圖的問題中有三種啟發函數的取法
1. H = |x<sub>2</sub> - x<sub>1</sub>| + |y<sub>2</sub> - y<sub>1</sub>|，稱為 Manhattan Distance，即為座標點的差值
2. H = sqrt(|x<sub>2</sub> - x<sub>1</sub>|<sup>2</sup> + |y<sub>2</sub> - y<sub>1</sub>|<sup>2</sup>)，為大家所熟知的 Euclidean Distance
3. 動態調整法

三種取法的效能可參考[這篇文章](http://admin.guyuehome.com/44306)。程式碼可[參考這篇](https://juejin.cn/post/7105034469958942756)。在此中間有不可經過的點，也就是障礙物，所以利用```NodeIsLegal```去檢查是否可經過。
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
