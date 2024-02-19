/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y] 
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
public:
    int getIndex(ArrayReader &reader) {
        // [l, r)，r - l 是偶数，那么可以区分前面半部分的和以及后面半部分的和
        // [l, r)，r - l是奇数，那么获取其中的除了中间的数字的左右两部分的和
        int l = 0, r = reader.length();
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if ((r - l) & 1) {
                int res = reader.compareSub(l, mid - 1, mid + 1, r - 1);
                if (res == 0) return mid;
                else if (res == 1) r = mid;
                else l = mid + 1;
            }
            else {
                int res = reader.compareSub(l, mid - 1, mid, r - 1);
                if (res == 1) r = mid;
                else l = mid;
            }
        }
        return l;
    }
};