#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int cap, cost;
};

class Solution {
public:
    // Add `k` as a parameter if needed by the problem
    int findMinimumTime(vector<int>& strength, int k) {
        int n = (int)strength.size();
        int S = 2*n;     // Source index
        int T = 2*n + 1; // Sink index
        vector<vector<Edge>> g(T+1);

        auto addEdge = [&](int u, int v, int cap, int cost) {
            g[u].push_back({v,(int)g[v].size(),cap,cost});
            g[v].push_back({u,(int)g[u].size()-1,0,-cost});
        };

        // Build the graph
        // For each lock i (0-based):
        //   We connect from i (left part) to each j in [0, n-1] (right part as n+j) with capacity=1 and cost computed.
        //   Also connect S -> i and n+j -> T to ensure matching structure.
        for (int i = 0; i < n; i++) {
            int s = strength[i];
            for (int j = 0; j < n; j++) {
                int x = 1 + k*j;
                int cost = (s - 1)/x + 1;
                addEdge(i, n+j, 1, cost);
            }
            addEdge(S, i, 1, 0);
        }
        for (int j = n; j < 2*n; j++) {
            addEdge(j, T, 1, 0);
        }

        // Now we run Min-Cost Max-Flow (SPFA)
        int minCost = 0;
        vector<int> dist(T+1), inq(T+1,0);
        vector<pair<int,int>> parent(T+1);

        auto spfa = [&]() {
            for (int i = 0; i <= T; i++) {
                dist[i] = INT_MAX;
            }
            dist[S] = 0;
            queue<int>q;
            q.push(S);
            inq[S] = 1;

            while(!q.empty()){
                int u=q.front();q.pop();
                inq[u]=0;
                for (int i = 0; i<(int)g[u].size(); i++){
                    const auto &e=g[u][i];
                    if(e.cap>0 && dist[u]+e.cost<dist[e.to]) {
                        dist[e.to]=dist[u]+e.cost;
                        parent[e.to]={u,i};
                        if(!inq[e.to]){
                            inq[e.to]=1;
                            q.push(e.to);
                        }
                    }
                }
            }
            return dist[T]<INT_MAX;
        };

        while(spfa()){
            // In this problem, each augmenting path will have capacity 1
            // because all edges from left to right are capacity 1.
            int flow=1; 
            minCost+=dist[T]*flow;

            // Update the edges along the path
            int v=T;
            while(v!=S){
                auto [u,i]=parent[v];
                g[u][i].cap -= flow;
                g[v][g[u][i].rev].cap += flow;
                v=u;
            }
        }

        return minCost;
    }
};