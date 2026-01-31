class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        int l = -1, sum = 0;
        vector<string> ans;
        for (int i = 0; i < n; ++i) {
            if (l == -1) {
                l = i;
                sum += words[i].size();
            }
            else {
                if (sum + words[i].size() + 1 > maxWidth) {
                    // [l, i) concate
                    int num = i - l; 
                    sum -= num - 1; // 减去之前加上的一个空格
                    string res;
                    if (num > 1) {
                        int space = (maxWidth - sum) / (num - 1), rem = (maxWidth - sum) % (num - 1);
                        for (int j = l; j < i; ++j) {
                            res = res + words[j];
                            if (j < i - 1) {
                                int times = space;
                                if (rem) ++times, --rem;
                                while (times--) res.push_back(' ');
                            }
                        }
                    }
                    else {
                        res = words[l];
                        int times = maxWidth - words[l].size();
                        while (times--) res.push_back(' ');
                    }
                    ans.push_back(res);
                    // change interval
                    sum = words[i].size();
                    l = i;
                }
                else sum += words[i].size() + 1;
            }
        }
        // [l, n)
        int num = n - l, times = maxWidth - sum; 
        string res;
        for (int i = l; i < n; ++i) {
            res = res + words[i];
            if (i < n - 1) res.push_back(' ');
        }
        while (times--) res.push_back(' ');
        ans.push_back(res);
        return ans;
    }
};