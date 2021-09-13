資料結構是指電腦中儲存、組織資料的方式，通常資料結構會伴隨著演算法，正確的資料結構會讓計算量降低。然而 C 語言是一種非常簡單的語言，相較於 Java、C++、Python，C 的許多資料結構需要自己寫，不像其他高階語言有內建。\
一般常見的資料結構有：\
陣列 (Array)、堆疊 (Stack)、佇列 (Queue)、連結串列 (Linked List)、樹 (Tree)、圖 (Graph)、雜湊表 (Hash table)。\
上述提到的資料結構除了陣列以外，在 C 語言實作皆需使用到指標，所以必須對於指標非常熟悉。

而在資訊工程中常見的演算法有：搜尋 (Search)、排序 (Sorting)。
在搜尋演算法中，針對已排序過的陣列可使用二元搜尋(Binary Search)，並有在 C 的標準函示庫中。若是有多餘的記憶體，則可自行建立 Hash Table 並使用該表作搜尋。
相較於搜尋算法，排序算法種類就更多，常見的排序算法有快速排序(Quick Sort)，並有在 C 的標準函示庫中，而在 Linux 中則是使用 Merge Sort。在排序算法中，除了一般的多餘記憶體使用跟計算複雜度外，還多了穩定與不穩定要考慮。所謂的穩定或不穩定來自於，當一個資料結構內有兩個相同的元素，則兩者的位置會不會交換，若會則為不穩定，反之為穩定。\
各種排序算法的比較可參考 https://en.wikipedia.org/wiki/Sorting_algorithm \

評斷一個算法的記憶體使用量與時間使用量，通常會使用大 O 符號 (big-O natation) 來表示，假設一個資料結構中有 n 筆資料，使用了 A 和 B 兩種算法，其記憶體使用量分別為 O(n)、O(n<sup>2</sup>)，而時間使用量分別為  O(n)、O(logn)，則我們會說：「**當資料量越多時**，A 算法所佔的記憶體空間較多，而 B 算法記憶體所花的時間較多。」\
big-O 的精神在於資料量與所使用的空間/時間趨勢，但不代表時間複雜度 O(n) 在任何情況下一定比時間複雜度 O(logn) 的算法還要慢，在某些情況是剛好反過來的，例如資料量非常少的時候。所以不會有一種算法是最好的，只有對於該情況最適用的算法。
