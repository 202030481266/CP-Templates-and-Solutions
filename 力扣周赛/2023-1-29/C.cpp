class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n = weights.size();
        if (k == 1) return 0;
        vector<long long> a(n - 1, 0);

        for (int i = 0; i < n - 1; ++i) 
            a[i] = weights[i] + weights[i + 1];
        // 寻找和最大的长度为k的序列和和最小的长度为k的序列
        long long maxx = 0, minn = 0;
        priority_queue<long long, vector<long long>, greater<long long>> q1;
        priority_queue<long long, vector<long long>, less<long long>> q2;
        if (a.size() == k - 1) return 0;
        for (int i = 0; i < k - 1; ++i) {
            q1.emplace(a[i]);
            q2.emplace(a[i]);
            maxx += a[i];
            minn += a[i];
        }
        for (int i = k - 1; i < a.size(); ++i) {
            if (a[i] > q1.top()) {
                maxx += a[i];
                maxx -= q1.top();
                q1.pop();
                q1.emplace(a[i]);
            }
            if (a[i] < q2.top()) {
                minn += a[i];
                minn -= q2.top();
                q2.pop();
                q2.emplace(a[i]);
            }
        }
        return maxx - minn;
    }
};