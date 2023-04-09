// https://leetcode.cn/problems/process-restricted-friend-requests/
// 卡并查集 + n^2
// 此题运用了2-SAT的思想，属于并查集的难题


class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
    	UnionFind un(n);
    	vector<unordered_set<int>> anti(n);

    	int m = requests.size(); 
    	vector<bool> ans;

    	for (auto r : restrictions) {
    		anti[r[0]].emplace(r[1]);
    		anti[r[1]].emplace(r[0]);
    	}
    	for (auto r : requests) {
    		int f1 = un.find(r[0]), f2 = un.find(r[1]);
    		// 只需要检查祖先节点，因为维护的关系决定了
    		if (anti[f1].count(f2) || anti[f2].count(f1)) 
    			ans.emplace_back(false);
    		else {
    			ans.emplace_back(true);
    			un.parent[f2] = f1;
    			for (int v : anti[f2]) {
    				// 这里是本题最关键的步骤，到时候加入的时候只需要检查祖先节点
    				anti[f1].emplace(v);
    				anti[v].erase(f2);
    				anti[v].emplace(f1);
    			}
    		}
    	}
    	return ans;
    }
};