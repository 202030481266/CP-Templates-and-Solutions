#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
	string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, add = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = j >= 0 ? num2[j] - '0' : 0;
            int result = x + y + add;
            ans.push_back('0' + result % 10);
            add = result / 10;
            i -= 1;
            j -= 1;
        }
        // 计算完以后的答案需要翻转过来
        reverse(ans.begin(), ans.end());
        return ans;
    }

    long long findTheArrayConcVal(vector<int>& nums) {
		int n = nums.size();
		vector<string> a;
		for (auto c : nums) a.emplace_back(to_string(c));

		string ans = "0";
		int l = 0, r = n - 1;
		while (l <= r) {
			if (l == r) {
				ans = addStrings(ans, a[l]);
			} else {
				string temp = a[l] + a[r];
				ans = addStrings(ans, temp);
			}
			++l, --r;
		}
		return stoll(ans);
    }
};
