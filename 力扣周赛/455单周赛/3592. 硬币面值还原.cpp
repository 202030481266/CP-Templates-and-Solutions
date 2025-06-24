using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
	vector<int> findCoins(vector<int>& numWays) {
		int n = numWays.size();
		vector<int> ans;
		while (true) {
			int x = 0;
			for (int i = 1; i <= n; ++i) {
				if (numWays[i - 1]) {
					if (numWays[i - 1] > 1) return {};
                    x = i;
					break;
				}
			}
			if (!x) break;
			ans.push_back(x);
			for (int i = n; i >= x * 2; --i) {
                if (numWays[i - 1] < numWays[i - x - 1]) return {};
				numWays[i - 1] -= numWays[i - x - 1];
			}
			numWays[x - 1] = 0;
		}
		return ans;
	}
};