#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class ExamTracker {
public:
    vector<int> times;
    vector<ll> sum;
    ExamTracker() {
        times.push_back(0);
        sum.push_back(0);
    }
    
    void record(int time, int score) {
        times.push_back(time);
        sum.push_back(sum.back() + score);
    }
    
    long long totalScore(int startTime, int endTime) {
        int ed = upper_bound(times.begin(), times.end(), endTime) - times.begin();
        int st = lower_bound(times.begin(), times.end(), startTime) - times.begin();
        return sum[ed - 1] - sum[st - 1];
    }
};

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */