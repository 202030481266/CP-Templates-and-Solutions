class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        const int MOD = 1e9 + 7;
        // sum1：区间和，sum2：区间平方和
        long long sum1[n * 4 + 10], sum2[n * 4 + 10];
        // 因为是区间修改，所以要懒标记下推
        int lazy[n * 4 + 10];
        memset(sum1, 0, sizeof(sum1)); 
        memset(sum2, 0, sizeof(sum2));
        memset(lazy, 0, sizeof(lazy));

        // 根据公式维护区间加 K
        auto add = [&](int id, int l, int r, int K) {
            int len = r - l + 1;
            sum2[id] = (sum2[id] + 2LL * K * sum1[id] + 1LL * K * K % MOD * len) % MOD;
            sum1[id] = (sum1[id] + 1LL * K * len) % MOD;
        };

        // 懒标记下推
        auto down = [&](int id, int l, int r) {
            int nxt = id << 1, mid = (l + r) >> 1;
            lazy[nxt] += lazy[id]; add(nxt, l, mid, lazy[id]);
            lazy[nxt | 1] += lazy[id]; add(nxt | 1, mid + 1, r, lazy[id]);
            lazy[id] = 0;
        };

        // 区间加 1
        function<void(int, int, int, int, int)> modify = [&](int id, int l, int r, int ql, int qr) {
            if (ql <= l && r <= qr) {
                add(id, l, r, 1);
                lazy[id]++;
            } else {
                if (lazy[id]) down(id, l, r);
                int nxt = id << 1, mid = (l + r) >> 1;
                if (ql <= mid) modify(nxt, l, mid, ql, qr);
                if (qr > mid) modify(nxt | 1, mid + 1, r, ql, qr);
                sum1[id] = (sum1[nxt] + sum1[nxt | 1]) % MOD;
                sum2[id] = (sum2[nxt] + sum2[nxt | 1]) % MOD;
            }
        };

        long long ans = 0;
        // last[x] 表示元素 x 最近出现在哪个下标
        unordered_map<int, int> last;
        for (int i = 1; i <= n; i++) {
            int &old = last[nums[i - 1]];
            modify(1, 1, n, old + 1, i);
            old = i;
            // 答案就是 [1, i] 这段区间的 sum2 之和
            ans = (ans + sum2[1]) % MOD;
        }
        return ans;
    }
};

