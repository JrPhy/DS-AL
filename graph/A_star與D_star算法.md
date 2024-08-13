Dijkstra 雖然能很快地找出最短路徑，但限制其實也不少，例如權重不能為負數，另一個就是途中不能有無法經過的點，如果有的話就不一定找的到最短路徑。此時就可使用 A* 算法。[此篇文章](https://paul.pub/a-star-algorithm/)有動圖演示，並且從 BFS 到 A* 算法，是非常好的參考資料。

## 1. A* 算法
此算法從 Dijkstra 做改進，加了一個啟發函數 H，也就是變成```w* = w + H```，其中 w 是原來的權重，w* 為加入啟發函數後的權重。所以當 H = 0 時就退回 Dijkstra 算法。而當 H 取太大時就是每個方向都要嘗試，就會變成 BFS。所以再取的時候最好是越接近實際解就會跑得很快。在圖的問題中有三種啟發函數的取法
1. H = |x<sub>2</sub> - x<sub>1</sub>| + |y<sub>2</sub> - y<sub>1</sub>|，稱為 Manhattan Distance，即為座標點的差值
2. H = sqrt(|x<sub>2</sub> - x<sub>1</sub>|<sup>2</sup> + |y<sub>2</sub> - y<sub>1</sub>|<sup>2</sup>)，為大家所熟知的 Euclidean Distance
3. 動態調整法

三種取法的效能可參考[這篇文章](http://admin.guyuehome.com/44306)。
