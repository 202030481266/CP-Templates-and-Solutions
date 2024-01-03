// xiaoshulin
// 2024.1.2

class BlackBox {
	using pii = pair<int, int>;
	unordered_map<int, int> mp, dfn;
	int tot, n, m, cnt, seg;
	vector<bool> vis;
	vector<int> neg_line, pos_line;
	vector<int> number, belong; 
	vector<set<pii>> S; 
	vector<int> sz;
    int opens = 0;
public:
    BlackBox(int N, int M) {
		n = N + 1, m = M + 1, tot = 0, cnt = 0;
		number.resize(2 * (n + m));
		belong.resize(2 * (n + m));
		neg_line.resize(2 * (n + m));
		pos_line.resize(2 * (n + m));
		vis.resize(2 * (n + m));
		for (int i = 0; i < m - 1; ++i) {
			mp[tot] = i; 
			dfn[i] = tot++;  
		}
		for (int i = 0; i < n - 1; ++i) {
			mp[tot] = i * m + (m - 1); 
			dfn[i * m +  (m - 1)] = tot++;
		}
		for (int i = m - 1; i >= 1; --i) {
			mp[tot] = (n - 1) * m + i; 
			dfn[(n - 1) * m + i] = tot++;
		}
		for (int i = n - 1; i >= 1; --i) {
			mp[tot] = i * m; 
			dfn[i * m] = tot++;
		}
		// y + x is the same
		// y - x is the same
		// build the graph
		for (int i = 1; i < m; ++i) { // [0, i] = [i, 0] = [n - 1, i - n + 1]
			int idx = i;
			if (i < n) { // [i, 0]
                // assert(dfn.count(idx) > 0 && dfn.count(i * m) > 0);
				pos_line[dfn[idx]] = dfn[i * m];
			}
			else { // [n - 1, i - n + 1]
                // assert(dfn.count(idx) > 0 && dfn.count((n - 1) * m + i - n + 1) > 0);
				pos_line[dfn[idx]] = dfn[(n - 1) * m + i - n + 1];
			}
		}
		for (int i = 0; i < m - 1; ++i) { // [0, i] = [n - 1, n - 1 + i] = [m - 1 - i, m - 1]
			int idx = i;
			if (n - 1 + i < m && n - 1 + i >= 0) {
                // assert(dfn.count(idx) > 0 && dfn.count((n - 1) * m + n - 1 + i) > 0);
				neg_line[dfn[idx]] = dfn[(n - 1) * m + n - 1 + i];
			}
			else {
                // assert(dfn.count(idx) > 0 && dfn.count((m - 1 - i) * m + m - 1) > 0);
				neg_line[dfn[idx]] = dfn[(m - 1 - i) * m + m - 1];
			}
		}
		for (int i = 0; i < m - 1; ++i) { // [n - 1, i] = [0, n - 1 + i] = [n + i - m, m - 1] 
			int idx = (n - 1) * m + i;
			if (n - 1 + i < m && n - 1 + i >= 0) {
                assert(dfn.count(idx) > 0 && dfn.count(n - 1 + i) > 0);
				pos_line[dfn[idx]] = dfn[n - 1 + i];
			}
			else { 
                assert(dfn.count(idx) > 0 && dfn.count((n + i - m) * m + m - 1) > 0);
				pos_line[dfn[idx]] = dfn[(n + i - m) * m + m - 1];
			}
		}
		for (int i = 1; i < m; ++i) { // [n - 1, i] = [0, i - n + 1] = [n - i - 1, 0]
			int idx = (n - 1) * m + i;
			if (i - n + 1 < m && i - n + 1 >= 0) {
                assert(dfn.count(idx) > 0 && dfn.count(i - n + 1) > 0);
				neg_line[dfn[idx]] = dfn[i - n + 1];
			}
			else {
                assert(dfn.count(idx) > 0 && dfn.count((n - i - 1) * m) > 0);
				neg_line[dfn[idx]] = dfn[(n - i - 1) * m];
			}
		}
		for (int i = 1; i < n - 1; ++i) { // [i, 0] = [0, i] = [i - m + 1, m - 1]
			int idx = i * m;
			if (i < m && i >= 0) {
                // assert(dfn.count(idx) > 0 && dfn.count(i) > 0);
				pos_line[dfn[idx]] = dfn[i];
			}
			else { 
                // assert(dfn.count(idx) > 0 && dfn.count((i - m + 1) * m + m - 1) > 0);
				pos_line[dfn[idx]] = dfn[(i - m + 1) * m + m - 1];
			}
		}
		for (int i = 1; i < n - 1; ++i) { // [i, 0] = [n - 1, n - i - 1] = [m - 1 + i, m - 1]
			int idx = i * m;
			if (n - i - 1 < m && n - i - 1 >= 0) {
                // assert(dfn.count(idx) > 0 && dfn.count((n - 1) * m + n - i - 1) > 0);
				neg_line[dfn[idx]] = dfn[(n - 1) * m + n - i - 1];
			}
			else {
                // assert(dfn.count(idx) > 0 && dfn.count((m - 1 + i) * m + m - 1) > 0);
				neg_line[dfn[idx]] = dfn[(m - 1 + i) * m + m - 1];
			}
		}
		for (int i = 1; i < n - 1; ++i) { // [i, m - 1] = [n - 1, m + i - n] = [i + m - 1, 0]
			int idx = i * m + m - 1;
			if (i + m - 1 < n && i + m - 1 >= 0) {
                // assert(dfn.count(idx) > 0 && dfn.count((i + m - 1) * m) > 0);
				pos_line[dfn[idx]] = dfn[(i + m - 1) * m];
			}
			else {
                // assert(dfn.count(idx) > 0 && dfn.count((n - 1) * m + m + i - n) > 0);
				pos_line[dfn[idx]] = dfn[(n - 1) * m + m + i - n];
			}
		}
		for (int i = 1; i < n - 1; ++i) { // [i, m - 1] = [0, m - i - 1] = [1 + i - m, 0]
			int idx = i * m + m - 1;
			if (m - i - 1 >= 0 && m - i - 1 < m) {
                // assert(dfn.count(idx) > 0 && dfn.count(m - i - 1) > 0);
				neg_line[dfn[idx]] = dfn[m - i - 1];
			}
			else {
                // assert(dfn.count(idx) > 0 && dfn.count((1 + i - m) * m) > 0);
				neg_line[dfn[idx]] = dfn[(1 + i - m) * m];
			}
		}
		// find path
		vector<int> top{dfn[0], dfn[m - 1], dfn[n * m - 1], dfn[(n - 1) * m]};
		for (int& v : top) {
			if (!vis[v]) {
				vis[v] = 1;
				dfs(v, 0, cnt);
				++cnt;
			}
		}
		seg = cnt; // [1, seg) is paths but not the circles 
		// find the circle
		for (int i = 0; i < tot; ++i) {
			if (!vis[i]) {
				vis[i] = 1;
				dfs(i, 0, cnt);
				++cnt;
			}
		}
		// [seg,cnt) is the circles
		S.resize(cnt);
		sz.resize(cnt);

        // --------------------------------debug
        // cout << "test mp" << endl;
        // for (int i = 0; i < tot; ++i) {
        //     cout << i << ' ' << mp[i] / m << ' ' << mp[i] % m << endl;
        // }
        // cout << "test dfn" << endl;
        // for (int i = 0; i < tot; ++i) {
        //     assert(dfn[mp[i]] == i);
        // }
        // cout << "test pos_line and neg_line" << endl;
        // for (int i = 0; i < tot; ++i) {
        //     cout << i << ' ' << pos_line[i] << ' ' << neg_line[i] << endl;
        // }
        // cout << "seg : " << seg << endl;
        // vector<int> group[cnt];
		// for (int i = 0; i < tot; ++i) {
		// 	group[belong[i]].push_back(i);
		// }
        // for (int i = 0; i < cnt; ++i) {
        //     cout <<i << ':' << endl;
        //     cout << "group dfn : "<<endl;
        //     for (int& v : group[i]) cout << v << ' ';
        //     cout << endl << "number : "<<endl;
        //     for (int& v : group[i]) cout << number[v] << ' ';
        //     cout << endl;
        // }
		// cout << endl;
        //-----------------------------------

		for (int i = 0; i < tot; ++i) ++sz[belong[i]];
    }
	void dfs(int u, int cnt, int f) {
        // cout << "dfs " << u << ' ' << cnt << ' ' << f << endl;
		number[u] = cnt;
		belong[u] = f;
		if (u == dfn[0] || u == dfn[n * m - 1]) {
			// find the path
			if (!vis[neg_line[u]]) {
				vis[neg_line[u]] = 1;
				dfs(neg_line[u], cnt + 1, f);
			}
		}
		else if (u == dfn[(n - 1) * m] || u == dfn[m - 1]) {
			// find the path
			if (!vis[pos_line[u]]) {
				vis[pos_line[u]] = 1;
				dfs(pos_line[u], cnt + 1, f);
			}
		}
		else {
			// find the circle
			if (!vis[pos_line[u]]) {
				vis[pos_line[u]] = 1;
				dfs(pos_line[u], cnt + 1, f);
			}
			else if (!vis[neg_line[u]]) {
				vis[neg_line[u]] = 1;
				dfs(neg_line[u], cnt + 1, f);
			}
		}
	}
	int dis(int x, int y, int flag, int siz) {
		// circle : siz , x -> y
        if (!flag) swap(x, y);
		if (y <= x) return siz - x + y;
        else return y - x;
	}
    int open(int index, int direction) {
        // cout << ++opens << " open command " <<" idnex : " << index << ' ' << "direction : " << direction<<endl;
		int b = belong[index], num = number[index], ans;
		auto& s = S[b];
		if (s.find(make_pair(num, index)) != s.end()) s.erase(make_pair(num, index)); // guarantee there won't exist the same node
		if (b < seg) {
			// it is a path
			int v = (direction == 1 ? pos_line[index] : neg_line[index]), num_v = number[v];
            auto it = s.lower_bound(make_pair(num, index));

			//----------------------------------------------debug
			// cout << "path" << endl;
            // if  (it != s.end())
            // cout << index << ' ' << direction << ' ' << it->first << ' ' << it->second << endl;
            // else cout << index << ' ' << direction << ' ' << -1 << ' ' << -1 << endl;
            // cout << num_v << ' ' << num << endl;
			// cout << endl;
			//---------------------------------------------------
			

			if (num_v > num) {
				// find the first one that bigger that u
				if (it == s.end()) ans = index; // the light will come back
				else {
					ans = it->second;// the light is gone
				}
			}
			else {
				// find the first one that smaller that u
				if (it == s.begin()) ans = index; // all the nodes are in front of the node
				else {
					it = prev(it); // the previous one
					ans = it->second;
				}
			}
			s.emplace(num, index);
		}
		else {
			// it is a circle
            if (s.empty()) { // no one
                s.emplace(num, index);
                return index;
            }
            if (s.size() == 1) { // only one
				ans = s.begin()->second;
                s.emplace(num, index);
                return ans;
            }
			int x = pos_line[index], y = neg_line[index], num_x = number[x], num_y = number[y];
			auto it = s.lower_bound(make_pair(num, index)); // find the bigger one
			int pre, nxt, siz = sz[b];
			if (it == s.end()) {
				pre = prev(it)->second;
				nxt = s.begin()->second;
			}
			else if (it == s.begin()) {
				pre = s.rbegin()->second;
				nxt = it->second;
			}
			else {
				pre = prev(it)->second;
				nxt = it->second;
			}

            //----------------------------------------debug
			// cout << "circle" << endl;
            // cout << pre << ' ' << nxt << ' ' << number[pre] << ' ' << number[nxt] << endl;
            // cout << x << ' ' << y << ' '<< num_x << ' ' << num_y << ' ' << num << endl;
			// cout << endl;
            //------------------------------------------------

			if (direction < 0) {
				int dir = (num_y == (num + 1) % siz);
				if (dis(num, number[pre], dir, siz) < dis(num, number[nxt], dir, siz)) ans = pre;
				else ans = nxt;
			}
			else {
				int dir = (num_x == (num + 1) % siz);
				if (dis(num, number[pre], dir, siz) < dis(num, number[nxt], dir, siz)) ans = pre;
				else ans = nxt;
			}
			s.emplace(num, index);
		}
		return ans;
    }
    
    void close(int index) {
		int b = belong[index], num = number[index]; 
		auto& s = S[b];
		s.erase(make_pair(num, index));
    }
};


