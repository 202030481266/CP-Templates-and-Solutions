/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int l = 0, r = 10001;
        while (l + 1 < r) {
            int mid = (l + r) >> 1, res = reader.get(mid);
            if (res == 2147483647 || res > target) r = mid;
            else l = mid;
        }
        return reader.get(l) == target ? l : -1;
    }
};