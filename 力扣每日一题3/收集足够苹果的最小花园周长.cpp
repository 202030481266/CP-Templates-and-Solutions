// xiaoshulin
// 2023.12.24
class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
		long long ans = -1, l = 1, r = 1e6;

		// sum(n ^ 2) = n * (n + 1) * (2 * n + 1) / 6
		// sum(n ^ 3) = (n ^ 2) * ((n + 1) ^ 2) / 4
		while (l <= r) {
			long long mid = (l + r) >> 1;
			long long tmp = 2 * (mid - 1) * mid * (2 * mid - 1);
			if (tmp >= neededApples) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		return (ans - 1) * 8; 
    }
};
