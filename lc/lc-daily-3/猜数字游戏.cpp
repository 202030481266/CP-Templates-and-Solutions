// 一眼USACO
class Solution {
public:
    string getHint(string secret, string guess) {
    	int bull = 0, cow = 0, n = secret.size();
    	vector<int> cnt1(10), cnt2(10);
    	for (int i = 0; i < n; ++i) {
    		if (secret[i] == guess[i]) {
    			++bull;
    		}
    		else {
    			++cnt1[secret[i] - '0'];
    			++cnt2[guess[i] - '0'];
    		}
    	}
    	for (int i = 0; i < 10; ++i) {
    		cow += min(cnt1[i], cnt2[i]);
    	}
    	return to_string(bull) + "A" + to_string(cow) + "B";
    }
};