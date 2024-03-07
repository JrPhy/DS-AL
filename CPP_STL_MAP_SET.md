## 1. map 與 set 的異同
在 C++ STL 中，有兩個使用 RBTree 的資料結構，分別為 map 與 set，而 unorder_map 與 hash_set 則是用 hash map 實作。所以 map 與 set 為有序的資料結構，而 unorder_map 與 hash_set 則是無序的。在實際情況下，若是需要對資料做頻繁的修改，那使用 unorder_map 比較實在，若是需要排序過的資料，則 map 比較適當。

|  | map | set |
| --- | --- | --- |
| 實作 | RBTree | RBTree |
| 排序 | 已排序 | 已排序 |
| key | 不可重複，無法修改 | 不可重複，無法修改 |
| value | 與 key 不同，可修改 | 與 key 相同，無法修改 |

## 1. map 使用
```cpp#include <map> // 使用 map 需要此 header```
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
