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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size();
        // cout<<"------------------"<<endl;
        // for (int& v : preorder) cout << v << ' ';cout<<endl;
        // for (int& v : postorder) cout << v << ' '; cout << endl;
        if (n == 0) return nullptr;
        // 前序遍历 根 左子树 右子树
        // 后序遍历 左子树 右子树 根
        TreeNode* root = new TreeNode(preorder[0]);
        if (n == 1) return root;
        int p1 = 0, p2 = -1;
        for (int i = n - 1; i > 0; --i) {
            if (preorder[i] == postorder[n - 2]) {
                p1 = i;
                break;
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            if (postorder[i] == preorder[1]) {
                p2 = i;
                break;
            }
        }
        if (p1 == 1) {
            root->left = nullptr;
            vector<int> pre_right(preorder.begin() + p1, preorder.end());
            vector<int> post_right(postorder.begin(), prev(postorder.end()));
            root->right = constructFromPrePost(pre_right, post_right);
        }
        else {
            vector<int> pre_left(preorder.begin() + 1, preorder.begin() + p1);
            vector<int> pre_right(preorder.begin() + p1, preorder.end());
            vector<int> post_left(postorder.begin(), postorder.begin() + p2 + 1);
            vector<int> post_right(postorder.begin() + p2 + 1, prev(postorder.end()));
            root->left = constructFromPrePost(pre_left, post_left);
            root->right = constructFromPrePost(pre_right, post_right);
        }
        return root;
    }
};