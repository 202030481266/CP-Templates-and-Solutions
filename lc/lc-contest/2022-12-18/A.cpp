class Solution {
public:
    int similarPairs(vector<string>& words) {
        int n = words.size();

        auto check = [&](string x, string y) {
            vector<int> a(30, 0);
            vector<int> b(30, 0);
            for (int i = 0; i < x.size(); i++) a[x[i] - 'a']++;
            for (int i = 0; i < y.size(); i++) b[y[i] - 'a']++;
            for (int i = 0; i < y.size(); i++) 
                if (!a[y[i] - 'a']) return false;
            for (int i = 0; i < x.size(); i++)
                if (!b[x[i] - 'a']) return false;
            return true;
        };
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (check(words[i], words[j])) ans++;
            }
        }
        return ans;
    }
};