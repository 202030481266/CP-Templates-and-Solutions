class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int, vector<int>, less<int>> q;

        long long sum = 0;
        for (auto c : gifts) q.emplace(c), sum += c;

        for (int i = 1; i <= k; ++i) {
            int u = q.top();
            sum -= (u - sqrt(u));
            q.pop();
            q.emplace(sqrt(u));
        }
        return sum;
    }
};