// 维护最大区间交集

typedef pair<int, int> pii;
class MyCalendarThree {
    set<int> a;
    unordered_map<int, int> vis;
public:
    MyCalendarThree() {
    }
    
    // 在线的算法
    int book(int startTime, int endTime) {
        // 最多调用 400 次
        // 扫描
        if (!vis.count(startTime)) a.insert(startTime);
        if (!vis.count(endTime)) a.insert(endTime);
        ++vis[startTime];
        --vis[endTime];
        int k = 0, ans = 0;
        for (auto it = a.begin(); it != a.end(); ++it) {
            k += vis[*it];
            ans = max(ans, k);
        }
        return ans;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */