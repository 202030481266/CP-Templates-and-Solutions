// huffman tree

class Solution {
public:
    int minBuildTime(vector<int>& blocks, int split) {
        priority_queue<int,vector<int>,greater<>> pq;
        
        // 相当于做了n-1次的合并
        for (int block : blocks)
            pq.push(block);
        
        while (pq.size() > 1){
            int smallest = pq.top();
            pq.pop();
            int second_smallest = pq.top();
            pq.pop();
            pq.push(split + second_smallest);
        }
        
        return pq.top();
    }
};

