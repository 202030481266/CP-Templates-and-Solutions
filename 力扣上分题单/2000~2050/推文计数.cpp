// https://leetcode.cn/problems/tweet-counts-per-frequency/



// 就是要线性遍历，哎，我还以为有啥技巧
class TweetCounts {
public:
    map<string, multiset<int>> cnt;

    TweetCounts() {}

    void recordTweet(string tweetName, int time) {
        cnt[tweetName].emplace(time);
    }

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        int len = 0;
        if (freq == "minute") len = 60;
        else if (freq == "hour") len = 60 * 60;
        else len = 60 * 60 * 24;
        vector<int> ans((endTime - startTime) / len + 1);
        auto begin = cnt[tweetName].lower_bound(startTime);
        auto end = cnt[tweetName].upper_bound(endTime);
        for (; begin != end; ++begin) {
            ++ans[(*begin - startTime) / len];
        }
        return ans;
    }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */