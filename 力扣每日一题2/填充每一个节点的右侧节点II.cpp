/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return root;
        // bfs
        vector<Node*> q;
        q.push_back(root);
        root->next = NULL;
        while (!q.empty()) {
            vector<Node*> tmp;
            for (int i = 0; i < q.size(); ++i) {
                Node* u = q[i];
                if (u->left) tmp.push_back(u->left);
                if (u->right) tmp.push_back(u->right);
            }
            for (int i = 0; i < tmp.size(); ++i) {
                if (i + 1 < tmp.size()) tmp[i]->next = tmp[i + 1];
                else tmp[i]->next = NULL; 
            }
            q = move(tmp);
        }
        return root;
    }
};