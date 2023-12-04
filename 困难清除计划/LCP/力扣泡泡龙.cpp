class Solution {
public:
    vector<vector<tuple<int, int, int, int>>> level_infs; /* 前缀和，占用，左下指针，右下指针 */
    vector<pair<int, int>> remove_list;
    int collect(int level, TreeNode* node) {
        if(!node) 
            return 0;

        while(level + 1 >= level_infs.size())
            level_infs.push_back({{0, -1, -1, -1}});

        level_infs[level].emplace_back(
            get<0>(level_infs[level].back()) + node->val, /* 前缀和 */
            -1, /* 被占用的情况 */
            level_infs[level+1].size(), /* 左侧向下指针 */
            -1 /* 右侧向下指针(需要等遍历完之后再补充) */
        );
        node->val = level_infs[level].size() - 1;

        if(collect(level + 1, node->left) + collect(level + 1, node->right) != 2) 
            remove_list.emplace_back((int)level_infs[level].size() - 1, level);
        
        get<3>(level_infs[level].back()) = (int)level_infs[level + 1].size() - 1;

        return 1;
    }
    int getMaxLayerSum(TreeNode* root) {
        collect(0, root);

        int height = (int)level_infs.size() - 1, res = INT_MIN;
        for(int level = 0; level < height; ++level)
            res = max(res, get<0>(level_infs[level].back()));

        for(int idx = 0; idx < remove_list.size(); ++idx) {
            auto [node, start] = remove_list[idx];
            int left = node, right = node;
            int lost = get<0>(level_infs[start][left]) - get<0>(level_infs[start][left-1]);
            for(int level = start; level < height; ++level) {
                if(left > right) 
                    break;

                /* 如果当前 "管辖区间" 为整层的节点，那么没有必要继续遍历下去，它相当于删除该层 */
                /* 另外，这个优化还能避坑 "如果最后一层全删掉，那么这个和为 0 是没有意义的" */
                if(right - left + 1 == level_infs[level].size() - 1)
                    break;

                auto& [lsum, luse, ne_left, _unused1] = level_infs[level][left];
                auto& [rsum, ruse, _unused2, ne_right] = level_infs[level][right];

                /* 剪枝：如果当前区间已经被使用过，则跳过后续部分 */
                if(luse != -1 && luse == ruse)
                    break;
                luse = ruse = idx;

                int add = 0;
                if(ne_left <= ne_right)
                    add = get<0>(level_infs[level+1][ne_right]) - get<0>(level_infs[level+1][ne_left - 1]);

                res = max(res, get<0>(level_infs[level].back()) - lost + add);

                left = ne_left, right = ne_right, lost = add;
            }
        }

        return res;
    }
};
