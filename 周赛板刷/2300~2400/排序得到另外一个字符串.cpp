// https://leetcode.cn/problems/check-if-string-is-transformable-with-substring-sort-operations/



#define lowbit(x) ((x)&(-x))
class Solution {
	int cnt1[10], cnt2[10];
public:
    bool isTransformable(string s, string t) {
    	if (s.size() != t.size()) return false;
    	int n = s.size(); 
    	vector<int> pos[10];
    	vector<int> to(10, 0);
    	for (int i = 0; i < n; ++i) {
    		int tmp = s[i] - '0', tmp1 = t[i] - '0'; 
    		++cnt1[tmp];
    		++cnt2[tmp1];
    		pos[tmp].emplace_back(i + 1);
    	}
    	for (int i = 0; i < 10; ++i) if (cnt1[i] != cnt2[i]) return false;
    	// fenwick tree
    	int tr[n + 10], a[n + 10];
    	memset(tr, 0x3f, sizeof(tr));
    	memset(a, 0x3f, sizeof(a));
    	auto update = [&](int idx, int val) {
    		a[idx] = val;
    		while (idx <= n) {
    			tr[idx] = val;
    			int low = lowbit(idx);
    			for (int i = 1; i < low; i <<= 1) tr[idx] = min(tr[idx], tr[idx - i]);
    			idx += lowbit(idx);
    		}
    	};
    	auto query = [&](int x, int y) { // 区间查询
    		int ans = 0x3f3f3f3f;
    		while (y >= x) {
    			ans = min(ans, a[y]);
    			for (--y; y - lowbit(y) >= x; y -= lowbit(y))
    				ans = min(ans, tr[y]);
    		}
    		return ans;
    	};
    	for (int i = 0; i < n; ++i) update(i + 1, s[i] - '0');
    	for (int i = 0; i < n; ++i) {
    		int tmp = t[i] - '0', p = pos[tmp][to[tmp]++];
    		if (query(1, p) != tmp) return false;
    		update(p, 0x3f3f3f3f);  // 已经使用了
    	}
    	return true;
    }
};