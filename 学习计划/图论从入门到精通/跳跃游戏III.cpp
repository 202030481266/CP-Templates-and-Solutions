class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<int> vis(n, 0);
        vis[start] = 1;
        queue<int> q;
        q.push(start);
        while (!q.empty()) {
            int c = q.front();
            q.pop();
            if (arr[c] == 0) return true;
            if (c - arr[c] >= 0 && !vis[c - arr[c]]) {
                vis[c - arr[c]] = 1;
                q.push(c - arr[c]);
            }
            if (c + arr[c] < n && !vis[c + arr[c]]) {
                vis[c + arr[c]] = 1;
                q.push(c + arr[c]);
            }
        }
        return false;
    }
};