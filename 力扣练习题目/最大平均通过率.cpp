class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();

        priority_queue<pair<double, pair<int,int>>, vector<pair<double, pair<int,int>>>, less<pair<double, pair<int,int>>>> q;

        for (int i = 0; i < n; ++i) {
            double t = 1.0 * (classes[i][1] - classes[i][0]);
            double m = 1.0 * (classes[i][1] + 1) * classes[i][1];
            q.emplace(make_pair(t / m, make_pair(classes[i][0], classes[i][1])));
        }
        while (extraStudents) {
            auto cur = q.top();
            q.pop();
            --extraStudents;
            double t = 1.0 * (cur.second.second - cur.second.first);
            double m = 1.0 * (cur.second.second + 2) * (cur.second.second + 1);
            q.emplace(make_pair(t / m, make_pair(cur.second.first + 1, cur.second.second + 1)));
        }
        double ans = 0;
        while (!q.empty()) {
            auto cur = q.top();
            q.pop();
            ans += (1.0 * cur.second.first / cur.second.second);
        }
        cout<< ans << endl;
        return ans / n;
    }
};