再窮舉的時候會需要把每個例子都跑一次，例如給 3 個數字，我想要找出這組數字的所有不重複數字排列。最簡單的做法就是跑三次迴圈，每次迴圈都是跑 1~3
```cpp
for(int i = 1; i <4; i++) {
    for(int j = 1; j <4; j++) {
        for(int k = 1; k <4; k++) {
            printf("%d  %d  %d\n", i, j, k);
        }
    }
}
```
但是當我們需要給 n 個數字去找，就需要手動去加迴圈，所以會希望改寫成遞迴，藉由傳入一個參數來達到給 n 個數字的效果。從上面的程式碼可以知道，我們是重複的去呼叫迴圈，所以該函數內就是放迴圈，給一個 level 參數來決定最後到底要跑幾層迴圈，並給一個結束條件。在此條件中就是```level == target```，而起始層數就是 0。
```cpp
#include <iostream>
void f(int level, int target, int nums[], int len) {
    if(level == target) {
        for(int i = 0; i < len; i++)
            printf("%d  ", nums[i]);
        printf("\n");
        return;
    }
    for(nums[level] = 1; nums[level] < target+1; nums[level]++) {
        f(level+1, target, nums, len);
    }
}
int main()
{
    const int len = 4;
    int nums[len];
    for(int i = 1; i < len+1; i++) nums[i-1] = i;
    f(0, len, nums, len);
    return 0;
}
```
像此種方法較常拿來作排列組合的問題，如[77. Combinations](https://leetcode.com/problems/combinations/description/)。做組合時，會先任一取一個，然後再從剩下的去取，接著重複去做，直到列出所有可能為止。
```cpp
#include <vector>
#include <iostream>
using namespace std;
void generateCombinations(int start, int n, int k, vector<int> &combination, vector<vector<int>> &result) {
    if (k == 0) {
        result.push_back(combination);
        return;
    }
    for (int i = start; i <= n; ++i) {
        combination[combination.size() - k] = i;
        generateCombinations(i + 1, n, k - 1, combination, result);
    }
}

int main()
{
    int n = 4, k = 2;
    vector<vector<int>> result;
    vector<int> combination(k);
    generateCombinations(1, n, k, combination, result);
    
    for(auto i:result) {
        for(int j:i) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}
```
