class Solution {
public:
    vector<string> computeSimilarities(vector<vector<int>>& docs) {
        int n = docs.size();

        unordered_map<int, vector<int>> h;
        for (int i = 0; i < n; ++i) 
            for (int& v : docs[i]) h[v].push_back(i);

        vector<int> cnt(n * n);
        for (auto it = h.begin(); it != h.end(); ++it) {
            auto arr = it->second;
            for (int i = 0; i < arr.size(); ++i) 
                for (int j = i + 1; j < arr.size(); ++j)
                    ++cnt[arr[i] * n + arr[j]];
        }

        auto formatDouble = [&](int num, int den) -> string {
            double value = (double)num / den;
            value = round(value * 10000.0) / 10000.0;
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(4) << value;
            return stream.str();
        };

        vector<string> ans;
        for (int i = 0; i < n * n; ++i)
            if (cnt[i]) {
                int x = i / n, y = i % n; // x * n + y
                assert(x < y);
                string res = to_string(x) + "," + to_string(y) + ": " + formatDouble(cnt[i], docs[x].size() + docs[y].size() - cnt[i]);
                ans.push_back(res);
            }
        return ans;
    }
};