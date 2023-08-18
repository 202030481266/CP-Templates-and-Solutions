// https://leetcode.cn/problems/image-overlap/
// 反向操作，记录偏移量能够带来的贡献，非常牛逼！


class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        int diff[2*n+1][2*n+1];
        memset(diff, 0, sizeof(diff));

        // 遍历图片每个位置去找多少偏移后和它一样
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (img1[i][j] == 1)
                {
                    for (int l = 0; l < n; ++l)
                    {
                        for (int m = 0; m < n; ++m)
                        {
                            if (img2[l][m] == 1)
                            {
                                // 偏移位置，这里要+n保证其大于等于0
                                diff[i-l+n][j-m+n] += 1;
                            }
                        }
                    }
                }
            }
        }
        
        // 找出最大偏移量，就是结果
        int res = 0;
        for (int i = 0; i < 2*n+1; ++i)
        {
            for (int j = 0; j < 2*n+1; ++j)
            {
                res = max(res, diff[i][j]);
            }
        }

        return res;
    }
};

