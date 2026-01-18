#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;


class AuctionSystem {
public:
    unordered_map<int, set<pair<int, int>>> item; 
    unordered_map<ll, int> price;
    AuctionSystem() {
        item.reserve(50001);
        price.reserve(50001);
    }

    ll hash(int userId, int itemId) {
        return 1LL * itemId * 50001 + userId;
    }

    void addBid(int userId, int itemId, int bidAmount) {
        auto& s = item[itemId];
        ll val = hash(userId, itemId);
        if (price.contains(val)) removeBid(userId, itemId);
        price[val] = bidAmount;
        s.emplace(bidAmount, userId);
    }
    
    void updateBid(int userId, int itemId, int newAmount) {
        addBid(userId, itemId, newAmount);
    }
    
    void removeBid(int userId, int itemId) {
        ll val = hash(userId, itemId);
        auto& s = item[itemId];
        int p = price[val];
        price.erase(val);
        s.erase(s.find({p, userId}));
    }
    
    int getHighestBidder(int itemId) {
        auto& s = item[itemId];
        if (s.empty()) return -1;
        return s.rbegin()->second;
    }
};

/**
 * Your AuctionSystem object will be instantiated and called as such:
 * AuctionSystem* obj = new AuctionSystem();
 * obj->addBid(userId,itemId,bidAmount);
 * obj->updateBid(userId,itemId,newAmount);
 * obj->removeBid(userId,itemId);
 * int param_4 = obj->getHighestBidder(itemId);
 */
