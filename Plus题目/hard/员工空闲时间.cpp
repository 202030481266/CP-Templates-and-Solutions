/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        int n = schedule.size();
        vector<pair<int, int>> arr;

        for (auto& p : schedule) {
            for (Interval& x : p) {
                int st = x.start, ed = x.end;
                arr.emplace_back(st, 1);
                arr.emplace_back(ed, -1);
            }
        }

        sort(arr.begin(), arr.end());

        int last = -1, cur = 0;
        vector<Interval> ans;
        for (pair<int, int>& p : arr) {
            cur += p.second;
            if (cur == 0) {
                if (last == -1) last = p.first;
            }
            else {
                // cur > 0
                if (last != -1) {
                    if (p.first > last)
                        ans.push_back(Interval(last, p.first));
                    last = -1;
                }
            }
        }
        return ans;
    }
};