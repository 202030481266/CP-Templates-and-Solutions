/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
    unordered_map<int, int> cache;
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        // 二分搜索进阶版本
        int n = mountainArr.length();

        auto get = [&](int i) -> int {
            if (cache.count(i)) return cache[i];
            int num = mountainArr.get(i);
            cache[i] = num;
            return num;
        };

        auto f = [&](int index) -> bool {
            // 1 is ascend, 0 is descend
            if (index == 0) return 1; 
            else if (index == n - 1) return 0;
            else return get(index) > get(index - 1);
        };

        function<int(int,MountainArray&,int,int)> dfs = [&](int target, MountainArray& mountainArr, int l, int r) -> int {
            cout << l << ' ' <<r << endl;
            if (l > r) return -1;
            if (l == r) return (get(l) == target ? l : -1);
            int mid = (l + r) >> 1, ans = -1, x = get(mid);
            if (target == x) {
                ans = mid;
                int tmp = dfs(target, mountainArr, l, mid - 1);
                if (tmp != -1) ans = tmp;
                return ans;
            }
            else if (x < target) {
                // ascend , [l, mid]
                if (f(mid)) return dfs(target, mountainArr, mid + 1, r);
                // descend [mid, r]
                else return dfs(target, mountainArr, l, mid - 1);
            }
            else {
                int x = dfs(target, mountainArr, l, mid - 1);
                if (x != -1) return x;
                else return dfs(target, mountainArr, mid + 1, r);
            }
        };
        return dfs(target, mountainArr, 0, n - 1);
    }
};