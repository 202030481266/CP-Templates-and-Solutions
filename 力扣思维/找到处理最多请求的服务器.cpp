// https://leetcode.cn/problems/find-servers-that-handled-most-number-of-requests/solutions/
// 技巧：优先队列和有序集合的搭配使用，一个维护编号索引，一个维护具体状态

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // 模拟，区间调度问题
        // 难点在于 i mod k 的分配
        set<int> s;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
        vector<int> res(k);

        for (int i = 0; i < k; ++i) s.emplace(i);
        for (int i = 0; i < arrival.size(); ++i) {
            while (!q.empty() && q.top().first <= arrival[i]) {
                s.emplace(q.top().second);
                q.pop();
            }
            if (s.empty()) continue;
            auto it = s.lower_bound(i % k);
            if (it == s.end()) {
                ++res[*s.begin()];
                q.emplace(arrival[i] + load[i], *s.begin());
                s.erase(s.begin());
            } else {
                ++res[*it];
                q.emplace(arrival[i] + load[i], *it);
                s.erase(it);
            }
        } 
        vector<int> ans;
        int maxx = *max_element(res.begin(), res.end());
        for (int i = 0; i < k; ++i) 
            if (res[i] == maxx) ans.emplace_back(i);
        return ans;
    }

};