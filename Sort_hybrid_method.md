由前兩篇可知每個排序算法各有優缺點，O(n<sup>2</sup>) 的算法慢，但是 code size 小且都是 in-place 的算法，適用於資料量不大。而 O(nlog<sub>2</sub>n) 的算法至少需要額外的記憶體，若是使用 iterative 的寫法 code size 就大非常多，但資料量大時速度就快非常多，故就有人各取其優點另外寫成一個排序算法。

## 1. Introspective Sort(Introsort)
此算法由 David Musser 在 1997 年提出，其混用了 Insertion Sort、Heap Sort 和 Quick Sort，且在 C++ STL 中使用的排序法即為此算法。由實驗可知，在 n < 20 的情況下 Insertion Sort 會比 Quick Sort 還要快，所以當陣列長度小於 16 時會使用 Insertion Sort。\
然而 Quick Sort 在最差的情況是 O(n<sup>2</sup>)，當 pivot 沒選好時就有可能遇到此情況，也就是當一直遞迴呼叫 Quick Sort 超過某次數後可能就是遇到了此情況，在 STL 中是設定 2log<sub>2</sub>n，此時會改用 Heap Sort，因為 Heap Sort 最差的情況也是 O(nlog<sub>2</sub>n)。\
然而 Merge Sort 最差的情況也是 O(nlog<sub>2</sub>n)，但是 Heap Sort 不需要另外的記憶體空間而 Merge Sort 需要。

https://www.techiedelight.com/introsort-algorithm/

## 2. Timsort
此算法由Tim Peters 在 2002 年提出，其混用了 Insertion Sort 和 Merge Sort，且在 Python、Java 中使用
