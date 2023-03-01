// https://leetcode.cn/problems/maximum-xor-with-an-element-from-array/
// 限制选择的01字典树

struct Trie {
    // 左子树指向表示 0 的子节点
    Trie* left = nullptr;
    // 右子树指向表示 1 的子节点
    Trie* right = nullptr;

    Trie() {}
};

class Solution {
private:
    // 字典树的根节点
    Trie* root = new Trie();
    // 最高位的二进制位编号为 30
    static constexpr int HIGH_BIT = 30;
public:
	void add(int num) {
        Trie* cur = root;
        for (int k = HIGH_BIT; k >= 0; --k) {
            int bit = (num >> k) & 1;
            if (bit == 0) {
                if (!cur->left) {
                    cur->left = new Trie();
                }
                cur = cur->left;
            }
            else {
                if (!cur->right) {
                    cur->right = new Trie();
                }
                cur = cur->right;
            }
        }
    }

    int check(int num) {
        Trie* cur = root;
        int x = 0;
        for (int k = HIGH_BIT; k >= 0; --k) {
            int bit = (num >> k) & 1;
            if (bit == 0) {
                // a_i 的第 k 个二进制位为 0，应当往表示 1 的子节点 right 走
                if (cur->right) {
                    cur = cur->right;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->left;
                    x = x * 2;
                }
            }
            else {
                // a_i 的第 k 个二进制位为 1，应当往表示 0 的子节点 left 走
                if (cur->left) {
                    cur = cur->left;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->right;
                    x = x * 2;
                }
            }
        }
        return x;
    }
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
    	int p = 0;
    	int n = nums.size();
    	int m = queries.size();
    	vector<vector<int>> q;
    	for (int i = 0; i < m; ++i) 
    		q.emplace_back(vector<int>{queries[i][0], queries[i][1], i});

    	sort(q.begin(), q.end(), [&](const vector<int>& a, const vector<int>& b){
    		return a[1] < b[1];
    	});
    	sort(nums.begin(), nums.end());

    	vector<int> ans(m);
    	for (int i = 0; i < m; ++i) {
    		while (p < n && nums[p] <= q[i][1]) add(nums[p++]);
    		if (!root->left && !root->right) {
    			ans[q[i][2]] = -1;
    		}
    		else ans[q[i][2]] = check(q[i][0]);
    	}
        return ans;
    }
};