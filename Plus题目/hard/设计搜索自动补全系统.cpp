// 前缀匹配 + 热度排行 + 在线算法
// 离线算法
struct cmp {
    bool operator()(const pair<int, string>& lhs,
                    const pair<int, string>& rhs) const {
        if (lhs.first != rhs.first)
            return lhs.first > rhs.first;
        else
            return lhs.second < rhs.second;
    }
};
struct Node {
    unordered_map<char, Node*> mp;
    set<pair<int, string>, cmp> content;
};
class AutocompleteSystem {
public:
    Node *root, *current;
    string input_string;
    unordered_map<string, int> cnt;
    bool flag = true;

    void add(string& s, int weight) {
        Node* cur = root;
        for (char& c : s) {
            if (!cur->mp.count(c)) {
                cur->mp[c] = new Node();
            }
            cur = cur->mp[c];
            cur->content.emplace(weight, s);
        }
    }
    void update(string& s, int weight, int change) {
        Node* cur = root;
        for (char& c : s) {
            cur = cur->mp[c];
            auto it = cur->content.find(make_pair(weight, s));
            cur->content.erase(it);
            cur->content.emplace(weight + change, s);
        }
    }
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new Node();
        current = root;
        for (int i = 0; i < sentences.size(); ++i) {
            add(sentences[i], times[i]);
            cnt[sentences[i]] = times[i];
        }
    }

    vector<string> input(char c) {
        if (c == '#') {
            if (cnt.count(input_string))
                update(input_string, cnt[input_string], 1);
            else
                add(input_string, 1);
            cnt[input_string] += 1;
            input_string = "";
            current = root;
            flag = true;
            return {};
        }
        input_string.push_back(c);
        if (!flag) return {};
        if (!current->mp.count(c)) {
            flag = false;
            return {};
        }
        // find the match strings
        current = current->mp[c];

        // cout << input_string << endl;
        // for (pair<int, string> v : current->content) {
        //     cout << v.first << ' ' << v.second << endl;
        // }

        vector<string> res;
        int i = 0;
        for (auto it = current->content.begin();
             it != current->content.end() && i < 3; ++i, ++it)
            res.push_back(it->second);
        return res;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */