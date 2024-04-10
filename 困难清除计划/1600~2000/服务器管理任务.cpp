class Solution {
public:
    using pii = pair<int, int>;
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size(), m = tasks.size();
        // 优先队列维护task
        // set空闲队列
        set<pii> s;
        priority_queue<pii, vector<pii>, greater<pii>> q;

        for (int i = 0; i < n; ++i)
            s.emplace(servers[i], i);

        vector<int> ans;
        int id, time = 0;

        for (int i = 0; i < m; ++i) {
            if (i > time) time = i; // 没有到达可以启动的时间，更新时间
            while (!q.empty() && q.top().first <= time) { // 可用的服务器全部出队
                id = q.top().second;
                q.pop();
                s.emplace(servers[id], id);
            }
            if (s.empty()) {
                // 没有可用的服务器，时间继续推
                int tmp = q.top().first;
                while (!q.empty() && q.top().first == tmp) {
                    id = q.top().second;
                    q.pop();
                    s.emplace(servers[id], id);
                }
                time = tmp; // 更新现在的时间
            }
            id = s.begin()->second;
            ans.push_back(id);
            s.erase(s.begin());
            q.emplace(tasks[i] + time, id); // 消耗服务器
        }

        return ans;
    }
};