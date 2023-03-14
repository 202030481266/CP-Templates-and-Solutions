class Solution {
public:
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int>& energy, vector<int>& experience) {
        int sum = accumulate(energy.begin(), energy.end(), 0);
        int a = experience[0], cur = experience[0];
        for (int i = 1; i < experience.size(); ++i) {
            a = max(a, experience[i] - cur);
            cur += experience[i];
        }
        int t1 = (sum + 1 > initialEnergy ? sum + 1 - initialEnergy : 0);
        int t2 = (a + 1 > initialExperience ? a + 1 - initialExperience : 0);
        return t1 + t2;
    }
};