// 在线算法
/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */
int vis[300][500];
const int N = 105, M = 205;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Solution {
public:
	// 需要实现回溯的功能，因为机器人是典型的但移动
	// 这道题就是手写一个dfs
	void dfs(Robot& robot, int x, int y, int d) {
		robot.clean();
		vis[x + N][y + M] = 1;
		for (int i = 0; i <= 3; ++i) {
			int nd = (d + i) % 4;
			int nx = x + dir[nd][0], ny = y + dir[nd][1];
			if (!vis[nx + N][ny + M]) {
				for (int j = 0; j < i; ++j) robot.turnRight();
				if (robot.move()) {
					dfs(robot, nx, ny, nd); // 回来的时候必定是nd的反方向，需要旋转两次回到nd方向，然后再反转到d方向
					for (int j = 0; j < 2 + i; ++j) robot.turnLeft();
				}
				else
					for (int j = 0; j < i; ++j) robot.turnLeft(); // 撤销旋转
			}
		}
		// 回退，靠着自己的反方向走一步，假设这一步一定会成功
		robot.turnRight();
		robot.turnRight();
		robot.move();
	}
    void cleanRoom(Robot& robot) {
    	memset(vis, 0, sizeof(vis));
    	dfs(robot, 0, 0, 0);
    }
};
