/* 
	1、0~n-1个点，每个点最多有一条出边，构成了一棵基本的内向基环树。
	2、内向基环树由于最多只有n条边，所以图中的每一个连通块最多只会出现一个有向环。（可以优化求解单源最短路）
	3、基环树具有树的大部分性质+环的性质，所以可以从树以及环的角度分类思考这类问题
	4、通用的基环树处理技巧：
		- 可以通过拓扑排序一次性减掉所有的树枝，剩下的都是基环
		- 遍历基环，拓扑排序之后选择入度为1的点搜索即可
		- 遍历树枝，环与树枝的交接点出发，反向搜索树枝，搜索入度为0的点，从而转换为一个树形问题
*/



// 题目模板1：https://leetcode.cn/problems/find-closest-node-to-given-two-nodes/description/
// 使用基环树的特性可以快速求解单源的最短路
class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size(), min_dis = n, ans = -1;

        auto bfs = [&](int x) -> vector<int> {
        	vector<int> dis(n, n);
        	// 要么走进了环中然后结束要么走到了树枝的叶子上（长链）
        	for (int d = 0; x >= 0 && dis[x] == n; x = edges[x])
        		dis[x] = d++;
        	return dis;
        };
        auto d1 = bfs(node1), d2 = bfs(node2);
        for (int i = 0; i < n; ++i) {
        	int d = max(d1[i], d2[i]);
        	if (d < min_dis) min_dis = d, ans = i;
        }
        return ans;
    }
};

// 扩展思路：对于很多个节点的列表怎么办？ 考虑最简单的情况就是两个点
// 基于树的思想，一般的树，对于两个节点最近的就是LCA（最近公共祖先），所以对于基环树，可以分类讨论
// 两个点都在环里面的话，那么打就是 x->y 取y，否则答案就是LCA
// 同样的道理可以扩展到n个点，如果有点在环里面，那么可以二分答案，取走d步，对于每个点可以计算得到d步内得到的点集合，只要所有的交集不为空就可以判断d是对的
// 如果都在点都在树上的话，所以答案就还是LCA


// 题目模板2：https://leetcode.cn/problems/longest-cycle-in-a-graph/
// 基环树的最长环，利用基环树的特性那么得到对于一个连通块来说最多得到一个环，所以只需要不断dfs就可以了
// 在一次dfs中节点被访问过了有两种情况：一种是之前dfs的，一种是本次dfs的，那么后者表明可以得到一个环。使用全局的时间戳技巧就可以巧妙地区分。
class Solution {
public:
    int longestCycle(vector<int>& edges) {
    	int n = edges.size(), ans = -1;
    	vector<int> vis(n);

    	for (int i = 0, clock = 1; i < n; ++i) {
    		if (vis[i]) continue;
    		for (int x = i, start_time = clock; x >= 0; x = edges[x]) {
    			if (vis[x]) {
    				if (vis[x] >= start_time)
    					ans = max(ans, clock - vis[x]);
    				break;
    			}
    			else vis[x] = clock++;
    		}
    	}
    	return ans;
    }
};


// 题目模板3：https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/
// 考虑使用图依赖关系建模，那么对于一个点的关系等价于每一个点连接一个自己喜欢的点的边，然后就可以得到一棵基环树
// 骑士圆桌问题的改版，等价于基环树的环的长度问题，如果环的长度大于等于3，那么答案就是最大的环长度，如果等于2，就可以包括两个环上的点的最长链（并且可以包括多个，只要拼接就好了）
class Solution {
public:
    int maximumInvitations(vector<int>& g) {
    	int n = g.size();
    	int deg[n]; memset(deg, 0, sizeof(deg));

    	for (int v : g) ++deg[v];

    	int max_depth[n]; memset(max_depth, 0, sizeof(max_depth));
    	queue<int> q;
    	for (int i = 0; i < n; ++i) 
    		if (deg[i] == 0) q.emplace(i);
    	// 拓扑排序并且同时计算出最长链
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		++max_depth[u];
    		int v = g[u];
    		max_depth[v] = max(max_depth[u], max_depth[v]);
    		if (--deg[v] == 0) q.emplace(v);
    	}
    	int max_ring_size = 0, sum_chain_size = 0;
    	for (int i = 0; i < n; ++i) {
    		if (deg[i] == 0) continue;
    		deg[i] = 0;
    		int ring_size = 1;
    		// 遍历属于i的基环
    		for (int v = g[i]; v != i; v = g[v]) {
    			deg[v] = 0;
    			++ring_size;
    		}
    		if (ring_size == 2) 
    			sum_chain_size += max_depth[i] + max_depth[g[i]] + 2;
    		else max_ring_size = max(max_ring_size, ring_size);
    	}
    	return max(sum_chain_size, max_ring_size);
    }
};
// 遍历反图转换成树形问题
class Solution {
public:
    int maximumInvitations(vector<int> &g) { // favorite 就是内向基环森林 g
        int n = g.size();
        vector<vector<int>> rg(n); // g 的反图
        vector<int> deg(n); // g 上每个节点的入度
        for (int v = 0; v < n; ++v) {
            int w = g[v];
            rg[w].emplace_back(v);
            ++deg[w];
        }

        // 拓扑排序，剪掉 g 上的所有树枝
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (deg[i] == 0) {
                q.emplace(i);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            int w = g[v]; // v 只有一条出边
            if (--deg[w] == 0) {
                q.emplace(w);
            }
        }

        // 通过反图 rg 寻找树枝上最深的链
        function<int(int)> rdfs = [&](int v) -> int {
            int max_depth = 1;
            for (int w: rg[v]) {
                if (deg[w] == 0) { // 树枝上的点在拓扑排序后，入度均为 0
                    max_depth = max(max_depth, rdfs(w) + 1);
                }
            }
            return max_depth;
        };

        int max_ring_size = 0, sum_chain_size = 0;
        for (int i = 0; i < n; ++i) {
            if (deg[i] <= 0) {
                continue;
            }
            // 遍历基环上的点（拓扑排序后入度大于 0）
            deg[i] = -1;
            int ring_size = 1;
            for (int v = g[i]; v != i; v = g[v]) {
                deg[v] = -1; // 将基环上的点的入度标记为 -1，避免重复访问
                ++ring_size;
            }
            if (ring_size == 2) sum_chain_size += rdfs(i) + rdfs(g[i]); // 基环大小为 2，累加两条最长链的长度
            else max_ring_size = max(max_ring_size, ring_size); // 取所有基环的最大值
        }
        return max(max_ring_size, sum_chain_size);
    }
};


