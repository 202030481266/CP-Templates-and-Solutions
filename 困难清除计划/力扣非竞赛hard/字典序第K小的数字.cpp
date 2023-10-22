class Solution {
    typedef long long ll;
public:
    int get(int x, ll n) {
        ll a = x, b = x;
        int res = 0;
        while (a <= n) {
            res += min(n, b) - a + 1;
            a = 10 * a;
            b = b * 10 + 9;
        }
        return res;
    }
    int findKthNumber(int n, int k) {
        int ans = 1;
        --k;
        while (k) {
            int tmp = get(ans, n);
            if (tmp <= k) {
                k -= tmp;
                ++ans;
            }
            else {
                ans = ans * 10;
                --k;
            }
        }
        return ans;
    }
};