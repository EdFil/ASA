#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>

#define NIL 0
#define INF (1<<28)

using namespace std;

int n, m, *match, *dist;
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]

bool bfs(vector<int> *G) {
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) {
        if(match[i]==NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=NIL) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[match[v]]==INF) {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool dfs(int u, vector<int> *G) {
    int i, v, len;
    if(u!=NIL) {
        len = G[u].size();
        for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[match[v]]==dist[u]+1) {
                if(dfs(match[v], G)) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp(vector<int> *G) {
    int matching = 0, i;
    // match[] is assumed NIL for all vertex in G
    while(bfs(G))
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i, G))
                matching++;
    return matching;
}

int main(){
    int studentJobs, jobNumber, maxSize, answer;

    scanf("%d%d", &n, &m);
    maxSize = n+m+1;
    vector<int> G[maxSize];
    match = new int[maxSize];
    memset(match, NIL, sizeof(maxSize));
    dist = new int[maxSize];
    memset(dist, NIL, sizeof(maxSize));

    for(int i = 1; i <=  n; i++){
        scanf("%d", &studentJobs);
        for(int j = 0; j < studentJobs; j++){
            scanf("%d", &jobNumber);
            G[i].push_back(jobNumber+n+1);
            G[jobNumber+n+1].push_back(i);
        }
    }

    answer = hopcroft_karp(G);
    printf("%d\n", answer);
}
