#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;



class StatisticsTracker {
public:
    ll sum;
    int n;
    set<pii> s; 
    multiset<int> s1, s2;
    unordered_map<int,int> cnt;
    queue<int> q;
    StatisticsTracker() {
        n = 0;
        sum = 0;
    }
    
    void addNumber(int number) {
        sum+=number;
        n++;
        q.push(number);
        
        // big, n/2
        s1.insert(number);
        while (s1.size() > n/2) {
            auto it = prev(s1.end());
            s2.insert(*it);
            s1.erase(it);
        }
        while (!s1.empty() && *prev(s1.end()) > *s2.begin()) {
            auto it = prev(s1.end());
            int tmp = *it;
            s1.erase(it);
            s1.insert(*s2.begin());
            s2.erase(s2.begin());
            s2.insert(tmp);
        }

        // 维护出现次数
        if (!cnt.count(number)) {
            s.insert({1,-number});
            cnt[number]=1;
        }
        else {
            int c = cnt[number];
            s.erase({c,-number});
            s.insert({c+1, -number});
            cnt[number]++;
        }
    }
    
    void removeFirstAddedNumber() {
        int number = q.front();
        q.pop();
        sum -= number;
        n--;

        // big, n/2
        if (s1.find(number) != s1.end()) {
            auto it = s1.find(number);
            s1.erase(it);
            if (s2.size() >= s1.size() + 2) {
                s1.insert(*s2.begin());
                s2.erase(s2.begin());
            } 
        }
        else {
            auto it = s2.find(number);
            s2.erase(it);
            if (s2.size() < s1.size()) {
                s2.insert(*prev(s1.end()));
                s1.erase(prev(s1.end()));
            }
        }

        int c = cnt[number];
        if (c == 1) {
            cnt.erase(number); // 0
            s.erase({1, -number});
        }
        else {
            cnt[number]--;
            s.erase({c, -number});
            s.insert({c-1, -number});
        }
    }
    
    int getMean() {
        return sum / n;
    }
    
    int getMedian() {
        return *s2.begin();
    }
    
    int getMode() {
        return -prev(s.end())->second;
    }
};

/**
 * Your StatisticsTracker object will be instantiated and called as such:
 * StatisticsTracker* obj = new StatisticsTracker();
 * obj->addNumber(number);
 * obj->removeFirstAddedNumber();
 * int param_3 = obj->getMean();
 * int param_4 = obj->getMedian();
 * int param_5 = obj->getMode();
 */