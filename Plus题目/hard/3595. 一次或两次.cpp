#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
	vector<int> onceTwice(vector<int>& nums) {
		int n = nums.size();
		vector<int> cnt(32);
		for (int x : nums) {
			for (int i = 0; i < 32; ++i) {
				if ((x >> i) & 1) ++cnt[i];
			}
		}
		int val1 = 0, val2 = 0, mask = 0;
		for (int i = 0; i < 32; ++i) {
			cnt[i] %= 3;
			if (cnt[i] == 2) {
				val2 |= (1 << i);
				mask |= (1 << i);
			}
			if (cnt[i] == 1) {
				val1 |= (1 << i);
				mask |= (1 << i);
			}
		}
		int ones = 0, twos = 0; // 0, 1 (3*x+a)%3 = a%3
		for (int x : nums) {
			if ((x & mask) == val1) {
				int y = x & ~mask;
				twos |= ones & y;
				ones ^= y;
				int b = ones & twos;
				ones &= ~b;
				twos &= ~b;
			}
		}
		return { ones + val1, ones + val2 };
	}
};