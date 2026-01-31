#include <bit>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        unsigned int n = nums.size();
        if (n <= 2) return n;
        int h = bit_width(n);
        return 1<<h;
    }
};