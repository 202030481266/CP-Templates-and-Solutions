// xiaoshulin


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
		vector<pair<TreeNode*, TreeNode*>> q;
		q.emplace_back(root, root);
		int c = 0;
		while (!q.empty()) {
			vector<pair<TreeNode*, TreeNode*>> tmp;
			for (auto [cur, f] : q) {
				if (cur->left) {
					tmp.emplace_back(cur->left, cur);
					tmp.emplace_back(cur->right, cur);
				}
			}
			if (c & 1) {
				int i = 0, j = q.size() - 1, flag = 0;
				while (i < j) {
					auto f1 = q[i].second;
					auto f2 = q[j].second;
					int x = q[i].first->left, y = q[i].first->right;
					q[i].first->left = q[j].first->left;
					q[i].first->right = q[j].first->right;
					q[j].first->left = x;
					q[j].first->right = y;
					if (!flag) {
						// [left, right]
						f1->left = q[j].first;
						f2->right = q[i].first;
					}
					else {
						// [right, left]
						f1->right = q[j].first;
						f2->left = q[i].first;
					}
					flag ^= 1;
					++i;
					--j;
				}
			}
			q = move(tmp);
			++c;
		}
		return root;
    }
};
