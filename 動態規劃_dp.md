動態規劃(Dynamic programming)是一種將原本的問題拆解成許多小問題，並基於原本的小問題繼續往下解。例如費氏數列、階層等問題，其技巧有 Top-Down, Bottom-up, memorize, backtracking 等，不同的問題會使用不同的技巧，通常用來降低計算的時間複雜度。

## 1. 費氏數列
費氏數列是一個任何程式設計都會教到的部分，是一個遞回程式的好例子，且數學表達氏通常也在中學學到\
F<sub>n-2</sub> = F<sub>n-1</sub> + F<sub>n-0</sub>, F<sub>0</sub> = F<sub>1</sub> = 1
```cpp
#include <stdio.h>
int f(int n) {
    if(n < 2) return 1;
    return f(n-1)+f(n-2);
}
int main()
{
    printf("%d", f(5));
    return 0;
}
```
![image](https://www.baeldung.com/wp-content/uploads/sites/4/2020/06/Fibonacci-top-down.svg)
從圖片可以知道，要計算 f(5)，要先計算 f(4) 與 f(3)，直到算到 f(1) 為止，所以必須要將這些部分都存下來，空間複雜度為指數次方。在電腦中會把函數的回傳值放在 stack 中，如果計算的數字太大，則會造成 stack-overflow，而且計算時間也會非常久，時間複雜度為指數次方。所以我們就將計算過的部份另外存於其他變數中，並用來計算下一個需要的 f(n)
```cpp
#include <stdio.h>
int f(int n) {
    if(n < 2) return 1;
    int f0 = 1, f1 = 1, f2;
    for(int i = 2; i < n; i++) {
        f2 = f1 + f0;
        f0 = f1;
        f1 = f2;
    }
    return f2;
}
int main()
{
    printf("%d", fibunacci(5));
    return 0;
}
```
在此我們將計算出的結果放在 f1 裡面，然後再一直更新，如此一來只需要多花三個 int，空間複雜度為 O(1)，而且也只要用一個迴圈即可算出，時間複雜度為 O(n)，在空間與時間都有很大的優化。而這種方法稱為 Bottom-up 或是 memorize 的方法。\
不過一般動態規劃的問題難就難在要找出遞迴關係式，例如 [leetcode 338. Counting Bits](https://leetcode.com/problems/counting-bits/description/)，最直接的解法就是每個都找出來然後在加起來
|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| binary | 0 | 01 | 10 | 11 | 100 | 101 | 110 | 111 | 1000 |
可以看到當數字為 2<sup>n</sup> 時就會多一個 bit，而且原本的數字會一直重複出現，例如當 n = 7 時就是在比 3 多一個 bit，5 時就是在比 2 多一個 bit，而 6 的 bit-count 與 3 相同，4 的 bit-count 與 2 相同，所以可以整理出規律為
當 n 為奇數時：n = n/2 + 1，在電腦中 7/2 會只取整數位，所以是 3
當 n 為偶數時：n = n/2
所以規則為
```cpp
ans[i] = ans[i >> 1] + (i & 1);
```
其中 i>>1 在電腦中為 /2 的意思，i & 1 為判斷 i mod 2 的意思。
