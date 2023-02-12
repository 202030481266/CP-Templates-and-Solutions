#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string alphabetBoardPath(string target) {
		string ans;
		// g[i][j] is char(i * 5 + j)
		auto f = [&](char x, char y) {
			int xx = (x - 'a') / 5;
			int xy = (x - 'a') % 5;
			int yx = (y - 'a') / 5;
			int yy = (y - 'a') % 5;
			// x->y
			string path;
			if (xy > yy) {
				for (int i = 1; i <= xy - yy; ++i)
					path += "L";
			}
			if (xx > yx) {
				for (int i = 1; i <= xx - yx; ++i)
					path += "U";
			} 
			if (xx < yx) {
				for (int i = 1; i <= yx - xx; ++i)
					path += "D";
			}
			
			if (yy > xy) {
				for (int i = 1; i <= yy - xy; ++i)
					path += "R";
			}
			return path;
		};
		char ch = 'a';
		for (int i = 0; i < target.size(); ++i) {
			if (target[i] == ch) {
				ans += "!";
			}
			else {
				ans += f(ch, target[i]);
				ch = target[i];
				ans += "!";
			}
		}
		return ans;
    }
};
