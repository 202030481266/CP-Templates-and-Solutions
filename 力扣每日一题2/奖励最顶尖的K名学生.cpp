class Solution {
    unordered_map<string, int> positive; 
    unordered_map<string, int> negative;
public:
    int cal(const string& s, char delim) {
        stringstream ss(s);
        string item;
        int res = 0;
        while (getline(ss, item, delim)) {
            if (positive.count(item)) res += 3;
            else if (negative.count(item)) res -= 1;
        }
        return res;
    }
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {
        for (string& v : positive_feedback) positive[v] = 1;
        for (string& v : negative_feedback) negative[v] = 1;
        auto cmp = [](const pair<int, int> a, const pair<int, int>b) {
            return a.first == b.first ? a.second > b.second : a.first < b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q;
        int n = report.size();
        for (int i = 0; i < n; ++i) {
            int res = cal(report[i], ' ');
            q.emplace(res, student_id[i]);
        }
        vector<int> ans;
        while (k--) {
            auto u = q.top();
            q.pop();
            ans.emplace_back(u.second);
        }
        return ans;
    }
};