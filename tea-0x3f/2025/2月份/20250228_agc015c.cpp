// 真的是太妙了，问题等价于查询子矩形内部有多少棵树的问题
// 错误思路：不使用统计的思想，一直在连通性和树上面兜兜转转

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

// This function contains the core logic, similar to the Go implementation.
void run() {
    // Use fast I/O, equivalent to Go's bufio.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::string> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // We use 1-based indexing for prefix sum arrays for easier calculations.
    // sumV stores the count of '1's (vertices).
    std::vector<std::vector<int>> sumV(n + 1, std::vector<int>(m + 1, 0));
    // sumH stores the count of horizontal edges.
    std::vector<std::vector<int>> sumH(n + 1, std::vector<int>(m + 1, 0));
    // sumVert stores the count of vertical edges.
    std::vector<std::vector<int>> sumVert(n + 1, std::vector<int>(m + 1, 0));

    // Pre-computation step: build the 2D prefix sum arrays.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Standard 2D prefix sum calculation for vertices.
            sumV[i + 1][j + 1] = sumV[i][j + 1] + sumV[i + 1][j] - sumV[i][j] + (a[i][j] - '0');

            // Check for a horizontal edge between (i, j) and (i, j+1).
            int h_edge = (j + 1 < m && a[i][j] == '1' && a[i][j + 1] == '1');
            sumH[i + 1][j + 1] = sumH[i][j + 1] + sumH[i + 1][j] - sumH[i][j] + h_edge;

            // Check for a vertical edge between (i, j) and (i+1, j).
            int v_edge = (i + 1 < n && a[i][j] == '1' && a[i + 1][j] == '1');
            sumVert[i + 1][j + 1] = sumVert[i][j + 1] + sumVert[i + 1][j] - sumVert[i][j] + v_edge;
        }
    }

    // Process each query.
    for (int k = 0; k < q; ++k) {
        int r1, c1, r2, c2;
        std::cin >> r1 >> c1 >> r2 >> c2;

        // Calculate the number of vertices in the subgrid [r1..r2] x [c1..c2].
        // This is a standard 2D prefix sum query.
        int vertices = sumV[r2][c2] - sumV[r1 - 1][c2] - sumV[r2][c1 - 1] + sumV[r1 - 1][c1 - 1];

        // Calculate horizontal edges fully within the subgrid.
        // These edges exist in the rectangle [r1..r2] x [c1..c2-1].
        int h_edges = 0;
        if (c2 > c1) {
            h_edges = sumH[r2][c2 - 1] - sumH[r1 - 1][c2 - 1] - sumH[r2][c1 - 1] + sumH[r1 - 1][c1 - 1];
        }

        // Calculate vertical edges fully within the subgrid.
        // These edges exist in the rectangle [r1..r2-1] x [c1..c2].
        int v_edges = 0;
        if (r2 > r1) {
            v_edges = sumVert[r2 - 1][c2] - sumVert[r1 - 1][c2] - sumVert[r2 - 1][c1 - 1] + sumVert[r1 - 1][c1 - 1];
        }

        int total_edges = h_edges + v_edges;

        // For a forest (like a grid graph), the number of connected components is |V| - |E|.
        std::cout << vertices - total_edges << "\n";
    }
}

int main() {
    run();
    return 0;
}
