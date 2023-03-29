// https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/



class Solution {
public:

	int cnt[400010];
	int dis[100010];

    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
    	int n = fruits.size();
    	memset(cnt, 0, sizeof(cnt));
    	for (int i = 0; i < n; ++i) {
    		dis[i] = fruits[i][0] + 1;
    		cnt[fruits[i][0] + 1] = fruits[i][1];
    	}
    	++startPos;
    	for (int i = 1; i <= startPos + k; ++i) {
    		cnt[i] += cnt[i - 1];
    	}
    	int pos = lower_bound(dis, dis + n, startPos) - dis;
  		int rr = cnt[startPos + k] - cnt[startPos - 1]; // [startPos, startPos + k]
  		int ll = cnt[startPos] - cnt[max(0, startPos - k - 1)]; // [startPos - k, startPos]
  		int ans = max(ll, rr);
  		if (pos == n || pos == 0) return ans;

  		int x = pos;
  		if (dis[pos] > startPos) --pos;

    	for (int i = pos; i >= 0; --i) {
    		if (dis[i] + k < startPos) break;
    		int l = dis[i], r = max(startPos, startPos + k - 2 * (startPos - dis[i]));
    		ans = max(ans, cnt[r] - cnt[l - 1]);
    	}
    	pos = x;
    	for (int i = x; i < n; ++i) {
    		if (dis[i] > startPos + k) break;
    		int r = dis[i], l = min(startPos, max(1, startPos - k + 2 * (dis[i] - startPos)));
    		ans = max(ans, cnt[r] - cnt[l - 1]);
    	}
    	return ans;
    }
};