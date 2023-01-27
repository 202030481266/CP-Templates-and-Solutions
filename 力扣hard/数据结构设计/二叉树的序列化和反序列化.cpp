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

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "null,";
        auto left = serialize(root->left);
        auto right = serialize(root->right);
        return to_string(root->val) + "," + left + right;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        auto strList = split(data, ',');
        return buildTree(strList);
    }
private:
    list<string> split(string& data, char c) {
        list<string> res;
        for (int i = -1, j = 0; j < data.length(); j++) {
            if (data[j] == c) {
                res.push_back(data.substr(++i, j - i));
                i = j;
            }
        }
        return res;
    }
    TreeNode* buildTree(list<string>& data) {
        string temp = data.front();
        data.pop_front();
        if (temp == "null") return nullptr;
        TreeNode* node = new TreeNode(stoi(temp));
        node->left = buildTree(data);
        node->right = buildTree(data);
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));