## 1. 介紹

Hash table 是一種輸入 key 得到 value 的資料結構，最簡單的 Hash table 就是 array，key 就是 index，所以我們可以透過 key 來取得對應位置的資料。而在其他語言中常見的字典 (Dictionary) 也是一種 Hash table，在 C++ 中也有 unorder_map 可以使用。

所以想要知道一個陣列中的某些元素出現過幾次，那就可以用最簡單的 Hash table，也就是 array 來實作。例如有一陣列 A = {1, 2, 6, 4, 8, 9, 7, 6, 3, 999}
```C
int map[1000];
for (int i = 0; i < 10; i++) map[A[i]]++;
```
這樣就可以簡單地知道 A 中每個元素出現的次數。但缺點也很明顯，就是要事先開一個很大的陣列才能夠保持 O(1) 的存取效能，簡單來說就是用記憶體換時間，為了解決這個問題，所以發明了一個 Hash function 來讓記憶體使用量減少，並盡量保持 O(1) 的存取效能。

## 2. Hash function
資料進到 table 時我們並不能事先知道他的範圍，所以要給個函數，把進來的 key 做對應的轉換。所以容器大小 L 會是固定的，但是 key 有可能會跑出陣列的範圍，所以首要就是將 key 的值轉換到 [0,L) 之間。再來就是經過轉換後的 key 有可能會是同一個值，例如 H(x) = H(y)，這時就稱為 Collision。所以在設計 Hash function 時要考量以下幾點：
1. Key 的值可能超過容器大小 (Overflow)
2. 轉換後不同的 key 可能對應到同個 key (H(x) = H(y))，也就是 (Collision)
3. 計算宜簡單，不然效能會降低
4. 盡量平均分配在容器中

#### 1. 線性探測 Linear probing
