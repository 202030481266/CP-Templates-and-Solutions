// https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/ 
// 先排序，然后双指针贪心匹配

class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), [](string& a, string& b)
        {
            if(a.length() == b.length()) return a < b;
            return a.length() > b.length();
        });
        int n = s.length();
        for(auto& ss : dictionary){
            int m = ss.length();
            if(m > n) continue;
            int i = 0, j = 0;
            while(i < n && j < m){
                if(s[i] == ss[j]) j++;
                i++;
                if(j == m) return ss;
            }
        }
        return "";
    }
};
