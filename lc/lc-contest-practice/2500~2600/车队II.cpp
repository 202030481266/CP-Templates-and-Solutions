struct Node {
    double sp, dis, tim, rel;
    int id;
    bool operator < (const Node& rhs) const {
        if (rel <= 0) return true;
        else if (rhs.rel <= 0) return false;
        return tim + dis / rel > rhs.tim + rhs.dis / rhs.rel;
    }
};
class Solution {
    int fa[100010], n, left[100010], right[100010];
    Node events[100010];
    double cur;
    vector<double> ans;
    priority_queue<Node, vector<Node>> q;
public:
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void merge(int fx, int fy) {
        // fx -> fy
        int f;
        auto& ex = events[fx], ey = events[fy];
        if (ex.sp < ey.sp) {
            fa[fy] = fx;
            f = fx;
        }
        else {
            fa[fx] = fy;
            f = fy;
        }
        // update events
        auto& ef = events[f];
        ef.dis = ey.dis - (cur - ey.tim) * ey.rel;
        ef.sp = min(ex.sp, ey.sp);
        ef.tim = cur;
        left[f] = min(left[fx], left[fy]);
        right[f] = max(right[fx], right[fy]);
        if (right[f] + 1 <= n - 1) {
            int pre = find(right[f] + 1);
            ef.rel = ef.sp - events[pre].sp;
        }
        else ef.rel = 0;  // assume there car n is super fast
        if (left[f] > 0) {
            int pre = find(left[f] - 1);
            auto& ep = events[pre];
            ep.dis = ep.dis - (cur - ep.tim) * ep.rel;
            ep.tim = cur;
            ep.rel = ep.sp - ef.sp;
            q.emplace(ep);
        }
        q.emplace(ef);
    }
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        n = cars.size();
        iota(fa, fa + n, 0);
        iota(left, left + n, 0);
        iota(right, right + n, 0);
        // assume there nth cars is super fast 
        for (int i = 0; i < n; ++i) {
            auto& ei = events[i];
            if (i < n - 1) {
                ei.dis = cars[i + 1][0] - cars[i][0];
                ei.sp = cars[i][1];
                ei.tim = 0;
                ei.rel = cars[i][1] - cars[i + 1][1];
            }
            else {
                ei.dis = 1e10;
                ei.sp = cars[i][1];
                ei.tim = 0;
                ei.rel = 0;
            }
            ei.id = i;
        }
        for (int i = 0; i < n; ++i) q.emplace(events[i]);
        ans = vector<double>(n, -1);
        cur = 0;
        while (!q.empty()) {
            Node ev = q.top();
            q.pop();
            int fx = find(ev.id);
            auto& ex = events[fx];
            if (ex.rel <= 0 || ans[ev.id] != -1) continue;
            cur = ex.tim + ex.dis / ex.rel;
            // cout << ev.id << ' ' << cur << endl;
            merge(fx, find(right[fx] + 1));
            ans[ev.id] = cur;
        }
        return ans;
    }
};