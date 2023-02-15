// https://leetcode.cn/problems/find-the-closest-palindrome/
// 贪心构造

// 用原数的前半部分替换后半部分得到的回文整数。
// 用原数的前半部分加一后的结果替换后半部分得到的回文整数。
// 用原数的前半部分减一后的结果替换后半部分得到的回文整数。
// 为防止位数变化导致构造的回文整数错误，因此直接构造 999…9999 和 100…001 作为备选答案。


using ULL = unsigned long long;

class Solution {
public:
    vector<ULL> getCandidates(const string& n) {
        int len = n.length();
        vector<ULL> candidates = {
            (ULL)pow(10, len - 1) - 1,
            (ULL)pow(10, len) + 1,
        };
        ULL selfPrefix = stoull(n.substr(0, (len + 1) / 2));
        for (int i : {selfPrefix - 1, selfPrefix, selfPrefix + 1}) {
            string prefix = to_string(i);
            string candidate = prefix + string(prefix.rbegin() + (len & 1), prefix.rend());
            candidates.push_back(stoull(candidate));
        }
        return candidates;
    }

    string nearestPalindromic(string n) {
        ULL selfNumber = stoull(n), ans = -1;
        const vector<ULL>& candidates = getCandidates(n);
        for (auto& candidate : candidates) {
            if (candidate != selfNumber) {
                if (ans == -1 ||
                    llabs(candidate - selfNumber) < llabs(ans - selfNumber) ||
                    llabs(candidate - selfNumber) == llabs(ans - selfNumber) && candidate < ans) {
                    ans = candidate;
                }
            }
        }
        return to_string(ans);
    }
};

