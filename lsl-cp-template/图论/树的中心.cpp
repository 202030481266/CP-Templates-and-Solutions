// 这份代码默认节点编号从 1 开始，即 i ∈ [1,n]，使用vector存图
int longest_path[N];
int second_longest_path[N];
int up_path[N];
int center_x, center_y, min_radius = 1e9;  // longest_path,second_longest_path对应上文中的len1,len2

struct Edge {
    int to, weight;  // to为边指向的节点，weight为边权
};

vector<Edge> neighbors[N];

void DfsDown(int current, int parent) {  // 求取len1和len2
    for (const auto& next_edge : neighbors[current]) {
        int next = next_edge.to, weight = next_edge.weight;  // next为这条边通向的节点，weight为边权
        if (next == parent) {
            continue;
        }
        DfsDown(next, current);
        if (longest_path[next] + weight > longest_path[current]) {  // 可以更新最长链
            second_longest_path[current] = longest_path[current];
            longest_path[current] = longest_path[next] + weight;
        } else if (longest_path[next] + weight > second_longest_path[current]) {  // 不能更新最长链，但可更新次长链
            second_longest_path[current] = longest_path[next] + weight;
        }
    }
}

void DfsUp(int current, int parent) {
    for (const auto& next_edge : neighbors[current]) {
        int next = next_edge.to, weight = next_edge.weight;
        if (next == parent) {
            continue;
        }
        up_path[next] = up_path[current] + weight;
        if (longest_path[next] + weight != longest_path[current]) {  // 如果自己子树里的最长链不在next子树里
            up_path[next] = std::max(up_path[next], longest_path[current] + weight);
        } else {  // 自己子树里的最长链在next子树里，只能使用次长链
            up_path[next] = std::max(up_path[next], second_longest_path[current] + weight);
        }
        DfsUp(next, current);
    }
}

void GetTreeCenter() {  // 统计树的中心，记为center_x和center_y（若存在）
    DfsDown(1, 0);
    DfsUp(1, 0);
    for (int i = 1; i <= n; i++) {
        if (std::max(longest_path[i], up_path[i]) < min_radius) {  // 找到了当前max(len1[x],up[x])最小点
            min_radius = std::max(longest_path[i], up_path[i]);
            center_x = i;
            center_y = 0;
        } else if (std::max(longest_path[i], up_path[i]) == min_radius) {  // 另一个中心
            center_y = i;
        }
    }
}