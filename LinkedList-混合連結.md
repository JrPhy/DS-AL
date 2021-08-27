在做單向做鏈結時有可能不小心把尾端接到了其他地方，形成了一個單項鏈結與一個環狀鏈結，此時若呼叫其他單項鏈結的函數就可能會造成無窮迴圈。在此介紹一個避免此情況發生的算法：Floyd Cycle Detection Algorithm

## 1. Floyd Cycle Detection Algorithm
此算法又稱龜兔賽跑演算法，由 Robert W. Floyd 提出。主要思路是若一個鏈結有環，則可以使用兩個一快一慢的 node 來檢查，當 next 指向同一位置時即表示兩指標在環狀鏈結裡面走了一陣子。
```C
int hasCycle(node *head) 
{
    node *fast = *slow = head;
    while (fast != NULL && fast->next != NULL) 
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return 1;
    }
    return -1;
}
```
在此算法中，快速指標一次走兩格，慢速指標一次走一格，所以可以利用此概念來算出環有多長。
## 2. 計算環的長度
假設環的長度為 n，可以把快慢速指標**相遇的**位置記錄下來，然後用快指標整個走訪一圈，當走到的位置或下一個位置與相遇的相等即結束迴圈。
```C
int hasCycle(node *head) 
{
    int count = 0, cycle = 0;
    node *fast = *slow = head, node *current = NULL;
    while (fast != NULL && fast->next != NULL) 
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow) 
        {
            cycle = 1;
            current = slow;
        }
        if(cycle == 1)
        while (fast != current && fast->next != current)
        {
            count = count + 2;
            if(fast->next->next == current) count = count + 2;
            else if(fast->next == current) ++count;
            fast->next->next
        }
    }
    return count;
}
```
## 3. 計算環的起點
假設環的長度為 n，起點到環的入口長度為 m，第一次相遇距起點為 k。已知快指標速度是慢指標的兩倍，設快指標第二次到**相遇**點時，快指標共走了 a 圈，慢指標共走 b 圈，，然後用快指標整個走訪一圈，當走到的位置或下一個位置與相遇的相等即結束迴圈。
```C
int hasCycle(node *head) 
{
    int count = 0, cycle = 0;
    node *fast = *slow = head, node *current = NULL;
    while (fast != NULL && fast->next != NULL) 
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow) 
        {
            cycle = 1;
            current = slow;
        }
        if(cycle == 1)
        {
            slow = current->next;
            count = 1;
            while (slow != current) slow = slow->next;
            {
                slow = slow->next;
                ++count;
            }
            
    }
    return count;
}
```
