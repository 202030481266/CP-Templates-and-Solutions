// xiaoshulin
// 2023.12.12

struct Node { 
	int x, y, use;
};
class Solution {
	using vec3d = vector<vector<vector<int>>>;
public:
    bool escapeMaze(vector<vector<string>>& maze) {
		int time = maze.size(), n = maze[0].size(), m = maze[0][0].size();

		if (time < n + m - 2) return false; // no enough time

		// the most important thing is realize the essence of skill2 
		// skill2 is helpful only if there exist t1, t2 and middle that satisfy following:
		// at the time t1, source -> middle is available, and at the time t2, middle -> target is available
		// and the sum of their cost is no more than 1 (only exist 1 skill1, I found this idea is adapted to mulit skill1s)

		// be careful that the middle can be any where ('.' or '#')

		const int inf = 0x3f3f3f3f;
		const int dirs[5][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
		vec3d dis1(n, vector(m, vector<int>(2, inf)));
		vec3d dis2(n, vector(m, vector<int>(2, inf)));
		int vis[n][m][2];  // every status only expand once

		// bfs
		function<void(vec3d&, int, int, int)> bfs = [&](vec3d&dp, int st, int ed, int type) {
			vector<Node> q;
			q.push_back(Node{st, ed, 1});
			// bfs
			for (int tim = 0; tim < time; ++tim) {
				vector<Node> tmp;
				memset(vis, 0, sizeof(vis));
				for (int i = 0; i < q.size(); ++i) {
					if (dp[q[i].x][q[i].y][q[i].use] == inf)
						dp[q[i].x][q[i].y][q[i].use] = tim;  // the earliest time arrive
					if (tim + 1 >= time) continue; // cannot move
					// move
					for (int k = 0; k < 5; ++k) {
						int x = q[i].x + dirs[k][0], y = q[i].y + dirs[k][1];
						if (x >= 0 && y >= 0 && x < n && y < m) {
							int nxt = (type == 0 ? tim + 1: time - 2 - tim);
							if (maze[nxt][x][y] == '.') { 
								if (!vis[x][y][q[i].use]) {
									tmp.push_back(Node{x, y, q[i].use});
									vis[x][y][q[i].use] = 1;
								}
							}
							else {
								// not arrive before
								if (q[i].use) {
                                    // use the skill1
                                    if (!vis[x][y][0]) {
                                        tmp.push_back(Node{x, y, 0});
                                        vis[x][y][0] = 1;
                                    }
									if (dp[x][y][1] == inf) {
										dp[x][y][1] = tim + 1; // record this means it can be there but will not use it to expand
									}
								}
								else {
									if (dp[x][y][0] == inf)
										dp[x][y][0] = tim + 1; // record this means it can be there but will not use it to expand
								}
							}
						}
					}
				}
				q = move(tmp);
			}
		};

		bfs(dis1, 0, 0, 0); // from start 
		if (dis1[n - 1][m - 1][0] != inf || dis1[n - 1][m - 1][1] != inf) return true;
		bfs(dis2, n - 1, m - 1, 1); // from end

		// use skill2
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (dis1[i][j][1] + min(dis2[i][j][0], dis2[i][j][1]) <= time - 1) return true; // from source no use skill1
				if (min(dis1[i][j][0], dis1[i][j][1]) + dis2[i][j][1] <= time - 1) return true; // from end no use skill1
			}
		}
		return false;
    }
};
