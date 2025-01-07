// 复杂的构造题目
class Solution {
    typedef long long ll;
public:
    int maxBuilding(int N, vector<vector<int>>& restrictions) {
        int n = restrictions.size();
        sort(restrictions.begin(), restrictions.end());
        vector<ll> a(n + 1), H(n + 1), h(n + 1), c(n + 1);
        vector<ll> pre(n + 1);
        // index start from 1
        for (int i = 0; i < n; ++i) {
            a[i + 1] = restrictions[i][0];
            H[i + 1] = restrictions[i][1];
        }
        H[0] = 0, a[0] = 1;
        for (int i = 1; i <= n; ++i) c[i] = a[i] - a[i - 1];
        multiset<ll> s1, s2; 
        ll sum = 0, ans = 0;
        for (int i = 0; i <= n; ++i) {
            sum += c[i];
            pre[i] = sum;
            s2.emplace(pre[i] + H[i]);
        }
        for (int i = 0; i <= n; ++i) {
            ll mn = 0x3f3f3f3f3f3f3f3f;
            if (!s1.empty()) mn = min(mn, *s1.begin() + pre[i]);
            if (!s2.empty()) mn = min(mn, *s2.begin() - pre[i]);
            h[i] = mn;
            if (i > 0) h[i] = min(h[i], h[i - 1] + c[i]);
            s2.erase(s2.lower_bound(H[i] + pre[i]));  // 只删除一个
            s1.emplace(H[i] + pre[i]);
            ans = max(ans, h[i]);
        }
        for (int i = 0; i < n; ++i) {
            // [i, i + 1] 之间的柱子
            ll tmp = a[i + 1] - a[i];
            if (h[i] == h[i + 1] + tmp) continue;
            ll c = (tmp + h[i + 1] - h[i]) / 2;
            c = min(c, tmp);
            ans = max(ans, min(h[i] + c, h[i + 1] + tmp - c));
        }
        // 最后一段
        ans = max(ans, h[n] + N - a[n]);
        return ans;
    }
};