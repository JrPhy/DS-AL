由前兩篇可知每個排序算法各有優缺點，O(n<sup>2</sup>) 的算法慢，但是 code size 小且都是 in-place 的算法，適用於資料量不大。而 O(nlog<sub>2</sub>n) 的算法至少需要額外的記憶體，若是使用 iterative 的寫法 code size 就大非常多，但資料量大時速度就快非常多，故就有人各取其優點另外寫成一個排序算法。

## 1. Introspective Sort(Introsort)
此算法由 David Musser 在 1997 年提出，其混用了 Insertion Sort、Heap Sort 和 Quick Sort，且在 C++ STL 中使用的排序法即為此算法。

https://www.techiedelight.com/introsort-algorithm/

## 2. Timsort
此算法由Tim Peters 在 2002 年提出，其混用了 Insertion Sort 和 Merge Sort，且在 Python、Java 中使用
