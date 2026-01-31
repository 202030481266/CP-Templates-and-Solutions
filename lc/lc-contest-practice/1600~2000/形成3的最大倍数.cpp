class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int n = digits.size();
        string ans;
        int cnt[3], sum = 0, flag = 0;
        sort(digits.begin(), digits.end());
        for (int i = 0; i < 3; ++i) cnt[i] = 0;
        for (int i = 0; i < n; ++i) {
            ++cnt[digits[i] % 3];
            if (digits[i] % 3 == 0 && digits[i] != 0) flag = 1; 
            sum += digits[i];
        }
        int x = 0, y = 0;
        if (sum % 3 == 1) {
            if (cnt[1]) x = 1, cnt[1] -= 1;
            else y = 2, cnt[2] -= 2;
        }
        if (sum % 3 == 2) {
            if (cnt[2]) y = 1, cnt[2] -= 1;
            else x = 2, cnt[1] -= 2;
        }
        if (cnt[1] == 0 && cnt[2] == 0) {
            if (cnt[0]) {
                if (!flag) return "0";
            }
            else return "";
        }
        for (int i = 0; i < n; ++i) {
            int tmp = digits[i] % 3;
            if (tmp == 1) {
                if (x) --x;
                else ans.push_back(char(digits[i] + '0'));
            }
            else if (tmp == 2) {
                if (y) --y;
                else ans.push_back(char(digits[i] + '0'));
            }
            else ans.push_back(char(digits[i] + '0'));
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};