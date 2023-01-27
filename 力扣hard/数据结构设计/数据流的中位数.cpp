// 套路： 使用优先队列可以维护前k大或者前k小的数的集合
// 对顶堆技巧可以维护动态的中位数
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int, vector<int>, greater<int>> q1;
    priority_queue<int, vector<int>, less<int>> q2;
    double median;

    MedianFinder() {}
    
    void addNum(int num) {
        if (q1.size() == 0) {
            q1.push(num);
            median = num;
        }
        else {
            if (num < median) q2.push(num);
            else q1.push(num);
            if (q1.size() > q2.size()) {
                while (q1.size() > q2.size()) {
                    int cur = q1.top();
                    q1.pop();
                    q2.push(cur);
                }
            }
            if (q2.size() > q1.size()) {
                while (q2.size() > q1.size()) {
                    int cur = q2.top();
                    q2.pop();
                    q1.push(cur);
                }
            }
        }
    }
    
    double findMedian() {
        int total = q1.size() + q2.size();
        if (total & 1) return median = q1.top();
        else {
            median = (q1.top() + q2.top()) / 2.0;
            return median;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */