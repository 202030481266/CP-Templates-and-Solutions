class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        int ans = 0;
        vector<int> nodes;
        for (int i = 0; i < sideLength; ++i)
            for (int j = 0; j < sideLength; ++j) {
                int num = 1;
                num *= (width - i - 1) / sideLength + 1;
                num *= (height - j - 1) / sideLength + 1;
                nodes.emplace_back(num);
            }
        sort(nodes.begin(), nodes.end(), [](int a, int b) {
          return a > b;  
        });
        for (int i = 0; i < maxOnes; ++i)
            ans += nodes[i];
        return ans;
    }
};

