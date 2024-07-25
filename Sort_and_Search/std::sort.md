C++ STL 中提供了 sort，主要是用 introspective sort。也得益於 C++ 的語法，讓 sort 用起來更加方便。

## 1. 數字升序與降序
在 C 中的 qsort 要寫個指標函數來告訴 qsort 你想要升序還降序，例如
```c
int compare(const void * a, const void * b)
{return ( *(int*)a - *(int*)b );}

qsort(base, nitems, size, compare(const void * a, const void * b));
```
上述就是一個對於 int 陣列且由小到大的排列，若返回值為 ```( *(int*)b - *(int*)a );``` 則反過來。在 C++ 中則是使用 sort，需要 ```#include <algorithm>```，預設由小到大，若要由大到小可以在第三個參數傳入 ```std::greater<int>()```。
```c++
#include <vector>
#include <algorithm>  // sort
#include <functional> // std::greater<int>()
int main()
{
    std::vector<int> a = {5, 8, 6, 44, 8, 0 ,2, -1};
    std::sort(a.begin(), a.end());
    for(int i = 0; i < 8; i++) cout << a[i] << ", ";
    // -1, 0, 2, 5, 6, 8, 8, 44,
    cout << endl;
    std::sort(a.begin(), a.end(), std::greater<int>());
    for(int i = 0; i < 8; i++) cout << a[i] << ", ";
    // 44, 8, 8, 6, 5, 2, 0, -1,
    cout << endl;
    std::sort(a.begin()+2, a.begin()+5);
    // 只排序 a[2]~a[4](5th) 的元素
    return 0;
}
```

## 2. 字串排列
在電腦中每個字元都有對應的整數，稱為 ascii code，例如 '0' 的 ascii code 為 0x30，十進位為 48。所以在做字串排列時其實就是在比較每個字元的 ascii code。
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

int main()
{
    std::string a = "sdgfasd65a4w6sef46";
    std::sort(a.begin(), a.end());
    std::cout << a;
    // 445666aaddeffgsssw
    std::sort(a.begin(), a.end(), std::greater<char>());
    std::cout << a;
    // wsssgffeddaa666544
    return 0;
}
```
而 C++ 的 sort 還可以對字串陣列作排列
```cpp
int main()
{
    std::vector<std::string> p = {"mobile","make","mini","muse","meet"};
    std::sort(p.begin(), p.end());
    for(std::string s:p) std::cout << s + ", ";
    // make, meet, mini, mobile, muse,
    return 0;
}
```
可以看出對於字串陣列排列，依然是依照 ascii code 的順序。

## 3. 多維陣列針對某個 key 排列
在 C++ 中常常使用 unordered_map，為一個無序的 key-value 資料結構，而 sort 並不支援 unordered_map，所以須將其轉成兩個一維陣列或是多維陣列，在 C++ 中可以使用 std::pair<int, int> 這個資料結構，且預設是以第一個參數進行排序。例如有個 unordered_map 中放 <std::string, int>，若想要對此 unordered_map 排序，則需另外宣告一個 std::vector<std::pair<std::string, int>>
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
using namespace std;

bool comp(pair<string, int> a, pair<string, int> b) {
    return a.second == b.second ? a.first < b.first : a.second < b.second;
    // 如果 value 值一樣，則依照前面的字母順序排列
}

int main()
{
    unordered_map<string, int> mp = {
            {"apple", 3},
            {"ace", 5},
            {"bird", 5},
            {"cats", 4}
        };
    
    vector<pair<string, int>> arr;
    for(auto it : mp) arr.emplace_back(it);
    sort(arr.begin(), arr.end());
    // 自訂比較函數
    for(auto [key, value]: arr) cout << key << ' ' << value << endl;
    /*ace 5
    apple 3
    bird 5
    cats 4*/
    sort(arr.begin(), arr.end(), comp);
    // 自訂比較函數
    for(auto [key, value]: arr) cout << key << ' ' << value << endl;
    /*apple 3
      cats 4
      ace 5
      bird 5*/
    return 0;
}
```
