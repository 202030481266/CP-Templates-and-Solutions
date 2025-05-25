int valid[26][26];
bool flag = true;
void init() {
	for (int i = 0; i < 26; ++i) {
		valid[i][(i + 1) % 26] = 1;
		valid[(i + 1) % 26][i] = 1;
		valid[i][(i + 25) % 26] = 1;
		valid[(i + 25) % 26][i] = 1;
	}
}

class Solution {
public:
    string resultingString(string s) {
		if (flag) {
			flag = false;
			init();
		}
        vector<int> st;
		int n = s.size();
		for (int i = 0; i < n; ++i) {
			int c = s[i] - 'a';
			if (!st.empty() && valid[st.back()][c]) {
				st.pop_back();
			}
			else st.push_back(c);
		}
		string ans;
		for (int v : st) ans.push_back('a' + v);
		return ans;
    }
};