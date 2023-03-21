// https://leetcode.cn/problems/stone-game-vi/



class Solution {
public:
	int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
		int n = aliceValues.size();
		priority_queue<pair<int, int>> q;

		// 从相对价值出发，一个石头具有相对价值
		for (int i = 0; i < n; ++i) {
			int sum = aliceValues[i] + bobValues[i];
			q.emplace(sum, i);
		}

		int alice = 0, bob = 0, flag = 1;
		while (!q.empty()) {
			auto [u, v] = q.top();
			q.pop();
			if (flag) alice += aliceValues[v];
			else bob += bobValues[v];
            flag ^= 1;
		}
		if (alice > bob) return 1;
		else if (alice == bob) return 0;
		else return -1;
	}
};