class VideoSharingPlatform {
    static int a[100010], b[100010], w[100010];
public:
    unordered_map<int, string> content;
    set<int> use;
    VideoSharingPlatform() {
        init();
    }
    void init() {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(w, 0, sizeof(w));
        use.insert(0);
    }
    
    int upload(string video) {
        int id = *use.begin();
        use.erase(use.begin());
        if (use.empty()) 
            use.insert(id + 1); // 此时此刻一定是最大的ID
        content[id] = video;
        return id;
    }
    
    void remove(int videoId) {
        if (!content.count(videoId)) return;
        content.erase(videoId);
        use.insert(videoId);
        a[videoId] = b[videoId] = w[videoId] = 0;
    }
    
    string watch(int videoId, int startMinute, int endMinute) {
        if (!content.count(videoId)) return "-1";
        string& s = content[videoId];
        int len = min(endMinute, (int)s.size()) - startMinute + 1;
        ++w[videoId];
        return s.substr(startMinute, len);
    }
    
    void like(int videoId) {
        if (!content.count(videoId)) return;
        ++a[videoId];
    }
    
    void dislike(int videoId) {
        if (!content.count(videoId)) return;
        ++b[videoId];
    }
    
    vector<int> getLikesAndDislikes(int videoId) {
        if (!content.count(videoId)) return {-1};
        return {a[videoId], b[videoId]};
    }
    
    int getViews(int videoId) {
        if (!content.count(videoId)) return -1;
        return w[videoId];
    }
};
int VideoSharingPlatform::a[100010] = {};
int VideoSharingPlatform::b[100010] = {};
int VideoSharingPlatform::w[100010] = {};

/**
 * Your VideoSharingPlatform object will be instantiated and called as such:
 * VideoSharingPlatform* obj = new VideoSharingPlatform();
 * int param_1 = obj->upload(video);
 * obj->remove(videoId);
 * string param_3 = obj->watch(videoId,startMinute,endMinute);
 * obj->like(videoId);
 * obj->dislike(videoId);
 * vector<int> param_6 = obj->getLikesAndDislikes(videoId);
 * int param_7 = obj->getViews(videoId);
 */