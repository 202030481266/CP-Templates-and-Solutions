class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        unordered_map<string,int> h;

        vector<string> ans;
        for (auto c : names) {
            if (h.count(c)) {
                int i = h[c];
                while (h.count(c + "(" + to_string(h[c]) + ")")) ++h[c];
                string temp = c + "(" + to_string(h[c]) + ")";
                ans.emplace_back(temp);
                ++h[temp];
                ++h[c];
            }
            else {
                ans.emplace_back(c);
                ++h[c];
            }
        }
        return ans;
    }   
};