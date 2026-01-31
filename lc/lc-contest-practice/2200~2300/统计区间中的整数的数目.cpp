// https://leetcode.cn/problems/count-integers-in-intervals/
// 区间合并问题，值域很大，不适合使用差分来合并，应该使用的是平衡树


class CountIntervals {
	typedef pair<int, int> pii;
public:
	int sum = 0; // 不会超过值域
	set<pii> s;
    CountIntervals() {}
    
    void add(int left, int right) {
    	for (auto it = s.lower_bound(pii{left, 0}); it != s.end() && it->second <= right; it = s.erase(it)) {
    		left = min(left, it->second);
    		right = max(right, it->first);
    		sum -= (it->first - it->second + 1);
    	}
    	sum += (right - left + 1);
    	s.emplace(right, left);
    }
    
    int count() {
    	return sum;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */