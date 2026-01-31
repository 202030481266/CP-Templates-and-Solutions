#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;

// template <class ForwardIterator>
// void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last);
// [first, last) -> [first, ..., middle - 1, middle, ..., last - 1] -> [middle, last - 1, first, ..., middle - 1]
std::vector<int> cyclicShiftSTL(std::vector<int> nums, int k) {
    if (nums.empty()) return nums;
    int n = nums.size();
    k = k % n; 
    if (k < 0) k += n;
    std::rotate(nums.begin(), nums.begin() + k, nums.end());
    return nums;
}

class Solution {
public:
    vector<int> rotateElements(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> arr;
        for (int i = 0; i < n; ++i) {
            if (nums[i] >= 0) arr.push_back(nums[i]);
        }
        auto a = cyclicShiftSTL(arr, k);
        for (int i = 0, j = 0; i < n; ++i) {
            if (nums[i] < 0) continue;
            nums[i] = a[j++];
        }
        return nums;
    }
};
