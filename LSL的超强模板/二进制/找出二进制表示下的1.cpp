// lowbit运算，hash, 树状数组


int H[37], x;
cin >> x;
for(int i = 0; i < 36; i++) {H[(1ll << i) % 37] = i;}
while(cin >> x) {
    while(x > 0) {
        cout << H[lowbit(x) % 37] << ' ';
        x -= lowbit(x);
    }
    cout << endl;
}