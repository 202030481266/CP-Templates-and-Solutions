// xiaoshulin
// 2024.1.9

class Solution {
	using pii = pair<int, int>;
public:
    int maxPartitionsAfterOperations(string ss, int k) {
		if (k == 26) return 1;
		int n = ss.size();
		// I think there should be a O(n) algorithm
		int type = 0, s = 0, l = 0;
		vector<pii> arr;
		vector<int> cur;
		vector<vector<int>> change;
		for (int i = 0; i < n; ++i) {
			int ch = ss[i] - 'a';
			if (!((s >> ch) & 1)) {
				if (type == k) {
					// [l, i)
					arr.emplace_back(l, i);
					change.push_back(cur);
					type = 0;
					s = 0;
					l = i;
					cur = vector<int>{};
				}
				++type;
				s |= (1 << ch);
				cur.push_back(i);
			}
		}
		if (l < n) {
			arr.emplace_back(l, n);
			change.push_back(cur);
		}
		vector<pii> f(n + 1);
		s = 0;
		type = 0;
		int res = 1;
		// reverse read is the same result as from left to right
		// we can prove it using math
		f[n] = make_pair(0, 0);
		for (int i = n - 1; i >= 0; --i) {
			int ch = ss[i] - 'a';
			if (!((s >> ch) & 1)) {
				if (type == k) {
					++res;
					type = 0;
					s = 0;
				}
				++type;
				s |= (1 << ch);
			}
			f[i] = make_pair(res, s);
		}
		// construct the link list
		vector<int> nxt(n);
		int last;
		for (int i = 0; i < 26; ++i) {
			last = -1;
			for (int j = n - 1; j >= 0; --j) {
				if (ss[j] - 'a' == i) {
					nxt[j] = last;
					last = j;
				}
			}
		}
        // -----------------------------------------debug f
        // cout << "debug f" <<endl;
        // for (int i = 0; i <= n; ++i) {
        //     cout << i << endl;
        //     cout << f[i].first << ' ' << f[i].second << endl;
        // }
        //------------------------------------------end debug

		int N = arr.size(), ans = N;
		const int all = (1 << 26) - 1; 
		for (int i = 0; i < N; ++i) {
			int t = change[i].size(), l = arr[i].first, r = arr[i].second; 

            //-------------------------------------------debug arr
            // cout << "print arr[" <<i<<"]" << endl;
            // cout << l << ' ' << r << ' ' << change[i].back() << endl;
            // for (int& p : change[i]) cout <<p << ' ';cout <<endl<<endl;
            //--------------------------------------------

			if (r - l > k) {
				// means that there are positions we can put a new character
				if (t == k) {
					// it have k type characters in this section
					int ed = change[i].back(); // [l, ed)
					if (ed - l > k - 1) {
						ans = max(ans, i + 1 + f[ed].first); // [l, ed)
					}
					if (r - ed > 1) { // [ed, r)
						int s = 0;
						for (int& p : change[i]) s |= (1 << ss[p] - 'a');
						// put in the change
						for (int& p : change[i]) {
							int nxt_p = nxt[p];
							if (nxt[p] < r && nxt_p != -1 && nxt_p > ed) {
								ans = max(ans, i + 1 + f[nxt_p].first);
							}
						}
						// put in the [ed + 1, r)
						for (int pos = ed + 1; pos < r; ++pos) {//[l, i)
							// we should choose those that not appear in the change 
							int st = f[pos + 1].second;
							if ((st | s) != all && __builtin_popcount(f[pos + 1].second) == k) {
								ans = max(ans, i + 1 + f[pos + 1].first + 1);
							}
							else {
								ans = max(ans, i + 1 + f[pos + 1].first);
							}
						}
					}
				}
			}
		}
		return ans;
    }
};
