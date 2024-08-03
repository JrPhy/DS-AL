## 1. map 與 set 的異同
在 C++ STL 中，有兩個使用 RBTree 的資料結構，分別為 map 與 set，而 unordered_map 與 hash_set 則是用 hash map 實作。所以 map 與 set 為有序的資料結構，而 unordered_map 與 hash_set 則是無序的。在實際情況下，若是需要對資料做頻繁的修改，那使用 unordered_map 比較實在，若是需要排序過的資料，則 map 比較適當。

|  | map | set | unordered_map |
| --- | --- | --- | --- |
| 實作 | RBTree | RBTree | array+list |
| 排序 | 已排序 | 已排序 | 未排序 |
| key | 不可重複，無法修改 | 不可重複，無法修改 | 可重複，無法修改 |
| value | 與 key 不同，可修改 | 與 key 相同，無法修改 | 與 key 不同，可修改 |
| TC | O(logn) | O(logn) | O(1)~O(n) |

## 1. map 使用
```cpp 
#include <map> // 使用 map 需要此 header
```
#### 1. 初始化
```cpp
std::map<int, std::string> EngMap; // 宣告一個 map，key 為整數，value 為字串
EngMap.insert(std::pair<int, std::string>(1, "A"));
EngMap.insert(std::pair<int, std::string>(15, "O"));
EngMap.insert(std::pair<int, std::string>(7, "G"));
```
也可以像陣列或是結構那樣初始化
```cpp
std::map<int, std::string> EngMap; // 宣告一個 map，key 為整數，value 為字串
EngMap[1] = "A";
EngMap[7] = "G";
EngMap[15] = "O";
```
```cpp
std::map<int, std::string> studentMap; // 宣告一個 map，key 為整數，value 為字串
EngMap[1] = "A";
EngMap[7] = "G";
EngMap[15] = "O";
```
如果有重複的 key，則會直接覆蓋原值
```cpp
EngMap[1] = "a"; 把 "A" 覆蓋掉
```
#### 2. 印出
印出 map 裡面的值，其中 first 成員為 key，second 成員為 value。
```cpp
for (const auto& x : EngMap) {
    std::cout << x.first << ": " << x.second << "\n";
}
// 1: A
// 7: G
// 15: O
```
印出來後會發現會照著 key 的順序作排列，即便插入時是 15 比 7 先插入。
#### 3. 尋找
在 map 中會使用 find(key) 跟 end() 來搭配使用，若 map.find(key) != map.end() 則表示該 key 存在於 map 中，反之則沒有
```cpp
if (EngMap.find(1) != map.end()) cout << "found\n";
else cout << "not found\n";
```
找到後就會返回該節點的指標。
#### 4. 刪除
使用 erase(key) 成員函數來刪除該 key 與 value，如果 key 不存在於 map 中並不會造成 crash。
```cpp
EngMap.erase(1); // {1, "A"} 被刪除
EngMap.erase(2); // 不會發生什麼事
```

#### 5. 其他用法
```cpp
EngMap.size() // 返回大小
EngMap.empty() // 是否為空
EngMap.clear() // 清除所有 key 與 value
```

#### 6. 善用 map 取代多個 if...else if
在某些例子中，我們會需要使用一個 FLAG 來決定需要呼叫哪支函數，例如
```cpp
typedef unsigned char uchar
void func0(...) {...};
void func1(...) {...};
void func2(...) {...};

bool OnStateChange(uchar flag) 
{
    if (flag == 0) func0(...);
    else if (flag == 1) func1(...);
    else if (flag == 2) func2(...);
    else 
    {
        printf("ERROR!\n");
        return false;
    }       
    return true;
}

int main()
{
    uchar flag = 1;
    OnStateChange(flag);
    return 0;
}
```
在此我們就可以寫一個 map，value 為一個指標函數，使用上就會更簡潔，也可參考 [C 語言的作法](https://github.com/JrPhy/C_tutorial/blob/main/CH8-%E6%8C%87%E6%A8%99%E8%88%87%E5%87%BD%E6%95%B8.md#5-%E5%96%84%E7%94%A8%E6%8C%87%E6%A8%99%E5%87%BD%E6%95%B8%E6%B8%9B%E5%B0%91%E7%A8%8B%E5%BC%8F%E7%A2%BC)。
```cpp
#include <iostream>
#include <map>
typedef unsigned char uchar;
void func1() {printf ("func1\n");};
void func2() {printf ("func2\n");};
void func3() {printf ("func3\n");};

int main ()
{
  uchar flag = 1;
  std::map < int, void (*)() > FuncMap;
  FuncMap[1] = func1;
  FuncMap[2] = func2;
  FuncMap[3] = func3;
  FuncMap[2]();
  return 0;
}
```

## 2. set 使用
與 map 的主要差異就是 key 即為 value 且不能修改只能刪除，而且因為 key 不能重複，所以相同的資料只會有一組。
#### 1. 初始化
```cpp
std::set<int> myset = {3, 1, 2, 8, 5, 2};
```
或是先開一個 set 然後用 insert
```cpp
std::set<int> myset;
myset.insert(3);
myset.insert(1);
myset.insert(2);
myset.insert(8);
myset.insert(5);
myset.insert(2);
```
也可以開一個 array 來做初始化
```cpp
int arr[] = {3, 1, 2, 8, 5, 2};
std::set<int> myset(arr, arr+5);
```
#### 2. 印出
印出 map 裡面的值。
```cpp
for (const auto& x : myset) {
    std::cout << x << ", ";
}
// 1, 2, 3, 5, 8
```
印出來後會發現會照著 key 的順序作排列，即便初始化是無序的。其中 2 出現了兩次，但是印出來也只有一個 2。
#### 3. 尋找
在 map 中會使用 find(key) 跟 end() 來搭配使用，若 map.find(key) != map.end() 則表示該 key 存在於 map 中，反之則沒有
```cpp
if (myset.find(1) != myset.end()) cout << "found\n";
else cout << "not found\n";
```
找到後就會返回該節點的指標。而相同的 key 在 set 中只會出現一次，所以也可以只用 count(key) == 1 來做判斷
```cpp
if (myset.count(1)) cout << "found\n";
else cout << "not found\n";
```
count 可以當作是返回一個 bool，與 find 的回傳值不同。
#### 4. 刪除
使用 erase(key) 成員函數來刪除該 key 與 value，如果 key 不存在於 map 中並不會造成 crash。
```cpp
myset.erase(1); // {1, "A"} 被刪除
myset.erase(4); // 不會發生什麼事
```

#### 5. 其他用法
```cpp
myset.size() // 返回大小
myset.empty() // 是否為空
myset.clear() // 清除所有 key 與 value
```
