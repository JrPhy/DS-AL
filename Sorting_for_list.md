因為 linked list 不是 C 語言內建的資料結構，故 C 中的 qsort 並不支援 list 的排序，需要自己寫。而兩者的差異在於 array 可以直接使用 index 做操作，list 沒辦法，所以在 list 寫法上會比較複雜。但  可以藉由末節點指向 NULL 來計算長度。當然也可以將 list 裡面的元素用 array 儲存起來，在對 array 排序完後就放進 list 中。

## 1. 氣泡排序法
氣泡排序法因為是與鄰近的元素倆倆比較，所以在實作上幾乎與 array 版本無差別。
```C
void bubbleSort(node **list)
{
    int i, j, a;
    node *temp1 = NULL, *temp = NULL;

    for(temp1 = *list; temp1 != NULL; temp1 = temp1->next)
    {
        for(temp2 = temp1->next; temp2!=NULL; temp2 = temp2->next)
        { 
            if(temp2->data < temp1->data)
            {
                a = temp1->data;
                temp1->data = temp2->data;
                temp2->data = a;
                
            }
        }
    }
}
```
