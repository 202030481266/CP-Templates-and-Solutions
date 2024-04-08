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

    Node(int _val, vector<Node*> _children)a {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    unordered_map<int, int> father;
    unordered_map<int, Node*> tree;

    void dfs1(Node* root, int fa) {
        tree[root->val] = root;
        father[root->val] = fa;
        for (Node* c : root->children) 
            dfs1(c, root->val);
    }

    bool check(Node* son, Node* fa) {
        Node* cur = tree[father[son->val]];
        while (cur->val != father[cur->val]) { // 只有根节点才有等于自己
            if (cur->val == fa->val) return true;
            cur = tree[father[cur->val]];
        }
        return cur->val == fa->val;
    } 

    void erase_son(Node* fx, Node* x) {
        for (int i = 0; i < fx->children.size(); ++i) {
            if (fx->children[i]->val == x->val) {
                fx->children.erase(fx->children.begin() + i);
                break;
            }
        }
    }

    void subtitue_son(Node* fx, Node* x, Node* y) {
        for (int i = 0; i < fx->children.size(); ++i) {
            if (fx->children[i]->val == x->val) {
                fx->children[i] = y;
                break;
            }
        }
    }

    bool find_son(Node* fx, Node* x) {
        for (int i = 0; i < fx->children.size(); ++i) {
            if (fx->children[i]->val == x->val) {
                return true;
            }
        }
        return false;
    }

    Node* moveSubTree(Node* root, Node* p, Node* q) {
        dfs1(root, root->val);
        if (check(q, p)) {
            if (p->val == root->val) {
                erase_son(tree[father[q->val]], q);
                q->children.push_back(p);
                subtitue_son(tree[father[p->val]], p, q);
                return q;
            }
            else {
                erase_son(tree[father[q->val]], q);
                q->children.push_back(p);
                subtitue_son(tree[father[p->val]], p, q);
            }
        }
        else {
            if (!find_son(q, p)) {
                erase_son(tree[father[p->val]], p);
                q->children.push_back(p);
            }
        }
        return root;
    }
};