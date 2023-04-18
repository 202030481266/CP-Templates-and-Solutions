// https://leetcode.cn/problems/design-movie-rental-system/



class MovieRentingSystem {
public:
	unordered_map<int, set<pair<int, int>>> s;
	set<tuple<int, int, int>> total;
	map<pair<int, int>, int> price;
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
    	for (auto &c : entries) {
    		s[c[1]].emplace(c[2], c[0]);
    		price[{c[0], c[1]}] = c[2];
    	}
    }
    
    vector<int> search(int movie) {
    	vector<int> ans;
    	auto &p = s[movie];
    	int i = 0;
    	for (auto it = p.begin(); it != p.end() && i < 5; ++i, ++it) 
    		ans.emplace_back(it->second);
    	return ans;
    }
    
    void rent(int shop, int movie) {
    	auto &p = s[movie];
    	int val = price[{shop, movie}];
    	p.erase({val, shop});  // 删除movie集合中的shop商店
    	total.emplace(val, shop, movie); // 添加进租借的电影集合
    }
    
    void drop(int shop, int movie) {
    	int val = price[{shop, movie}];
    	total.erase({val, shop, movie});  // 删除在租借的电影集合
    	s[movie].emplace(val, shop);  // 添加进电影对应的商店集合
    }
    
    vector<vector<int>> report() {
    	vector<vector<int>> ans;
    	int i = 0;
    	for (auto it = total.begin(); it != total.end() && i < 5; ++i, ++it)
    		ans.emplace_back(vector<int>{get<1>(*it), get<2>(*it)});
    	return ans;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */