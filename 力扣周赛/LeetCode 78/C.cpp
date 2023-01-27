#include <bits/stdc++.h>
using namespace std;

// 贪心算法，其实很容易想到的，就是毯子一定在某个区间的左端点

int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
  sort(tiles.begin(), tiles.end());
  int n = tiles.size();
  long long cur = 0, ans = 0;
  for(int i = 0, j = 0; i < n; i++) {
    while(j < n && tiles[j][1] - tiles[i][0] + 1 <= carpetLen) cur += (tiles[j][1] - tiles[j][0] + 1), j++;
    if(j < n) ans = max(ans, cur + max(0, tiles[i][0] + carpetLen - tiles[j][0]));
    else ans = max(ans, cur);
    cur -= (tiles[i][1] - tiles[i][0] + 1);
  }
  return ans;
}
