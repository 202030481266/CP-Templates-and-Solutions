// https://leetcode.cn/problems/course-schedule-iii/
// 经典的反悔贪心技巧模板题


class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int n = courses.size();
        // 总是应该先选那些结束早的课程，仔细想想就懂了
        sort(courses.begin(),courses.end(),[&](const auto& v1,const auto& v2){
        	if (v1[1] == v2[1]) return v1[0] < v2[0];
        	else return v1[1] < v2[1];
        });
        priority_queue<int> pq;
        int times = 0;
        // 满足条件的课程有多个时 选择持续时间最短的 这样可以使结果最优
        // 反悔贪心思想
        for (int i = 0; i < n; ++i) {
            int duration = courses[i][0],lastday = courses[i][1];
            if (times + duration <= lastday){
                times += duration;
                pq.push(duration);
            } else if (pq.size() && pq.top() > duration){
            	// 老子把之前的课程不学了，我学这个更好
                times -= pq.top() - duration;
                pq.pop();
                pq.push(duration);
            }
        }
        return pq.size();
    }
};

