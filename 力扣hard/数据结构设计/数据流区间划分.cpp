// 直接使用set来进行维护，但是这样的输出答案就要遍历set
// 好像也没什么更好的办法，毕竟vector这个东西删除效率没的说


class SummaryRanges {
private:
    static constexpr int N = 10010;
    set<pair<int,int>> intervals;
    bool vis[N];
public:
    SummaryRanges() {
        intervals.emplace(INT_MIN, INT_MIN);
        intervals.emplace(INT_MAX, INT_MAX);
        memset(vis, false, sizeof(vis));
    }

    void addNum(int value) {
        if (vis[value]) return;
        vis[value] = true;
        auto upper = intervals.lower_bound(make_pair(value, value)), lower = prev(upper);
        int left, right;
        if (value == lower->second + 1 && value == upper->first - 1) {
            left = lower->first, right = upper->second;
            intervals.erase(lower);
            intervals.erase(upper);
        } else if (value == lower->second + 1) {
            left = lower->first, right = value;
            intervals.erase(lower);
        } else if (value == upper->first - 1) {
            left = value, right = upper->second;
            intervals.erase(upper);
        } else {
            left = right = value;
        }
        intervals.emplace(left, right);
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> ans;
        for (auto it = next(intervals.begin()); it != prev(intervals.end()); ++it)
            ans.emplace_back(vector<int>{it->first, it->second});
        return ans;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */