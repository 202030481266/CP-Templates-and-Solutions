class Solution {
public:
    // 大模拟+状态机
    using PII = pair<int, int>;
    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        auto cmp = [&](int x, int y) {
            int l = (time[x][0] + time[x][2]);
            int r = (time[y][0] + time[y][2]);
            return l != r ? l < r : x < y;
        };
        
        // 左边和右边的等待队列
        priority_queue<int, vector<int>, decltype(cmp)> L(cmp), R(cmp);
        
        // 左边「放下」状态队列和右边「搬起」状态队列，PII 的第一关键字是完成时间，第二关键字是工人ID
        priority_queue<PII, vector<PII>, greater<PII>> ql, qr;
        
        // 剩余待处理货物数量和当前时间
        int rest = n, cur = 0;
        for (int i = 0; i < k; i++) L.push(i);
        
        while (rest > 0 || qr.size() > 0 || R.size() > 0) {
            // 1. 如果搬起或者放下的工人在此时已经完成，则将他们依次加入左边或者右边的等待队列。
            while (qr.size() && qr.top().first <= cur) {
                R.push(qr.top().second);
                qr.pop();
            }
            while (ql.size() && ql.top().first <= cur) {
                L.push(ql.top().second);
                ql.pop();
            }

            // 如果右边有人等待，则取优先级最低的工人过桥，过桥后放入左侧的处于「放下」状态的队列。
            if (R.size() > 0) {
                int x = R.top(); R.pop();
                cur += time[x][2];
                ql.push({cur + time[x][3], x});
            } else if (L.size() > 0 && rest > 0) {
            // 否则如果旧仓库还有货物，并且左侧有等待的工人，则取优先级最低的工人过桥，过桥后放入右侧处于「搬起」状态的队列，并使得旧仓库待搬运货物数量减一。
                int x = L.top(); L.pop();
                cur += time[x][0];
                qr.push({cur + time[x][1], x});
                rest--;
            } else {
            // 否则，此时没有人需要过桥，时间应该过渡到第一个处于「放下」或者「搬起」状态的工人切换状态的时刻。
                int x = 1e9;
                if (qr.size()) x = min(x, qr.top().first);
                if (ql.size()) x = min(x, ql.top().first);
                if (x != 1e9) cur = max(cur, x);
            }
        }
        return cur;
    }
};

