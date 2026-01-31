// https://leetcode.cn/problems/find-the-string-with-lcp/
// 贪心构造+验证 (利用了反动态规划的构造思想)
// 使用并查集来维护相等的字符的位置的集合


class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        
        /** 将原 lcp 数组增加一行一列 0，方便编码 */
        for(int i = 0; i < n; ++i) 
            lcp[i].push_back(0);
        lcp.push_back(vector<int>(n + 1, 0));
        
        /** 并查集模板代码 **/
        int fa[n];
        memset(fa, -1, sizeof(fa));
        function<int(int)> find = [&](int x) -> int {
            if(fa[x] == -1) return x;
            return fa[x] = find(fa[x]);
        };
        auto merge = [&](int x, int y) {
            x = find(x), y = find(y);
            if(x != y) fa[x] = y;
        };
        
        /* 根据 lcp 数组的性质，找出两个字符的相等或不等关系 */
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(lcp[i][j] == lcp[i + 1][j + 1] + 1) {
                    merge(i, j);
                } else if(lcp[i][j] != 0) {
                    // 不可能出现的情况
                    return "";
                }
            }
        }
        
        /* 分组 */
        vector<int> v[n];
        for(int i = 0; i < n; ++i)
            v[find(i)].push_back(i);
        
        /* 不能超过 26 个组，因为组间不相同，超过 26 个必打破 */
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            if(v[i].size()) cnt++;
        if(cnt > 26) return "";
        
        /* 按照下标出现的先后顺序排序，将 'a' 安排在最小的下标，'b' 次之...，以保证字典序最小 */
        sort(v, v + n);
        char cur = 'a';
        string res(n, 'a');
        for(int i = 0; i < n; ++i) {
            if(v[i].size()) {
                for(int j : v[i]) 
                    res[j] = cur;
                cur += 1;
            }
        }
        
        /* 得到字符串后，重新求一遍 lcp 数组，如果和原来的不一样代表无法构造 */
        vector<vector<int>> nlcp(n + 1, vector<int>(n + 1, 0));
        for(int i = n-1; i >= 0; --i) {
            for(int j = n-1; j >= 0; --j) {
                if(res[i] == res[j]) {
                    nlcp[i][j] = nlcp[i+1][j+1] + 1;
                } else {
                    nlcp[i][j] = 0;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(nlcp[i][j] != lcp[i][j]) return "";
            }
        }
        
        return res;
    }
};

