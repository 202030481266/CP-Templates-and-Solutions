// https://leetcode.cn/problems/longest-uncommon-subsequence-ii/



// 暴力获取所有的子序列, O(5 * 10000)
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
    	int n = strs.size();
    	unordered_map<string, vector<int>> cnt;

    	for (int k = 0; k < n; ++k) {
    		string s = strs[k];
    		int sz = s.size();
    		for (int i = 0; i < (1 << sz); ++i) {
    			string temp;
    			for (int j = 0; j < sz; ++j) {
    				if ((i >> j) & 1)
    					temp += s[j];
    			}
    			cnt[temp].emplace_back(k);
    		}
    	}
    	int ans = 0;
    	for (auto [s, c] : cnt) {
    		if ((c.size() == 1) && (s.size() > ans))
    			ans = s.size();
    	}
    	return ans == 0 ? -1 : ans;
    }
};

// 规律，如果一个字符串拥有一个别的字符串没有的子序列，那么这个字符串一定可以称为符合条件的子序列
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        auto is_subseq = [](const string& s, const string& t) -> bool {
            int pt_s = 0, pt_t = 0;
            while (pt_s < s.size() && pt_t < t.size()) {
                if (s[pt_s] == t[pt_t]) {
                    ++pt_s;
                }
                ++pt_t;
            }
            return pt_s == s.size();
        };

        int n = strs.size();
        int ans = -1;
        for (int i = 0; i < n; ++i) {
            bool check = true;
            for (int j = 0; j < n; ++j) {
                if (i != j && is_subseq(strs[i], strs[j])) {
                    check = false;
                    break;
                }
            }
            if (check) {
                ans = max(ans, static_cast<int>(strs[i].size()));
            }
        }
        return ans;
    }
};

