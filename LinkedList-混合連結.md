在做單向做鏈結時有可能不小心把尾端接到了其他地方，形成了一個單項鏈結與一個環狀鏈結，此時若呼叫其他單項鏈結的函數就可能會造成無窮迴圈。在此介紹一個避免此情況發生的算法：Floyd Cycle Detection Algorithm。此算法有三個功能
1. 檢測鏈結是否有環
2. 若 1 成立，計算該環的長度
3. 若 1 成立，找出進入環的節點

## 1. Floyd Cycle Detection Algorithm
此算法又稱龜兔賽跑演算法，由 Robert W. Floyd 提出。主要思路是若一個鏈結有環，則可以使用兩個一快一慢的 node 來檢查，當 next 指向同一位置時即表示兩指標在環狀鏈結裡面走了一陣子。在此算法中，快速指標一次走兩格，慢速指標一次走一格，所以可以利用此概念來算出環有多長。

## 2. 計算環的長度
假設環的長度為 n，可以把快慢速指標**相遇的**位置記錄下來，然後用快指標整個走訪一圈，當走到的位置或下一個位置與相遇的相等即結束迴圈。

## 3. 計算環的起點
假設環的長度為 n，起點到環的入口長度為 m，第一次相遇距環的入口為 k。已知快指標速度是慢指標的兩倍，設快指標第二次到**相遇**點時，快指標共走了 m + (n-k) + 2k 步，慢指標共走 m + k 步，又 2(m+k) = m + (n-k) + 2k，可得 m = n - k，即慢指標與快指標第一次相遇後，將快指標指向起點，然後走一次一步，接著慢指標繼續從相遇點往前走，在下一次遇到的點就是環的入口了。
```C
node *hasCycle(node *head) 
{
    int count = 0, cycle = 0;
    node *fast = *slow = head, node *current = NULL;
    while (fast != NULL && fast->next != NULL) 
    {
        //檢測是否有環
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow) 
        {
            cycle = 1;
            current = slow;
        }
        
        //若有環，計算環的長度
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
        fast = head;
        
        //若有環，找出進入環的節點
        while(fast != current)
        {
            fast = fast->next;
            slow = slow->next;
        }
        slow->data = count;
    }
    return slow;
}
```
