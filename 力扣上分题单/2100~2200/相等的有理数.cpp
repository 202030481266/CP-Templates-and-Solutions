// https://leetcode.cn/problems/equal-rational-numbers/



class Solution {
public:
	using ll = long long;
	void simplify(ll &n, ll &m) {
		if (n == 0 || m == 0) {
			n = 0, m = 1;
		}
		ll g = gcd(n, m);
		if (g > 0) {
			n /= g, m /= g;
		}
	}
	pair<ll, ll> add(ll n1, ll d1, ll n2, ll d2) {
		ll n, d;
		if (d1 == 0) n = n2, d = d2;
		else if (d2 == 0) n = n1, d = d1;
		else n = n1 * d2 + n2 * d1, d = d1 * d2;
		simplify(n, d);
		return {n, d};
	}
	pair<ll, ll> trans(string s) {
		ll int_part = 0, nonrep_part = 0, rep_part = 0, nonrep_len = 0, rep_len = 0;
		int i = 0, N = s.size();
		while (i < N && s[i] != '.') {
			int_part = int_part * 10 + s[i] - '0';
			++i;
		}
		++i; // '.'
		while (i < N && s[i] != '(') {
			nonrep_part = nonrep_part * 10 + s[i] - '0';
			++nonrep_len;
			++i;
		}
		++i; // '('
		while (i < N && s[i] != ')') {
			rep_part = rep_part * 10 + s[i] - '0';
			++rep_len;
			++i;
		}
		ll p1 = pow(10, nonrep_len);
		ll p2 = pow(10, rep_len);
		// 非重复小数部分的分子分母表示
		ll nonrep_num = nonrep_part;
		ll nonrep_dom = p1;
		// 重复部分的分子分母表示，这里需要使用等比数列的知识来判断
		ll rep_num = rep_part;
		ll rep_dom = p1 * (p2 - 1);
		simplify(nonrep_num, nonrep_dom);
		simplify(rep_num, rep_dom);
		auto p = add(nonrep_num, nonrep_dom, rep_num, rep_dom);
		return add(p.first, p.second, int_part, 1LL);
	}
    bool isRationalEqual(string s, string t) {
    	// 转换无限小数为有理数（分数）
    	return trans(s) == trans(t);
    }
};