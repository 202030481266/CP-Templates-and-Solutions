#include <bits/stdc++.h>
using namespace std;


int countWords(vector<string>& words1, vector<string>& words2) {
	map<string, int> mp1;
	map<string, int> mp2;
	for (string& s : words1) ++mp1[s];
	for (string& s : words2) ++mp2[s];
	int ans = 0;
	for (auto[s, cnt] : mp1) 
		if (mp2[s] == 1 && cnt == 1) ++ans;
	return ans;
}


int main() {
	vector<string> words1{"leetcode","is","amazing","as","is"}, words2{"amazing","leetcode","is"};
	cout << countWords(words1, words2) << endl;
}