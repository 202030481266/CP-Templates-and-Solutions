// https://leetcode.cn/problems/video-stitching/description/
// 贪心：经典的区间覆盖问题



class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
    	int n = clips.size();
    	vector<int> r(200);

    	for (int i = 0; i < n; ++i) 
    		r[clips[i][0]] = max(clips[i][1], r[clips[i][0]]);

    	int cur = 0, mr = 0, ans = 0;
    	for (int i = 0; i <= time; ++i) {
    		mr = max(mr, r[i]);
    		if (i == cur) {
    			// already can be here
                if (i == time) return ans;
                // no more run
                if (mr == i) return -1;
                // run 
                ++ans;
    			cur = mr;
    		}
    	}
    	return ans;
    }
};