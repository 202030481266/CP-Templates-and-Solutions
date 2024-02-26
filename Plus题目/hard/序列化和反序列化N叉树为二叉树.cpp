/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

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
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if (!root) return nullptr;
        TreeNode* cur = new TreeNode(root->val);
        if (root->children.size() > 0) {
            vector<TreeNode*> son;
            for (Node* child : root->children) {
                son.push_back(encode(child));
            }
            cur->left = son[0];
            for (int i = 0; i + 1 < son.size(); ++i) {
                son[i]->right = son[i + 1];
            }
        }
        return cur;
    }
	
    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if (!root) return nullptr;
        vector<Node*> child;
        if (root->left) {
            vector<TreeNode*> son;
            TreeNode* cur = root->left;
            while (cur) {
                son.push_back(cur);
                cur = cur->right;
            }
            for (TreeNode* u : son) {
                child.push_back(decode(u));
            }
        }
        return new Node(root->val, child);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));