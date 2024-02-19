class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = dist.size();
        auto check = [&](int speed) -> bool {
            double need = 0;
            for (int i = 0; i < n - 1; ++i) {
                need += ceil(1.0 * dist[i] / speed);
            }
            need += 1.0 * dist[n - 1] / speed;
            return need <= hour;
        };
        int l = 0, r = 1e7;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return check(r) ? r : -1;
    }
};