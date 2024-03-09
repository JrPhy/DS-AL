## 1. map 與 set 的異同
在 C++ STL 中，有兩個使用 RBTree 的資料結構，分別為 map 與 set，而 unorder_map 與 hash_set 則是用 hash map 實作。所以 map 與 set 為有序的資料結構，而 unorder_map 與 hash_set 則是無序的。在實際情況下，若是需要對資料做頻繁的修改，那使用 unorder_map 比較實在，若是需要排序過的資料，則 map 比較適當。

|  | map | set |
| --- | --- | --- |
| 實作 | RBTree | RBTree |
| 排序 | 已排序 | 已排序 |
| key | 不可重複，無法修改 | 不可重複，無法修改 |
| value | 與 key 不同，可修改 | 與 key 相同，無法修改 |

## 1. map 使用
```cpp 
#include <map> // 使用 map 需要此 header
```
#### 1. 初始化
```cpp
std::map<int, std::string> EngMap; // 宣告一個 map，key 為整數，value 為字串
EngMap.insert(std::pair<int, std::string>(1, "A"));
EngMap.insert(std::pair<int, std::string>(7, "G"));
EngMap.insert(std::pair<int, std::string>(15, "O"));
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
```
#### 3. 尋找
在 map 中會使用 find(key) 跟 end() 來搭配使用，若 map.find(key) != map.end() 則表示該 key 存在於 map 中，反之則沒有
```cpp
if (EngMap.find(1) != map.end()) cout << "found\n";
else cout << "not found\n";
```

#### 4. 刪除
使用 erase(key) 成員函數來刪除該 key 與 value，如果 key 不存在於 map 中並不會造成 crash。
```cpp
EngMap.erase(1); // {1, "A"} 被刪除
EngMap.erase(2); // 不會發生什麼事
```

#### 5. 其他用法
```cpp
EngMap.size() // 返回大小
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

## 2. set
