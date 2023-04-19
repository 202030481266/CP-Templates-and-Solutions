// https://leetcode.cn/problems/second-minimum-time-to-reach-destination/
// 可变的次短路问题（本质就是动态规划）


class Solution {
public:
	typedef pair<int, int> pii;
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
    	// 所有的节点都是绿色开始，并且只有绿色的时候才能离开节点
    	// 求解的是严格第二小值， 节点 1 到节点 n 需要的 第二短时间，感觉就是次短路问题
    	// color[i] = ((cur / change) & 1 ? red : green)
    	vector<vector<int>> g(n);
    	vector<int> dis1(n, 0x3f3f3f3f), dis2(n, 0x3f3f3f3f);
    	dis1[0] = 0;
    	for (auto &e : edges) {
    		--e[0], --e[1];
    		g[e[0]].emplace_back(e[1]);
    		g[e[1]].emplace_back(e[0]);
    	}
    	priority_queue<pii, vector<pii>, greater<pii>> q; 
    	q.emplace(0, 0);
    	while (!q.empty()) {
    		auto [d, u] = q.top();
    		q.pop();
    		if (dis2[u] < d) continue;
    		// d是到达u的时间
    		for (int v : g[u]) {
    			int dis;
				// 到达u的时候是绿灯
				if ((d / change) % 2 == 0) dis = d + time;
				// 到达u的时候是红灯
				else dis = d + time + change - (d % change);
				if (dis1[v] > dis) {
					swap(dis1[v], dis);
					q.emplace(dis1[v], v);
				}
				if (dis2[v] > dis && dis1[v] < dis) {
					dis2[v] = dis;
					q.emplace(dis2[v], v);
				}
    		}
    	}
    	return dis2[n - 1];
    }
};