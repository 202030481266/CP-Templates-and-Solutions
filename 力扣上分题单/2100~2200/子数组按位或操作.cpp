// https://leetcode.cn/problems/bitwise-ors-of-subarrays/
// 固定右端点，观察到题目的或运算的性质是单调不减的所有左右有32个数字
// 但是题目非常不友好会超时


class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
    	int n = arr.size();
    	set<int> s;
		set<int> res;

    	for (int i = 0; i < n; ++i) {
    		s.emplace(arr[i]);
			set<int> f;
    		for (int v : s) {
    			f.emplace(v | arr[i]);
				res.emplace(v | arr[i]);
    		}
			s = move(f);
    	}
    	return res.size();
    }
};


// 下面这个版本可以过
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& a) {
        // ors 保留前面子数组的或运算的所有结果值
        unordered_set<int> res,ors;
        for(int x:a)
        {
            unordered_set<int> tmp;
            // 将 ors 中的各元素与当前元素进行或运算
            for(auto it=ors.begin();it!=ors.end();it++)
                tmp.insert((*it)|x);
            // 插入当前元素
            tmp.insert(x);
            ors=tmp;
            // 与原来保存所有或运算结果值的res做并集
            for(auto it=tmp.begin();it!=tmp.end();it++)
                res.insert(*it);
        }
        return res.size();
    }
};