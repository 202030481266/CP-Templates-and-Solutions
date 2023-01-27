class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int n = skill.size();
        long long sum = accumulate(skill.begin(), skill.end(), 0);
        long long t = sum / (n / 2);
        long long ans = 0;
        if (n == 2) return skill[0] * skill[1];

        vector<int> cnt(1001);
        vector<int> vis(1001);
        for (auto c : skill) cnt[c]++;
        for (int i = 0; i < n; i++) {
            if (vis[skill[i]]) continue;
            if (t <= skill[i]) return -1;
            if (skill[i] == t - skill[i]) {
                if (cnt[skill[i]] & 1) return -1;
                ans += ((1ll * skill[i] * skill[i]) * (cnt[skill[i]] / 2));
            } else {
                if (cnt[skill[i]] != cnt[t - skill[i]]) return -1;
                ans += ((1ll * skill[i] * (t - skill[i])) * cnt[skill[i]]);
            }
            vis[skill[i]] = vis[t - skill[i]] = true;
        }
        return ans;
    }
};