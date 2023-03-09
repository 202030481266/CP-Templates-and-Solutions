// https://leetcode.cn/problems/check-if-word-can-be-placed-in-crossword/
// 一行行水平匹配或者一列列竖直匹配，如果能够匹配，那么对应的行或者列肯定只有唯一解


class Solution {
public:
	bool placeWordInCrossword(vector<vector<char>>& board, string word) {
		int m = board.size(), n = board[0].size(), sLen = word.length();
		
		// 遍历行
		for (auto& row : board) {
			for (int j = 0; j < n; ++j) {
				if (row[j] == '#')continue;
				
				// 遍历并匹配两个 # 之间的字符
				int j0 = j;
				bool ok1 = true, ok2 = true;
				// 注意第 2 层和第 3 层共用 j，因此整体复杂度为 O(nm)
				for (; j < n && row[j] != '#'; ++j) {
					// 正向匹配
					if (j - j0 >= sLen || (row[j] != ' ' && row[j] != word[j - j0])) {
						ok1 = false;
					}
					// 逆向匹配
					if (j - j0 >= sLen || (row[j] != ' ' && row[j] != word[sLen - 1 - j + j0])) {
						ok2 = false;
					}
				}
				if ((ok1 || ok2) && j - j0 == sLen) {
					return true;
				}
			}
		}

		// 遍历列（同理）
		for (int j = 0; j < n; ++j) {
			for (int i = 0; i < m; ++i) {
				if (board[i][j] == '#') continue;;
				
				int i0 = i;
				bool ok1 = true, ok2 = true;
				for (; i < m && board[i][j] != '#'; ++i) {
					if (i - i0 >= sLen || (board[i][j] != ' ' && board[i][j] != word[i - i0])) {
						ok1 = false;
					}
					if (i - i0 >= sLen || (board[i][j] != ' ' & board[i][j] != word[sLen - 1 - i + i0])) {
						ok2 = false;
					}
				}
				if ((ok1 || ok2) && i - i0 == sLen) {
					return true;
				}
			}
		}
		return false;
	}
};