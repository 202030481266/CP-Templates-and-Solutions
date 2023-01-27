// 哈希表+双向链表来构键，关键的思路在于桶的设计
class AllOne {
public:
    list<pair<unordered_set<string>,int>> bucks;
    unordered_map<string, list<pair<unordered_set<string>,int>>::iterator> key_map;
    AllOne() {}
    
    void inc(string key) {
        if (!key_map.count(key)) {
            auto cur = bucks.begin();
            if (bucks.empty() || cur->second > 1) {
                // create a new buck
                unordered_set<string> s({key});
                key_map[key] = bucks.emplace(cur, s, 1);
            } else {
                // insert one element
                cur->first.emplace(key);
                key_map[key] = cur;
            }
        } else {
            // exist
            auto cur = key_map[key], nxt = next(cur);
            if (nxt == bucks.end() || nxt->second > cur->second + 1) {
                // create a new buck
                unordered_set<string> s({key});
                key_map[key] = bucks.emplace(nxt, s, cur->second + 1);
            } else {
                // insert one element
                nxt->first.emplace(key);
                key_map[key] = nxt;
            }
            cur->first.erase(key);
            if (cur->first.empty()) bucks.erase(cur);
        }
    }
    
    void dec(string key) {
        auto cur = key_map[key];
        if (cur->second > 1) {
            // should be move to another small buck
            auto pre = prev(cur);
            if (cur == bucks.begin() || pre->second < cur->second - 1) {
                // should create a new element
                unordered_set<string> s({key});
                key_map[key] = bucks.emplace(cur, s, cur->second - 1);
            } else {
                pre->first.emplace(key);
                key_map[key] = pre;
            }
        } else {
            key_map.erase(key);
        }
        cur->first.erase(key);
        if (cur->first.empty()) bucks.erase(cur);
    }
    
    string getMaxKey() {
        return bucks.empty() ? "" : *bucks.rbegin()->first.begin();
    }
    
    string getMinKey() {
        return bucks.empty() ? "" : *bucks.begin()->first.begin();
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */