/*
// 对拍程序
int maxIncreasingGroups(vector<int>& usageLimits) {
        int n = usageLimits.size();
        priority_queue<int> q;
        for (int i = 0; i < n; ++i) 
            q.emplace(usageLimits[i]);
        int k = 1;
        while (q.size() >= k) {
            vector<int> tmp;
            for (int i = 0; i < k; ++i) {
                int u = q.top();
                q.pop();
                tmp.emplace_back(u);
            }
            for (int& c : tmp) {
                if (c > 1) {
                    q.emplace(c - 1);
                }
            }
            ++k;
        }
        //
        return k - 1;
    }
*/
// 上面的复杂度太高了，必须使用更加优秀的算法来实现
// 本质就是构造出 1, 2, 3, 4....K 求解 K 的最大值
class Solution {
    typedef long long ll;
public:
    int maxIncreasingGroups(vector<int>& b) {
        vector<ll> a(b.begin(), b.end());
        sort(a.begin(), a.end());
        ll ans = 1;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] >= ans) a[i] -= ans++;
            if (i + 1 < a.size()) a[i + 1] += a[i];
        }
        return ans - 1;
    }
};