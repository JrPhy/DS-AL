在搜尋的算法中一般來說就兩種，一種是任何情況都可使用的線性搜尋法(linear search)，從頭找到尾即可也沒什麼使用限制，複雜度是 O(n)。\
另一種就是這邊要介紹的二元搜尋法(binary search)，這僅在被搜尋的結構是**排序過**的才可使用，時間複雜度是 O(logn)。\
因為是以排序過的資料，所以在每次搜尋時都能將資料從中間分成兩部分，一部分是較小的一部分是較大的，且要找的資料為 key。\
若第一次尋找後 key < a[mid]，則將陣列範圍限定在頭到中間，後半段的部分就捨去，反之留下中間到尾，並重複此步驟直到找到或證明該 key 不存在於這資料中。\
舉例來說一陣列中有九個元素分別為 a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}，我們想要找的 key = 7。\
利用 a[head] = 1, a[tail] = 9, a[mid] = 5。第一次尋找後 key > a[mid]，則將下一次範圍限定在 {6, 7, 8, 9}，此時 a[head] = 6, a[tail] = 9, a[mid] = 7。所以只找了兩次就找到了。\
下列使用整數型別陣列示範，因為是用 array，所以若有找到，則直接將 key 的位置傳出來，之後就可以直接取用該位置的值。若沒找到則是 -1。
```C
int bsearch(const int array[], int head, int tail, int key)
{
    int mid = 0;
    while(head <= tail)	
    {
        mid = head + (tail - head)/2;  //之所以不直接寫 (tail + head)/2 是因為可能會溢位造成 mid 變為負數。
        if (key < array[mid]) tail = mid - 1;
        else if (key > array[mid]) head = mid + 1;
        else return mid;
    }
    return -1;
}
```
在 C 語言的標準函式庫中有內建此函數，使用方式請參考 [模擬泛型函數](https://github.com/JrPhy/C_tutorial/blob/main/CH5-%E6%8C%87%E6%A8%99%E8%88%87%E5%AD%97%E4%B8%B2.md#5-%E6%A8%A1%E6%93%AC%E6%B3%9B%E5%9E%8B%E5%87%BD%E6%95%B8)。實作請參考 [bsearch實作](http://www.jbox.dk/sanos/source/lib/bsearch.c.html)。在標準函式庫中的 bserach 使用泛型指標來讓函數使用情況更普遍，並利用指標相減找出位置。\
對於多數情況來說，binary search 所花的時間是比 linear search 還要少的，但當被搜尋的資料中有重複的值就會比較麻煩。
