// 实际上就是区间管理
// 在线算法还是挺有难度的
class RangeModule {
    set<int> s;
    unordered_map<int, int> h;
public:
    RangeModule() {
    }

    void add(int x, int y) {
        s.insert(x);
        s.insert(y);
        h[x] = 0;
        h[y] = 1;
    }

    void del(int x, int y) {
        for (auto it = s.lower_bound(x); it != s.end() && *it <= y; ) {
            if (*it == x && h[x] == 1 || *it == y && h[y] == 0) ++it;
            else {
                h.erase(*it);
                it = s.erase(it);
            } 
        }
    }
    
    void addRange(int left, int right) {
        // 在线的算法似乎只需要暴力合并即可？
        // 因为合并可以看作删除了之前添加的区间，那么无论怎么合并，删除的区间不会超过添加进去的区间，所以暴力操作即可

        // cout << "AddRange and the Range is [" << left << "," << right << "]" << endl;
        // cout << "previous set status is:" << endl;
        // for (int v : s) {
        //     if (h[v] == 0) cout << "[" << v << ",";
        //     else cout << v << "]" << ",";
        // }
        // cout << endl;

        int start, end;
        auto l = s.lower_bound(left), r = s.lower_bound(right);
        if (l == s.end() || h[*l] == 0) start = left; 
        else start = *prev(l);
        if (r == s.end()) end = right;
        else if (h[*r] == 1) end = max(*r, right);
        else {
            if (*r == right) end = *next(r);
            else end = right;
        }
        // [start, end)
        del(start, end);
        add(start, end);

        // cout << "operation over, now the set status is:" << endl;
        // for (int v : s) {
        //     if (h[v] == 0) cout << "[" << v << ",";
        //     else cout << v << "]" << ",";
        // }
        // cout << endl << endl;
    }
    
    bool queryRange(int left, int right) {

        // cout << "Query is [" << left << "," << right << "]" << endl;
        // for (int v : s) {
        //     if (h[v] == 0) cout << "[" << v << ",";
        //     else cout << v << "]" << ",";
        // }
        // cout << endl;

        auto l = s.lower_bound(left);
        if (l == s.end()) return false;
        // 如果是右端点 
        bool res;
        if (h[*l] == 1) res = (*prev(l) <= left && *l >= right);
        // 如果是左端点
        else res = (*l == left && *next(l) >= right);

        // cout << "The query result is " << (res ? "True" : "False") << endl << endl;
        
        return res;
    }
    
    void removeRange(int left, int right) {

        // cout << "remove range and the Range is [" << left << "," << right << "]" << endl;
        // cout << "previous set status is:" << endl;
        // for (int v : s) {
        //     if (h[v] == 0) cout << "[" << v << ",";
        //     else cout << v << "]" << ",";
        // }
        // cout << endl;

        vector<pair<int, int>> in;
        auto l = s.lower_bound(left), r = s.lower_bound(right);
        if (l != s.end() && h[*l] == 1 && *l > left) in.emplace_back(*prev(l), left);
        if (r != s.end() && h[*r] == 1 && *r > right) in.emplace_back(right, *r);
        del(left, right);
        for (auto [st, ed] : in) add(st, ed);

        // cout << "operation over, now the set status is:" << endl;
        // for (int v : s) {
        //     if (h[v] == 0) cout << "[" << v << ",";
        //     else cout << v << "]" << ",";
        // }
        // cout << endl << endl;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */