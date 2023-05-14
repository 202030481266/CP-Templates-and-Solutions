class Solution {
    typedef pair<int, int> pii;
    int cnt[10010];
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        memset(cnt, 0, sizeof(cnt));
        int n = barcodes.size();
        priority_queue<pii> q;
        for (int c : barcodes) ++cnt[c];
        for (int c : barcodes) {
            if (cnt[c]) {
                q.emplace(cnt[c], c);
                cnt[c] = 0;
            }
        }
        vector<int> ans;
        while (!q.empty()) {
            auto [cx, x] = q.top();
            q.pop();
            if (q.empty()) {
                ans.emplace_back(x);
                break;
            }
            auto [cy, y] = q.top();
            q.pop();
            ans.emplace_back(x);
            ans.emplace_back(y);
            if (cx - 1 > 0) q.emplace(cx - 1, x);
            if (cy - 1 > 0) q.emplace(cy - 1, y);
        }
        return ans;
    }
};