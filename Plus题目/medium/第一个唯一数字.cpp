#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class FirstUnique {
public:
    unordered_map<int, int> cnt;
    int p = 0;
    vector<int> q;
    FirstUnique(vector<int>& nums) {
        q = nums;
        for (int& v : q) cnt[v]++;
    }
    
    int showFirstUnique() {
        while (p < q.size() && cnt[q[p]] > 1) p++;
        return (p < q.size() ? q[p] : -1);
    }
    
    void add(int value) {
        q.push_back(value);
        cnt[value]++;
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */