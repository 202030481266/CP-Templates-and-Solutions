// https://leetcode.cn/problems/verbal-arithmetic-puzzle/



// 直接确定数字会导致搜索深度过深，因此需要从后面开始搜索
class Solution {
	int h[30], use[10], exi[30];
public:
    bool isSolvable(vector<string>& words, string result) {
    	// 1 <= words[i].length, results.length <= 7
    	// 表达式中使用的不同字符数最大为 10，意思就是每一个不同的字符对应一个不同的数字
    	// 算法：爆搜
    	int n = words.size();
    	memset(h, -1, sizeof(h));
    	memset(use, 0, sizeof(use));
    	memset(exi, 0, sizeof(exi));
    	vector<int> a;
    	for (auto &c : words)
    		for (char ch : c) if (!exi[ch - 'A']) a.emplace_back(ch - 'A'), exi[ch - 'A'] = 1;
    	for (char ch : result) if (!exi[ch - 'A']) a.emplace_back(ch - 'A'), exi[ch - 'A'] = 1;
    	// 有些字符是不能为0
    	memset(exi, 0, sizeof(exi));
    	for (auto &c : words) 
    		if (c.size() > 1) exi[c[0] - 'A'] = 1;
    	if (result.size() > 1) exi[result[0] - 'A'] = 1;
    	// dfs
    	bool find = false;
    	function<void(int)> dfs = [&](int d) {
    		if (find) return;
    		if (d == a.size()) {
    			// 所有的字母都分配了数字
    			int sum = 0, tmp = 0, res = 0;
    			for (auto &c : words) {
    				tmp = 0;
    				for (int i = 0; i < c.size(); ++i) tmp = tmp * 10 + h[c[i] - 'A'];
    				sum += tmp;
    			}
    			for (int i = 0; i < result.size(); ++i) res = res * 10 + h[result[i] - 'A'];
    			if (sum == res) find = true;
    			return; // 无论怎样都要退回
    		}
    		for (int i = 0; i < 10; ++i) {
    			if (!use[i]) {
    				// 不能为前导零
    				if (exi[a[d]] && i == 0) continue;
    				h[a[d]] = i;
    				use[i] = 1;
    				dfs(d + 1);
    				use[i] = 0;
    				h[a[d]] = -1;
    			}
    		}
    	};
    	dfs(0);
    	return find;
    }
};


// 优化搜索
// 本题算法明显，但是实现非常困难！
class Solution {
private:
    bool notZeros[26];
    int char2num[26];
    int num2char[10];

    // 递归函数
    // words,result输入参数不修改
    // pos 表示单词遍历的位数，从最右边开始，一旦超过最大单词的长度则结束
    // wordIndex 当前遍历单词的序号
    // carry 表示之前位的进位,默认为0
    bool dfs(vector<string>& words, string& result, int pos, int wordIndex, int carry)
    {
        // 已经遍历完全部的，则必须进位为0
        if (pos == result.size())
        {
            return carry == 0;
        }

        if (wordIndex < words.size())
        {
            // 还在遍历每个单词中
            string& word = words[wordIndex];
            // 如果pos大于等于单词长度，则忽略，继续下一个单词
            if (pos >= word.size())
            {
                return dfs(words, result, pos, wordIndex+1, carry);
            }

            char c = word[word.size()-1-pos];
            // 如果有字符映射，则继续递归下一个单词
            if (char2num[c-'A'] != -1)
            {
                return dfs(words, result, pos, wordIndex+1, carry);
            }
            // 如果没有字符映射，则考虑可能的数值选择 0-9，
            // 这里需要排除字符不能为零，则从1开始，否则从0开始
            int start = notZeros[c-'A'] ? 1 : 0;
            for (int i = start; i < 10; ++i)
            {
                if (num2char[i] == -1)
                {
                    num2char[i] = c;
                    char2num[c-'A'] = i;
                    if (dfs(words, result, pos, wordIndex+1, carry))
                    {
                        return true;
                    }
                    // 失败则回溯
                    num2char[i] = -1;
                    char2num[c-'A'] = -1;
                }
            }
        }
        else
        {
            // 单词已经遍历完，开始计算, 然后继续下一位的pos
            int sum = carry;
            for (string& word : words)
            {
                if (word.size() > pos)
                {
                    sum += char2num[word[word.size() - 1 - pos] - 'A'];
                }
            }
            //  基于sum求和结果去得到是期望result对应的数值
            int exp = sum % 10;
            char c  = result[result.size()-1-pos];
            // 对于已经映射的情况，需要严格和exp一样，否则返回无效
            if (char2num[c-'A'] != -1)
            {
                if (char2num[c-'A'] != exp)
                {
                    return false;
                }
                // pos到一个位置，wordIndex从头开始
                return dfs(words, result, pos+1, 0, sum/10);
            }

            // 对于无映射的情况，则设置对应值后去判断，一旦无效则回溯
            if (num2char[exp] != -1)
            {
                // exp已被映射，无解
                return false;
            }
            char2num[c-'A'] = exp;
            num2char[exp] = c;
            // pos到一个位置，wordIndex从头开始
            if (dfs(words, result, pos+1, 0, sum/10))
            {
                return true;
            }

            // 无效则回溯
            num2char[exp] = -1;
            char2num[c-'A'] = -1;
            return false;
        }

        return false;
    }

public:
    bool isSolvable(vector<string>& words, string result) {
        // 初始化
        for (int i = 0; i < 26; ++i)
        {
            notZeros[i] = false;
            // 无效值
            char2num[i] = -1;
        }
        for (int i = 0; i < 10; ++i)
        {
            num2char[i] = -1;
        }

        // 设置 notZeros
        int maxWordSize = 1;
        for (string& word : words)
        {
            // 对于大于1的长度，第一个不能为0
            if (word.size() > 1)
            {
                notZeros[word[0]-'A'] = true;
            }
            maxWordSize = max(maxWordSize, (int)word.size());
        }
        if (result.size() > 1)
        {
            notZeros[result[0]-'A'] = true;
        }

        // 前置判断无效，直接返回false
        // - 单词长度超过result，无前置0，必然不满足
        // - 单词长度太短，小于result，进位了也不满足，必然不满足
        if (maxWordSize > result.size() || maxWordSize + 1 < result.size())
        {
            return false;
        }

        return dfs(words, result, 0, 0, 0);
    }
};

