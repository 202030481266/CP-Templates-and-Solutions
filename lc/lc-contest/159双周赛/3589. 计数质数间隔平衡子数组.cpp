using namespace std;
using ll = long long;

static constexpr int maxn = 5e4 + 7;
static constexpr int inf = 0x3f3f3f3f;
int primes[maxn], flag = 1;

void init(int n) {
	for (int i = 2; i <= n; ++i) primes[i] = 1;
	for (int i = 2; i * i <= n; ++i) {
		if (primes[i]) {
			for (int j = i * i; j <= n; j += i) {
				primes[j] = 0;
			}
		}
	}
}

class Solution {
public:
	int primeSubarray(vector<int>& nums, int k) {
		if (flag) {
			flag = 0;
			init(50000);
		}
		int n = nums.size();
		vector<int> mxq(n + 5, -inf), mnq(n + 5, inf);
		int st1 = 0, ed1 = 0;
		int st2 = 0, ed2 = 0;
		int l = 1, sp = 0, ans = 0, x = 0;
		for (int i = 1; i <= n; ++i) {
			if (primes[nums[i-1]]) {
				++sp;
				while (st1 < ed1 && nums[mxq[ed1 - 1]-1] <= nums[i-1]) ed1--;
				mxq[ed1++] = i;
				while (st2 < ed2 && nums[mnq[ed2 - 1]-1] >= nums[i-1]) ed2--;
				mnq[ed2++] = i;
			}
			while (st1 < ed1 && st2 < ed2 && nums[mxq[st1]-1] - nums[mnq[st2]-1] > k) {
				if (mxq[st1] < mnq[st2]) {
					x = mxq[st1];
					st1++;
				}
				else {
					x = mnq[st2];
					st2++;
				}
			}
			while (sp >= 2) {
				if (primes[nums[l - 1]]) --sp;
				++l;
			}
			if (l - x > 1) {
				ans += l - x - 1;
			}
		}
		return ans;
	}
};