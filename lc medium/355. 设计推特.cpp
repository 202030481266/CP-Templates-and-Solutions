#include <bits/stdc++.h>
using namespace std;

using bs = bitset<501>;
using pii = pair<int, int>;
using tiii = tuple<int,int,int>;

const int maxn = 501;
bs user[maxn];
vector<pii> message[maxn];
int ti = 0;

class Twitter {
public:
    
    Twitter() {
        ti = 0;
        for (int i = 1; i <= 500; ++i) {
            user[i].reset();
            message[i].clear();
        }
    }
    
    void postTweet(int userId, int tweetId) {
        message[userId].emplace_back(tweetId, ++ti);
    }
    
    vector<int> getNewsFeed(int userId) {
        priority_queue<tiii> q;
        const bs& b = user[userId];
        for (int i = 0; i < maxn; ++i) {
            if ((b.test(i) || i == userId) && message[i].size()) {
                q.emplace(message[i].back().second, (int)message[i].size()-1, i);
            }
        }
        vector<int> ans;
        for (int i = 0; i < 10 && !q.empty(); ++i) {
            auto [_, idx, Id] = q.top();
            q.pop();
            ans.push_back(message[Id][idx].first);
            if (idx - 1 >= 0) {
                q.emplace(message[Id][idx-1].second, idx-1, Id);
            }
        }
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) return;
        user[followerId].set(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if (followerId == followeeId) return;
        user[followerId].reset(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */