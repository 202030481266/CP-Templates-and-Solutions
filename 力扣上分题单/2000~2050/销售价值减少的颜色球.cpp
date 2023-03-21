// https://leetcode.cn/problems/sell-diminishing-valued-colored-balls/



class Solution {
public:

	static constexpr int mod = 1e9 + 7;

	int maxProfit(vector<int>& inventory, int orders) {
		// reverse order
		sort(inventory.begin(), inventory.end(), greater<int>());
		int n = inventory.size();
		long long sum = 0, res = 0, ans = 0;
		for (auto c : inventory) {
			sum += 1ll * c;
			res = (res + (1ll + c * 1ll) * c / 2ll) % mod;
		}

		if (sum <= orders) return res;

		inventory.emplace_back(0);

		for (int i = 0; ; ++i) {
			long long j = i + 1, v = inventory[i];
			long long need = 1ll * j * (v - inventory[j]);
			// 1 + v
			ans = (ans + (1ll + v) * v / 2) % mod;
			if (need < orders) {
				orders -= need;
				continue;
			}
			v -= orders / j;
			ans = (ans - (orders % j) * ((v * (v - 1) / 2) % mod) - (j - orders % j) * (((v + 1) * v / 2) % mod)) % mod;
			break;
		}
		return (ans % mod + mod) % mod;
	}
};