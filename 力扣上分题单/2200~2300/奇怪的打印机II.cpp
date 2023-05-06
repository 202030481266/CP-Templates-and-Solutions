// https://leetcode.cn/problems/strange-printer-ii/
// 拓扑排序


class Solution {
public:
    bool isPrintable(vector<vector<int>>& t) {
        int i,j,k,m,n;
        m=t.size();
        n=t[0].size();
        int top[61],bottom[61],left[61],right[61];
        memset(top,0x3f,sizeof(top));
        memset(bottom,0xff,sizeof(bottom));
        memset(left,0x3f,sizeof(left));
        memset(right,0xff,sizeof(right));
        //对每种颜色的顶、底、左、右边界进行初始化
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                k=t[i][j];
                top[k]=min(top[k],i);
                bottom[k]=max(bottom[k],i);
                left[k]=min(left[k],j);
                right[k]=max(right[k],j);
            }
        }
        //遍历矩阵，获取每种颜色的上下左右边界

        bool haveedge[61][61]={0};
        //haveedge用于避免重复建边
        vector<int>edgefrom[61];
        //edgefrom[i]表示从i出发的有向边
        int deg[61]={0};
        //deg[i]表示颜色i的入度
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                //用i,j做下标遍历图中每个像素
                k=t[i][j];
                for(int color=1;color<=60;color++){
                    if(top[color]<=i&&i<=bottom[color]&&left[color]<=j&&j<=right[color]){
                        if(color!=k&&!haveedge[color][k]){
                            edgefrom[color].push_back(k);
                            deg[k]++;
                            haveedge[color][k]=true;
                        }
                    }
                    //若t[i][j]位于颜色为color的矩形内部，颜色却不为color为k
                    //说明先染成color，再染成k
                    //建立有向边color → k
                }
            }
        }

        vector<int>v;
        while(true){
            for(i=1;i<=60;i++){
                if(deg[i]==0){
                    v.push_back(i);
                    deg[i]=-1;
                    for(int a:edgefrom[i]){
                        deg[a]--;
                    }
                    break;
                }
            }
            if(i==61)break;
        }
        //将入度为0的颜色放入v，最后看1~60是不是都能放入v
        return v.size()==60;
    }
};

