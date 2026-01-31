#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;

const double EPS = 1e-5; // 精度控制，这道题不能使用太高的精度，否则会wa

typedef std::vector<double> Vector;

// 高斯消元，返回线性基
void gaussElimination(std::vector<Vector>& vectors, vector<int>& weight) {
    int n = vectors.size();
    int dim = vectors[0].size();
    int rank = 0;

    // 对于每一列
    for (int col = 0; col < dim; ++col) {
        // 寻找当前列的主元
        int pivot = -1, w = INF;
        for (int row = rank; row < n; ++row) {
            if (std::fabs(vectors[row][col]) > EPS) {
                if (weight[row] < w) {
                    w = weight[row];
                    pivot = row;
                }
            }
        }
        // 如果没有找到非零的主元，继续下一列
        if (pivot == -1) continue;

        // 交换当前行和主元行，并确保非零行在顶部
        std::swap(vectors[rank], vectors[pivot]);
        std::swap(weight[rank], weight[pivot]);

        // 将主元所在行归一化
        double pivotVal = vectors[rank][col];
        for (int j = col; j < dim; ++j) {
            vectors[rank][j] /= pivotVal;
        }

        // 对其他行进行消元
        for (int row = 0; row < n; ++row) {
            if (row != rank && std::fabs(vectors[row][col]) > EPS) {
                double factor = vectors[row][col];
                for (int j = col; j < dim; ++j) {
                    vectors[row][j] -= factor * vectors[rank][j];
                }
            }
        }
        ++rank;
    }

    int ans = accumulate(weight.begin(), weight.begin() + rank, 0);
    cout << rank << ' ' << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    vector<Vector> vec(n, Vector(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> vec[i][j];
        }
    }
    vector<int> weight(n);
    for (int& v : weight) cin >> v;
    vector<int> indices(n);
    gaussElimination(vec, weight);
}