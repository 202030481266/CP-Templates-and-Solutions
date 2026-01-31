#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class FileSharing {
public:
    int n, id;
    set<int> s;
    unordered_map<int, set<int>> mp;
    vector<set<int>> chunks;
    FileSharing(int m) {
        // 1 <= m <= 100
        this->n = m;
        id = 1;
        chunks.resize(n+1);
    }
    
    int join(vector<int> ownedChunks) {
        int userid;
        if (s.empty()) {
            userid = id++;
        }
        else {
            userid = *s.begin();
            s.erase(s.begin()); 
        }
        for (auto& v : ownedChunks) {
            chunks[v].insert(userid);
            mp[userid].insert(v);
        }
        return userid;
    }
    
    void leave(int userID) {
        s.insert(userID);
        for (int v : mp[userID]) {
            chunks[v].erase(userID);
        }
        mp.erase(userID);
    }
    
    vector<int> request(int userID, int chunkID) {
        vector<int> res;
        for (int v : chunks[chunkID]) {
            res.push_back(v);
        }
        if (!res.empty()) {
            mp[userID].insert(chunkID);
            chunks[chunkID].insert(userID);
        }
        return res;
    }
};

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing* obj = new FileSharing(m);
 * int param_1 = obj->join(ownedChunks);
 * obj->leave(userID);
 * vector<int> param_3 = obj->request(userID,chunkID);
 */