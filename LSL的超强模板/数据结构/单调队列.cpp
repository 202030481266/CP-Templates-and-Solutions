// queue

vector<int> a;// array of numbers

struct Queue {
    static const int Maxn=1e6,inf=0x3f3f3f3f;
    vector<int> Q,Maxx,Minn;
    int st,ed,k,n;
    Queue() {st=ed=k=0;}
    Queue(int _n,int _k){
        st=ed=0;k=_k;n=_n;
        Q=vector<int>(_n+1,0);
        Maxx=vector<int>(_n+1,-inf);
        Minn=vector<int>(_n+1,inf);
    }
    inline void get_min() {
        st=0;ed=0;
        Q[ed++]=1;Minn[1]=a[1];
        for(int i=2;i<=n;i++) {
            while(st<ed && a[i]<a[Q[ed-1]]) --ed;
            Q[ed++]=i;
            while(st<ed && Q[st]<i-k+1) ++st;
            Minn[i]=a[Q[st]];
        }
    }
    inline void get_max() {
        st=0;ed=0;
        Q[ed++]=1;Maxx[1]=a[1];
        for(int i=2;i<=n;i++) {
            while(st<ed && a[i]>a[Q[ed-1]]) --ed;
            Q[ed++]=i;
            while(st<ed && Q[st]<i-k+1) ++st;
            Maxx[i]=a[Q[st]];
        }
    }
};