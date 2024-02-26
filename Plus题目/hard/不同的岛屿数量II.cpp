// 两种解法
// 最快的解法就是使用一个结论：如果一个图形里面所有的点的欧式距离之和误差很小，我们可以认为这个图形是相似的。
class Solution {
typedef pair<int,int> PII;
public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        // 1.类似同构问题 使用哈希映射来确定连通分量的形状
        // 2.直接使用flood fill算法即可
        const double eps = 1e-6;
        int m = grid.size(),n = grid[0].size();
        vector<vector<bool>> st(m,vector<bool>(n,false));
        PII paths[m * n];
        int tot;
        int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};
        function<void(int,int)> dfs = [&](int x,int y){
            st[x][y] = true;
            paths[tot++] = {x,y};
            for(int i=0;i<4;++i){
                int nx = x + dx[i],ny = y + dy[i];
                if(nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0 || st[nx][ny]){
                    continue;
                }
                dfs(nx,ny);
            }
        };

        function<double(PII,PII)> dist = [&](PII p1,PII p2){
            double dx = p1.first - p2.first;
            double dy = p1.second - p2.second;
            return sqrt(dx * dx + dy * dy);
        };

        function<double()> get_hash = [&]() {
            double sum = 0.0;
            for(int i=0;i<tot;i++){
                for(int j=i+1;j<tot;j++){
                    sum += dist(paths[i],paths[j]);
                }
            }
            return sum;
        };
        unordered_set<double> se;
        function<bool(double)> get_id = [&](double key){
            for(auto& num:se){
                if(fabs(key - num) < eps){
                    return false;
                }
            }
            se.insert(key);
            return true;
        };
        int ans = 0;
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(!st[i][j] && grid[i][j] == 1){
                    tot = 0;
                    dfs(i,j);
                    auto t = get_id(get_hash());
                    if(t){
                        ans ++;
                    }
                }
            }
        }

        return ans;
    }
};
// 官方的解法：利用坐标转换公式，然后判断八种可能得情况：
/*
对于一个形状，如果它可以翻转（水平和垂直）和旋转（90度、180度、270度），我们需要计算这些操作产生的所有唯一组合的数量，这是一个称为Burnside引理或轨道计数定理的组合问题的实例。
在这个问题中，我们有以下变换：
- 不做任何变换（恒等变换）
- 顺时针旋转90度
- 顺时针旋转180度
- 顺时针旋转270度
- 水平翻转
- 垂直翻转
- 水平翻转后再旋转90度（等同于垂直翻转后旋转270度）
- 水平翻转后再旋转270度（等同于垂直翻转后旋转90度）
*/
class Solution {
public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        this->grid = grid;
        this->seen = vector<vector<bool>>(m, vector<bool>(n, false));
        set<string> shapes;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                vector<int> shape;
                explore(r, c, shape);
                if (!shape.empty()) {
                    shapes.emplace(canonical(shape));
                }
            }
        }

        return shapes.size();
    }

    void explore(int r, int c, vector<int> &shape) {
        if (0 <= r && r < grid.size() && 0 <= c && c < grid[0].size() && grid[r][c] == 1 && !seen[r][c]) {
            seen[r][c] = true;
            shape.emplace_back(r * grid[0].size() + c);
            explore(r + 1, c, shape);
            explore(r - 1, c, shape);
            explore(r, c + 1, shape);
            explore(r, c - 1, shape);
        }
    }

    string canonical(const vector<int> &shape) {
        string ans;
        int lift = grid.size() + grid[0].size();
        vector<int> out(shape.size());
        vector<int> xs(shape.size());
        vector<int> ys(shape.size());

        // 对于一个坐标最多八种情况：
        // (x,y),(-x,y),(x,-y),(-x,-y),(y,x),(-y,x),(y,-x),(-y,-x)
        for (int c = 0; c < 8; ++c) {
            int t = 0;
            for (int z: shape) {
                int x = z / grid[0].size();
                int y = z % grid[0].size();
                xs[t] = c <= 1 ? x : c <= 3 ? -x : c <= 5 ? y : -y;
                ys[t++] = c <= 3 ? (c % 2 == 0 ? y : -y) : (c % 2 == 0 ? x : -x);
            }

            int mx = *min_element(xs.begin(), xs.end());
            int my = *min_element(ys.begin(), ys.end());
            
            std::transform(xs.begin(), xs.end(), ys.begin(), out.begin(), [&](int a, int b) { 
                return (a - mx) * lift + (b - my); 
            });
            sort(out.begin(), out.end());
            string candidate;
            for (int x : out) {
                candidate += to_string(x) + " ";
            }
            // 选择一种最大表示法
            if (ans < candidate) {
                ans = candidate;
            }
        }
        return ans;
    }
private:
    vector<vector<int>> grid;
    vector<vector<bool>> seen;
};
