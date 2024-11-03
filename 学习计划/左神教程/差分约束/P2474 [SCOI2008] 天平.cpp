#include <bits/stdc++.h>
using namespace std;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, a, b;
    cin >> n >> a >> b;
    
    vector<string> s(n+1);
    for(int i=1; i<=n; ++i){
        cin >> s[i];
        // Ensure the string has exactly n characters
        while(s[i].size() < n) s[i] += '?';
    }
    
    // Initialize dmin and dmax
    vector<vector<int>> dmin(n+1, vector<int>(n+1, -2));
    vector<vector<int>> dmax(n+1, vector<int>(n+1, 2));
    
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            if(i == j){
                dmin[i][j] = 0;
                dmax[i][j] = 0;
                continue;
            }
            char c = s[i][j-1];
            if(c == '+'){
                dmin[i][j] = 1;
                dmax[i][j] = 2;
            }
            else if(c == '-'){
                dmin[i][j] = -2;
                dmax[i][j] = -1;
            }
            else if(c == '='){
                dmin[i][j] = 0;
                dmax[i][j] = 0;
            }
            else { // '?'
                dmin[i][j] = -2;
                dmax[i][j] = 2;
            }
        }
    }
    
    // Floyd-Warshall adaptation
    for(int k=1; k<=n; ++k){
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                dmin[i][j] = max(dmin[i][j], dmin[i][k] + dmin[k][j]);
                dmax[i][j] = min(dmax[i][j], dmax[i][k] + dmax[k][j]);
            }
        }
    }
    
    int ans1=0, ans2=0, ans3=0;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<i; ++j){
            if(i == a || i == b || j == a || j == b) continue;
            
            // Check if left side is always heavier
            if(dmin[a][i] > dmax[j][b] || dmin[a][j] > dmax[i][b]){
                ans1++;
            }
            
            // Check if right side is always heavier
            if(dmax[a][i] < dmin[j][b] || dmax[a][j] < dmin[i][b]){
                ans3++;
            }
            
            // Check if sides are always balanced
            bool balanced1 = (dmin[a][i] == dmax[a][i]) && (dmin[j][b] == dmax[j][b]) && (dmin[a][i] == dmin[j][b]);
            bool balanced2 = (dmin[b][i] == dmax[b][i]) && (dmin[j][a] == dmax[j][a]) && (dmin[b][i] == dmin[j][a]);
            if(balanced1 || balanced2){
                ans2++;
            }
        }
    }
    
    cout << ans1 << " " << ans2 << " " << ans3;
}
