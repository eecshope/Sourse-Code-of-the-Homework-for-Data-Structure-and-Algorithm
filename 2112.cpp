#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define maxl 1<<25;
struct edge{
    int to, cap, rev;
    edge(){}
    edge(int to, int cap, int rev): to(to), cap(cap), rev(rev) {}
};
vector<edge> G[250];
int dist[250][250];
int k, c, m;
bool used[250];

void floyd(){
    for(int r=1; r<=k+c; r++)
    for(int p=1; p<=k+c; p++)
    for(int q=1; q<=k+c; q++)
        dist[p][q] = min(dist[p][q], dist[p][r]+dist[r][q]);
    return;
}


void add_edge(int from, int to, int cap){
    G[from].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(from, 0, G[from].size()-1));
}


int dfs(int v, int t, int f){
    if(v==t) return f;
    used[v] = true;
    for(int i=0; i<G[v].size(); i++){
        edge &e = G[v][i];
        if(!used[e.to] && e.cap>0){
            int d = dfs(e.to, t, min(f, e.cap));
            if(d>0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}


int max_flow(int s, int t){
    int flow = 0;
    for(;;){
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, 1<<25);
        if(f==0) return flow;
        flow += f;
    }
}


bool check(int maxlen){
    for(int i=0; i<=k+c+1; i++)
        G[i].clear();
    for(int i=k+1; i<=k+c; i++)
        add_edge(0, i, 1);
    for(int i=k+1; i<=k+c; i++){
        for(int j=1; j<=k; j++){
            if(dist[i][j]<=maxlen){
                add_edge(i, j, 1);
            }
        }
    }
    for(int i=1; i<=k; i++)
        add_edge(i, k+c+1, m);
    int flow = max_flow(0, k+c+1);
    if(flow==c)
        return true;
    else return false;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d %d %d", &k, &c, &m);
    for(int i=1; i<=k+c; i++)
    for(int j=1; j<=k+c; j++){
        int tmp;
        scanf("%d", &tmp);
        if(tmp!=0||(tmp==0&&i==j))
            dist[i][j] = tmp;
        else dist[i][j] = maxl;
    }
    floyd();
    int l=0, r=0;
    for(int i=1; i<=k+c; i++)
    for(int j=1; j<=k+c; j++)
        r = max(dist[i][j], r);
    while(l<r){
        int mid = (l+r)/2;
        if(check(mid))
            r = mid;
        else l = mid+1;
    }
    printf("%d", r);
    return 0;
}