class TimeMap {
    unordered_map<string, int> idx;
    vector<vector<pair<int, string>>> group;
    int tot = 0;
public:
    TimeMap() {
        tot = 0;
    }
    
    void set(string key, string value, int timestamp) {
        if (!idx.count(key)) {
            idx[key] = tot++;
            group.push_back({});
        }
        group[idx[key]].emplace_back(timestamp, value);
    }
    
    string get(string key, int timestamp) {
        if (!idx.count(key)) return "";
        int id = idx[key];
        int l = 0, r = group[id].size();
        // [l, r)
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (group[id][mid].first <= timestamp) l = mid;
            else r = mid;
        }
        if (group[id][l].first <= timestamp) return group[id][l].second;
        return "";
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */