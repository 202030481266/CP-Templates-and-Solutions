class Solution {
public:
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        // 判断是否是垂直的线段
        bool v1 = start1[0] == end1[0], v2 = start2[0] == end2[0];

        if (v1 && v2) {
            if (start1[0] != start2[0]) return {};
            int mn1 = min(start1[1], end1[1]), mx1 = max(start1[1], end1[1]); 
            int mn2 = min(start2[1], end2[1]), mx2 = max(start2[1], end2[1]); 
            int left = max(mn1, mn2), right = min(mx1, mx2);
            if (right < left) return {};
            else return {(double)start1[0], (double)left};
        } 
        else if (v1) {
            // v1是垂直的线段
            int mn = min(start2[0], end2[0]), mx = max(start2[0], end2[0]);
            if (mn <= start1[0] && mx >= start1[0]) {
                double k = (double)(end2[1] - start2[1]) / (end2[0] - start2[0]);
                double y = k * (start1[0] - start2[0]) + start2[1];
                mn = min(start1[1], end1[1]), mx = max(start1[1], end1[1]);
                if (y >= mn && y <= mx) 
                    return {(double)start1[0], (double)y};
            }
            return {};
        }
        else if (v2) {
            // v2是垂直的线段
            int mn = min(start1[0], end1[0]), mx = max(start1[0], end1[0]);
            if (mn <= start2[0] && mx >= start2[0]) {
                double k = (double)(end1[1] - start1[1]) / (end1[0] - start1[0]);
                double y = k * (start2[0] - start1[0]) + start1[1];
                mn = min(start2[1], end2[1]), mx = max(start2[1], end2[1]);
                if (y >= mn && y <= mx) 
                    return {(double)start2[0], (double)y};
            }
            return {};
        }
        else {
            double k1 = (double)(end1[1] - start1[1]) / (end1[0] - start1[0]);
            double k2 = (double)(end2[1] - start2[1]) / (end2[0] - start2[0]);
            int mn1 = min(start1[0], end1[0]), mx1 = max(start1[0], end1[0]);
            int mn2 = min(start2[0], end2[0]), mx2 = max(start2[0], end2[0]);
            int left = max(mn1, mn2), right = min(mx1, mx2);
            if (left > right) return {};
            if (k1 == k2) {
                // 共线
                if ((start1[1] - start2[1]) * (start2[0] - end2[0]) == (start2[1] - end2[1]) * (start1[0] - start2[0])) {
                    if (left == mn1) {
                        if (left == start1[0]) return {(double)start1[0], (double)start1[0]};
                        else return {(double)end1[0], (double)end1[1]};
                    }
                    else {
                        if (left == start2[0]) return {(double)start2[0], (double)start2[1]};
                        return {(double)end2[0], (double)end2[1]};
                    } 
                }
                return {};
            }
            // 斜率不相同
            double x = (k1 * start1[0] - k2 * start2[0] + start2[1] - start1[1]) / (k1 - k2);
            if (x >= left && x <= right)
                return {x, k1 * (x - start1[0]) + start1[1]};
        }
        return {};
    }
};