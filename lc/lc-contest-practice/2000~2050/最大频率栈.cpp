// https://leetcode.cn/problems/maximum-frequency-stack/description/



class FreqStack {
public:
    set<tuple<int, int, int>> q;
    unordered_map<int, vector<int>> cnt;
    int time = 0;
    FreqStack() {
        q.clear();
        cnt.clear();
    }

    void push(int val) {
        if (cnt[val].size()) {
            // cerr << "pop" << val << ' ' << cnt[val].size() << ' ' << cnt[val].back() << endl;
            auto it = q.find(tuple<int, int, int>{cnt[val].size(), cnt[val].back(), val});
            assert(it != q.end());
            q.erase(it);
        }
        cnt[val].emplace_back(++time);
        q.emplace(cnt[val].size(), time, val);
        // cerr << "push" << val << ' ' << cnt[val].size() << ' ' << time << endl;
    }

    int pop() {
        auto [fre, last, val] = *q.rbegin();
        // cerr << "pop" << val << ' ' << fre << ' ' << last << endl;
        q.erase(prev(q.end()));
        cnt[val].pop_back();
        if (cnt[val].size()) {
            // cerr << "push" << val << ' ' << cnt[val].size() << ' ' << cnt[val].back() << endl;
            q.emplace(cnt[val].size(), cnt[val].back(), val);
        }
        return val;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */