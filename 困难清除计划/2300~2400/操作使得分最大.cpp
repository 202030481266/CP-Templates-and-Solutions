class Solution {
    static constexpr int mod = 1e9 + 7;
    long long b[100005];
public:
    long long power(long long a, int b) {
        long long res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
        }
        return res;
    }
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> a(n); 
        for (int i = 0; i < n; ++i) {
            int tmp = nums[i], cnt = 0;
            for (int d = 2; (long long)d * d <= tmp; ++d) {
                if (tmp % d == 0) ++cnt;
                while (tmp % d == 0) 
                    tmp /= d;
            }
            if (tmp > 1) ++cnt;
            a[i] = cnt;
        }
        stack<int> s;
        vector<int> right(n, n);
        vector<int> left(n, -1);
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && a[s.top()] < a[i]) {
                right[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        while (!s.empty()) s.pop();
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && a[s.top()] <= a[i]) {
                left[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        for (int i = 0; i < n; ++i) {
            b[nums[i]] += (1ll * (i - left[i]) * (right[i] - i));
        }
        long long ans = 1;
        for (int i = 100000; i >= 1; --i) {
            if (!b[i]) continue;
            if (k > b[i]) ans = ans * power(i, b[i]) % mod, k -= b[i];
            else {
                ans = ans * power(i, k) % mod;
                break;
            }
        }
        return ans;
    }
};