/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
    unordered_map<int, int> index;
public:
    void postorder(TreeNode* root, vector<int>& a) {
        if (!root) return;
        a.push_back(root->val);
        postorder(root->left, a);
        postorder(root->right, a);
    }
    void inorder(TreeNode* root, vector<int>& a) {
        if (!root) return;
        inorder(root->left, a);
        a.push_back(root->val);
        inorder(root->right, a);
    }
    vector<int> string2vector(string s) {
        vector<int> res;
        stringstream ss(s);
        string item;
        while (getline(ss, item, ',')) res.push_back(stoi(item));
        return res;
    }
    string vector2string(vector<int>& a) {
        string res;
        for (int i = 0; i < a.size(); ++i) {
            res += to_string(a[i]);
            if (i != a.size() - 1) res.push_back(',');
        }
        return res;
    }
    TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
        if (preorder_left > preorder_right) {
            return nullptr;
        }
        
        // 前序遍历中的第一个节点就是根节点
        int preorder_root = preorder_left;
        // 在中序遍历中定位根节点
        int inorder_root = index[preorder[preorder_root]];
        
        // 先把根节点建立出来
        TreeNode* root = new TreeNode(preorder[preorder_root]);
        // 得到左子树中的节点数目
        int size_left_subtree = inorder_root - inorder_left;
        // 递归地构造左子树，并连接到根节点
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
        // 递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i) {
            index[inorder[i]] = i;
        }
        return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "";
        vector<int> a, b;
        postorder(root, a);
        inorder(root, b);
        return vector2string(a) + "$" + vector2string(b);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0) return nullptr;
        int pos = 0, n = data.size();
        for (int i = 0; i < n; ++i) 
            if (data[i] == '$') {
                pos = i;
                break;
            }
        vector<int> pre = string2vector(data.substr(0, pos));
        vector<int> in = string2vector(data.substr(pos + 1, n - pos - 1));
        return buildTree(pre, in);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;