/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares 4 different elements in the array
 *     // return 4 if the values of the 4 elements are the same (0 or 1).
 *     // return 2 if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
 *     // return 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
 *     int query(int a, int b, int c, int d);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
public:
    int guessMajority(ArrayReader &reader) {
        // 有意思的题目
        // 利用线性次数的操作可以计算出所有的取值
        int n = reader.length();
        vector<int> arr(n);
        arr[0] = 0;// 假设就是0
        // 先计算前面四个
        if (reader.query(0, 2, 3, 4) == reader.query(1, 2, 3, 4)) arr[1] = 0;
        else arr[1] = 1;
        if (reader.query(0, 1, 3, 4) == reader.query(1, 2, 3, 4)) arr[2] = 0;
        else arr[2] = 1;
        if (reader.query(0, 1, 2, 4) == reader.query(1, 2, 3, 4)) arr[3] = 0;
        else arr[3] = 1;
        int pre = reader.query(0, 1, 2, 3), cur;
        for (int i = 1; i + 3 < n; ++i) {
            cur = reader.query(i, i + 1, i + 2, i + 3);
            if (pre == cur) arr[i + 3] = arr[i - 1];
            else arr[i + 3] = arr[i - 1] ^ 1;
            pre = cur;
        }
        int cnt0 = 0, cnt1 = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i]) ++cnt1;
            else ++cnt0;
        }
        if (cnt0 == cnt1) return -1;
        else if (cnt0 > cnt1) return 0;
        else {
            for (int i = 1; i < n; ++i) {
                if (arr[i]) return i;
            }
        }
        return -1;
    }
};