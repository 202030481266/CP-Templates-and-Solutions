struct node {
    int s, d, r, id;
    node(int _s, int _d, int _id): s(_s), d(_d), id(_id) { r = s % d; }
    bool operator < (const node& rhs) const {
        return (d == rhs.d ? (r == rhs.r ? s < rhs.s : r < rhs.r) : d < rhs.d); 
    }
};
const int mod = 1e9 + 7;
using ll = long long;
class Solution {
public:
    vector<int> solve(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size();

        // 此题难度很高
        // 实际上算法分析复杂度最高就是 n*sqrt(n)， 最高 1.58 * 10^7，显然我这个复杂度比分块的 m*sqrt(n) 还是要好的
        // 同类查询， d 和 r 相同

        vector<node> q;
        for (int i = 0; i < m; ++i)
            q.push_back(node(queries[i][0], queries[i][1], i));

        sort(q.begin(), q.end());

        vector<int> ans(m);

        auto f = [&](int l, int r) {
            // [l, r) 同类
            ll sum = 0;
            for (int i = q[l].s; i < n; i += q[l].d) {
                sum += nums[i];
            }
            for (int i = q[l].s, j = l; i < n && j < r; i += q[l].d) {
                while (j < r && q[j].s == i) {
                    ans[q[j].id] = sum % mod;
                    ++j;
                }
                sum -= nums[i];
            }
        };

        int pre = 0;
        for (int i = 1; i < m; ++i) {
            if (q[i].d != q[pre].d || q[i].r != q[pre].r) {
                // [pre, i)
                f(pre, i);
                pre = i;
            }
        }
        f(pre, m);
        return ans;
    }
};