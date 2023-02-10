class AuthenticationManager {
private:
    int ttl;
    unordered_map<string, int> hs;
    multiset<int> s;
public:
    AuthenticationManager(int timeToLive) {
        ttl = timeToLive;
    }
    
    void generate(string tokenId, int currentTime) {
        hs[tokenId] = currentTime + ttl;
        s.emplace(currentTime + ttl);
    }
    
    void renew(string tokenId, int currentTime) {
        if (!hs.count(tokenId) || currentTime >= hs[tokenId]) 
            return;
        auto it  = s.find(hs[tokenId]);
        assert(it != s.end());
        s.erase(it);
        hs[tokenId] = currentTime + ttl;
        s.emplace(currentTime + ttl);
    }
    
    int countUnexpiredTokens(int currentTime) {
        while (s.size() && *s.begin() <= currentTime) {
            s.erase(s.begin());
        }
        return s.size();
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */