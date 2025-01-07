class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int k) {
        int n = stations.size();
        
        // 二分
        vector<double> dis(n - 1);
        for (int i = 0; i + 1 < n; ++i) {
            dis[i] = stations[i + 1] - stations[i];
        }

        auto check = [&](double d) -> bool {
            int c = k;
            for (double& v : dis) {
                int need = ceil(v / d) - 1;
                if (c < need) return false;
                c -= need;
            }
            return true;
        };

        double l = 0, r = *max_element(dis.begin(), dis.end()); // (l, r]

        for (int i = 0; i < 100; ++i) {
            double mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }
        
        return r;
    }
};