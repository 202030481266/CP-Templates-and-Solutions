// https://leetcode.cn/problems/dinner-plate-stacks/



class DinnerPlates {
public:
	vector<vector<int>> a;
	set<int> s[2];
	int cap, cur = 0;

    DinnerPlates(int capacity) {
		a.resize(200010);
    	cap = capacity;
    }
    
    void push(int val) {
    	if (s[0].empty()) s[0].emplace(cur++);
    	int i = *s[0].begin();
    	a[i].emplace_back(val);
    	if (a[i].size() == cap) s[0].erase(i);
    	// whatever should add to s[1]
    	s[1].emplace(i);
    }
    
    int pop() {
    	if (s[1].empty()) return -1;
    	int i = *s[1].rbegin();
    	int ans = a[i].back();
    	a[i].pop_back();
    	if (a[i].empty()) s[1].erase(i);  // empty
    	s[0].emplace(i); // add it to s[0]
		return ans;
    }
    
    int popAtStack(int index) {
    	auto it = s[1].lower_bound(index);
    	if (s[1].find(index) == s[1].end()) return -1;
    	else {
    		int res = a[index].back();
    		a[index].pop_back();
    		if (a[index].empty()) s[1].erase(index); // empty
    		s[0].emplace(index); // add it to s[0]
			return res;
    	}
    }
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */