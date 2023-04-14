// https://leetcode.cn/problems/escape-a-large-maze/



class Solution {
public:
	static constexpr int N = 1000000;
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
    	// blocked的长度只有200，是一个突破口，数据量非常小
    	// blocked想要横向封锁或者纵向封锁至少需要1e6个网格所以明显不可能是这种情况，如果想要封锁掉，那么情况肯定是至少封锁了其中一个源点
    	// 控制深度进行搜索：最多距离为200的点，否则无论如何都封锁不住
    	// 但是尽管这样搜索的图太过于稠密了，很容易就会被构造的数据卡住，根据数学规律就可以发现，n个障碍最多不能围住不超过(n*(n-1)/2)个非障碍的格子
    	// 限制了搜索深度和搜索的个数，那么bfs就可以跑的飞快！
    	int n = blocked.size();
    	unordered_map<long long, int> is_blocked;
    	// 记录状态的信息
    	for (auto &p : blocked) is_blocked[1ll * p[0] * N + p[1]] = 1;
    	// bfs搜索
    	int clock = 0, count = 0;
    	unordered_map<long long, int> time;
    	auto bfs = [&](long long x, long long y, long long xx, long long yy) -> bool {
    		vector<pair<long long, long long>> q;
    		q.emplace_back(x, y);
    		++clock, count = 1;
    		time[x * N + y] = clock;
    		for (int d = 0; d <= 200 && !q.empty() && count <= (n * (n - 1) / 2); ++d) {
    			vector<pair<long long, long long>> tmp;
    			for (int k = 0; k < q.size(); ++k) {
	    			for (int i = 0; i < 4; ++i) {
	    				if (q[k].first == xx && q[k].second == yy) return false;
	    				long long nx = q[k].first + dirs[i][0], ny = q[k].second + dirs[i][1];
	    				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
	    				else if (time[nx * N + ny] != clock && !is_blocked[nx * N + ny]) {
	    					time[nx * N + ny] = clock;
	    					++count;
	    					tmp.emplace_back(nx, ny);
	    				}
	    			}
	    		}
	    		q = move(tmp);
    		}
    		return q.empty();
    	};
    	return !(bfs(source[0], source[1], target[0], target[1]) || bfs(target[0], target[1], source[0], source[1]));
    }
};