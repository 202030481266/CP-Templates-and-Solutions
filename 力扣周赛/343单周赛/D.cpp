class Solution {
public:
    string smallestBeautifulString(string s, int k) {
        // 暴力枚举，然后检查是否形成了长度为2或者3的回文串（只需要检查左边）
        // 因为s本身就是美丽字符串，所有回文串只会有可能在更新的字符周围
        int n = s.size(), pos = -1;
        for (int i = n - 1; i >= 0; --i) {
            int tmp = s[i] - 'a';
            for (int j = tmp + 1; j < k; ++j) {
                // 检查新字符是否会造成长度为2的回文串
                if (i - 1 >= 0 && s[i - 1] - 'a' == j) continue; 
                // 检查新字符是否会造成长度为3的回文串
                if (i - 2 >= 0 && s[i - 2] - 'a' == j) continue;
                // 构造解
                s[i] = (char)(j + 'a');
                pos = i;
                break;
            }
            if (pos != -1) break;
        }
        // 找到第一个改变的位置后就可以往后构造没有回文串的最小解
        if (pos == -1) return ""; // 无解
        // 还可以变小
        for (int i = pos + 1; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                // 检查新字符是否会造成长度为2的回文串
                if (i - 1 >= 0 && s[i - 1] - 'a' == j) continue;
                // 检查新字符是否会造成长度为3的回文串
                if (i - 2 >= 0 && s[i - 2] - 'a' == j) continue;
                s[i] = (char)(j + 'a');
                break;
            }
        }
        return s;
    }
};