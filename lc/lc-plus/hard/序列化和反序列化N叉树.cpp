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

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        // serialY=Y(y1(serialy1)y2(serialy2)...yn(serialyn))
        if (!root) return "";
        string hash;
        vector<string> chi;
        for (Node* child : root->children) {
            chi.push_back(serialize(child));
        }
        // sort(chi.begin(), chi.end()); ，使用最小表示会导致错误，调了非常久！
        for (string& s : chi) hash += s;
        return to_string(root->val) +  "(" + hash + ")";
    }
    
    // Decodes your encoded data to tree.
    Node* dfs(string& s, int& p) {
        if (s[p] == ')' || p >= s.size()) return nullptr;
        int x = 0;
        while (isdigit(s[p])) {
            x = x * 10 + (s[p] - '0');
            ++p;
        }
        vector<Node*> child;
        ++p;
        while (p < s.size() && s[p] != ')') {
            Node* c = dfs(s, p);
            if (c != nullptr)
                child.push_back(c);
            ++p;
        }
        return new Node(x, child);
    }

    Node* deserialize(string data) {
        int p = 0;
        Node* ans = dfs(data, p);
        return ans;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));