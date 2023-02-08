// https://leetcode.cn/problems/largest-number/
// 经典的贪心构造问题，其实就是字符串拼接问题，让大的字符串优先排前面



class Solution {
public:
    string largestNumber(vector<int> &nums) {
        vector<string> a;

        for (auto c : nums) a.emplace_back(to_string(c));
        // 排序技巧
        sort(a.begin(), a.end(), [&](const string& x, const string& y){
        	return x + y > y + x;
        });
    	string ans; 
    	// 恶心的前导零
    	int pos = a.size();
    	for (int i = 0; i < a.size(); ++i)
    		if (stoi(a[i]) != 0) {
    			pos = i;
    			break;
    		}
    	for (int i = pos; i < a.size(); ++i) ans += a[i];
    	return ans.size() > 0 ? ans : "0";
    }
};
