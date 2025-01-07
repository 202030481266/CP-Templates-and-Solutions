// xiaoshulin
// 2024.1.1

// 特殊的二分做法
const int T = 50;
const double inf = 1e9;

class Solution {
public:
    double minRecSize(vector<vector<int>>& lines) {
        int n = lines.size();
        if (n == 1)
            return 0.0;
        
        double rl = -inf, rr = inf;
        int t = T;
        sort(lines.begin(), lines.end(), [](vector<int> &a, vector<int> &b){
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]); 
        });
        while (t--) {
            double mid = (rl + rr) * 0.5;
            bool conflict = false;
            for (int i = 0; i < n - 1; ++i) {
                double a = (double)lines[i][0] * mid + lines[i][1];
                double b = (double)lines[i + 1][0] * mid + lines[i + 1][1];
                if (a - b > 1e-8) {
                    conflict = true;
                    break;
                }
            }
            if (conflict)
                rl = mid;
            else
                rr = mid;
        }
        
        t = T;
        double ll = -inf, lr = inf;
        sort(lines.begin(), lines.end(), [](vector<int> &a, vector<int> &b){
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]); 
        });
        while (t--) {
            double mid = (ll + lr) * 0.5;
            bool conflict = false;
            for (int i = 0; i < n - 1; ++i) {
                double a = (double)lines[i][0] * mid + lines[i][1];
                double b = (double)lines[i + 1][0] * mid + lines[i + 1][1];
                if (a - b > 1e-8) {
                    conflict = true;
                    break;
                }
            }
            if (conflict)
                lr = mid;
            else
                ll = mid;
        }
        
        t = T;
        double ul = -inf, ur = inf;
        sort(lines.begin(), lines.end(), [](vector<int> &a, vector<int> &b){
            return a[0] > b[0] || (a[0] == b[0] && a[1] > b[1]); 
        });
        while (t--) {
            double mid = (ul + ur) * 0.5;
            bool conflict = false;
            for (int i = 0; i < n - 1; ++i) {
                double a = (mid - lines[i][1]) / lines[i][0];
                double b = (mid - lines[i + 1][1]) / lines[i + 1][0];
                if (a - b > 1e-8) {
                    conflict = true;
                    break;
                }
            }
            if (conflict)
                ul = mid;
            else
                ur = mid;
        }
        
        t = T;
        double dl = -inf, dr = inf;
        sort(lines.begin(), lines.end(), [](vector<int> &a, vector<int> &b){
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]); 
        });
        while (t--) {
            double mid = (dl + dr) * 0.5;
            bool conflict = false;
            for (int i = 0; i < n - 1; ++i) {
                double a = (mid - lines[i][1]) / lines[i][0];
                double b = (mid - lines[i + 1][1]) / lines[i + 1][0];
                if (a - b > 1e-8) {
                    conflict = true;
                    break;
                }
            }
            if (conflict)
                dr = mid;
            else
                dl = mid;
        }
        
        if (ll - rr > 1e-8)
            return 0.0;
        
        return (rr - ll) * (ur - dl);
    }
};

// 贪心反证法
class Solution {
public:
    double minRecSize(vector<vector<int>>& f) {
        int n = f.size();
        vector<int> k(n, 0), b(n, 0);
        sort(f.begin(), f.end());
        for (int i = 0; i < n; i++) {
            k[i] = f[i][0]; b[i] = f[i][1];
        }
        int p = 0, q = 0;
        while (q < n && k[q] == k[p]) q++;
        if (q >= n) return 0.;
        double x_min = 1e100, x_max = -1e100;
        double y_min = 1e100, y_max = -1e100;
        for (; q < n;) {
            int r = q;
            while (r + 1 < n && k[r + 1] == k[q]) r++;
            // [p, q - 1], [q, r]
            double cx1 = 1.0 * (b[r] - b[p]) / (k[r] - k[p]);
            double cx2 = 1.0 * (b[q] - b[q - 1]) / (k[q] - k[q - 1]);
            x_min = min(x_min, min(cx1, cx2));
            x_max = max(x_max, max(cx1, cx2));
            double cy1 = 1.0 * (b[r] * k[p] - b[p] * k[r]) / (k[r] - k[p]);
            double cy2 = 1.0 * (b[q] * k[q - 1] - b[q - 1] * k[q]) / (k[q] - k[q - 1]);
            y_min = min(y_min, min(cy1, cy2));
            y_max = max(y_max, max(cy1, cy2));
            p = q;
            while (q < n && k[q] == k[p]) q++;
        }
        return (x_max - x_min) * (y_max - y_min);
    }
};


