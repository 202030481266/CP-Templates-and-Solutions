class SnapshotArray {
    vector<vector<pair<int, int>>> arr;
    int cur;
public:
    SnapshotArray(int length) {
        arr.resize(length);
        for (int i = 0; i < length; ++i)
            arr[i].emplace_back(0, 0);
        cur = 0;
    }
    
    void set(int index, int val) {
        pair<int, int>& p = arr[index].back();
        if (cur == p.first) p.second = val;
        else arr[index].emplace_back(cur, val);
    }
    
    int snap() {
        return cur++;
    }
    
    int get(int index, int snap_id) {
        vector<pair<int, int>>& v = arr[index];
        int l = 0, r = v.size();
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (v[mid].first <= snap_id) l = mid;
            else r = mid;
        }
        return v[l].second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */