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

class Solution {
public:
    Node* findRoot(vector<Node*> tree) {
        // 非常巧妙的一个点子：除了根节点，其他所有节点都会出现两次
        int sum = 0;
        for (auto& v : tree) {
            sum ^= v->val;
            for (auto& son : v->children)
                sum ^= son->val;
        }
        for (auto& v : tree)
            if (v->val == sum)
                return v;
        return nullptr;
    }
};