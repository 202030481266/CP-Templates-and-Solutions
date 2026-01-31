// 构造下一个大的排列算法
// 找到最小的降序，然后使用一个最小的数字替换然后后面全部升序排列即可
class Solution {
public:
    string nextPalindrome(string num) {
        int n = num.size() / 2;
        // 只需要观察[0, n) 即可
        int p = -1;
        for (int i = n - 2; i >= 0; --i) {
            if (num[i] < num[i + 1]) {
                p = i;
                break;
            }
        }
        if (p == -1) return "";
        int l = p + 1, r = n;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (num[mid] > num[p]) l = mid;
            else r = mid;
        }
        char c = num[l];
        l = p, r = n - 1 ;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (num[mid] <= c) r = mid;
            else l = mid;
        }
        swap(num[p], num[r]);
        swap(num[num.size() - p - 1], num[num.size() - r - 1]);
        sort(num.begin() + p + 1, num.begin() + n); // [p + 1, n)
        for (int i = p + 1; i < n; ++i) {
            num[num.size() - 1 - i] = num[i];
        }
        return num;
    }
};