## 1. 介紹

Hash table 是一種輸入 key 得到 value 的資料結構，最簡單的 Hash table 就是 array，key 就是 index，所以我們可以透過 key 來取得對應位置的資料。而在其他語言中常見的字典 (Dictionary) 也是一種 Hash table，在 C++ 中也有 unorder_map 可以使用，而 map 在 C++ 中則是用紅黑樹實作。

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

最主要的是 Overflow 與 Collision 這兩個問題，key 如果超過容器大小會造成 runtime crash，通常可以使用模數 (mod %) 來簡單的處理，而 Collision 則會使得原本的值被覆蓋造成值被取錯，以下會介紹一些方法來避免這兩個問題。\
假設容器的容量為 0 ~ m-1，值的範圍在 0 ~ n-1，

#### 1. 開放定址 Open Addressing
先將值的範圍藉由 mod 映射到 0 ~ m-1，也就是 h(x) = x mod m，如果有另一個值也被映射到同個 key，也就是 h(x<sub>1</sub>) = h(x<sub>2</sub>)，那就在這個映射值後往後找空位，找到後就可以放入，稱為探測法 (probing)。
```C
int len = 10, map[len] = {0};
int Insert_to_map(int map[], int len, int key) {
    int in_map = 0;
    for (int i = 0; i < len; i++ ) {
        if (0 == map[key%len+i]) {
            map[key%len+i] = value;
            in_map = 1;
            break;
        }
    }
    return in_map;
}
```
```C
int len = 10, map[len] = {0};
int Is_in_map(int map[], int len, int key) {
    return in_map[key];
}
```
雖然這個方法可以解決 Collision 與 Overflow 的問題，但是卻無法知道該組 (key, value) 是否真的存在於 map 中。例如 h(x) = x mod 10，(8, 15), (18, 2)，h(8) = h(18) = 8。如果 (8, 15) 在而 (18, 2) 不在，但是因為 h(18) = 8，所以 Is_in_map(map, 10, 18) 會返回 15，就不是返回正確的值，所以還需要再多放一些資料才能夠找到正確的值，不過這個的問題有很多例子，例如 (8, 15), (9, 6), (18, 2)，當前面兩組資料已放在 map 裡後，h(18) = 8，所以會找到第九個位置，但是 h(9) = 9 也已經被佔用了，所以還需要往後移動，所以以這個例子來說，至少還要再多個欄位去處理往後找了幾次。在設計上就需要開個多維陣，也可在後面去**串接 list**，此方法稱為 Chaining。\
![image](https://github.com/JrPhy/DS-AL/blob/master/pic/hash_collision.jpg)
#### 2. 串鍊 Chaining
串鍊的資料結構可看成 linked-list of array，也就是開一個 n 為的 node array，然後前面存 key，如果發生碰撞，那就直接在首加入資料。在此我們只需要在首加入即可，這樣可以省下走訪的時間，其餘的尋找與刪除和 [linked-list](https://github.com/JrPhy/DS-AL/blob/master/List_and_Tree/LinkedList-%E5%96%AE%E5%90%91%E9%80%A3%E7%B5%90.md) 的尋找與刪除一樣。 
```C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct _node
{
    int key;
    int data;
    struct _node *next;
}node;

node* newNode(int key, int value)
{
    node *tmpNode = malloc(sizeof(node));
    if(tmpNode!=NULL) {
        tmpNode->key = key;
        tmpNode->data = value;
        tmpNode->next = NULL;
    }
    return tmpNode;
}

int lenOfList(node *list)
{
    int length = 0;
    while(list != NULL)
    {
        ++length;
        list = list->next;
    }
    return length;
}

void insertNode(node **list, int key, int value)
{
    node *new_node = newNode(key, value);
    new_node->next = *list;
    *list = new_node;
}

bool deleteNode(node **list, int key) 
{
    int position = 0;
    node *temp = *list;
    while(temp != NULL)
    {
        if (key == temp->key && 0 == position) {
            *list = temp->next;
            free(temp);
            return true;
        }
        else if (temp->next != NULL && key == temp->next->key && temp->next->data) break;
        ++position;
        temp = temp->next;
    }
    //temp = *list;
    //for (int i = 0; temp != NULL && i < position - 1; ++i) temp = temp->next;
    
    if (temp == NULL || temp->next == NULL) return false;
    
    node *nodeToBeDel = temp->next;
    temp->next = nodeToBeDel->next;

    free(nodeToBeDel);
    return true;
}

void push_into_map(node *map[], int n, int key, int value) {
    insertNode(&map[key%n], key, value);
}

bool del_from_map(node *map[], int n, int key) {
    if (0 == key) return deleteNode(&map[0], 0);
    else return deleteNode(&map[key%n], key);
}

void print_map(node *map[], int key) {
    node *list = map[key];
    printf("%d->", key);
    while(list != NULL)
    {
        printf("(%d, %d)->", list->key, list->data);
        list = list->next;
    }
    printf("\n");
}

bool is_in_map(node *map[], int n, int key) {
    node *list = map[key%n];
    while(list != NULL)
    {
        if (key == list->key && list->data) return true;
        list = list->next;
    }
    return false;
}

int main() {
    int n = 10;
    node *map[n]; 
    for (int i = 0; i < n; i++) {
        map[i] = newNode(i, i);
    }
    push_into_map(map, n, 39, 28);
    push_into_map(map, n, 29, 11);
    push_into_map(map, n, 99, 2);
    push_into_map(map, n, 33, 22);
    for (int i = 0; i < n; i++) {
        print_map(map, i);
    }
    printf("============\n");
    is_in_map(map, n, 40);
    del_from_map(map, n, 33);
    del_from_map(map, n, 45);
    del_from_map(map, n, 9);
    del_from_map(map, n, 8);
    del_from_map(map, n, 8);
    del_from_map(map, n, 0);
    for (int i = 0; i < n; i++) {
        print_map(map, i);
    }
    return 0;
}
```
![image](https://github.com/JrPhy/DS-AL/blob/master/pic/hash_chain.jpg)
