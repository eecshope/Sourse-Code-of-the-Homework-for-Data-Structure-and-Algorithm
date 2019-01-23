#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct edge{
    int to, cap, rev;
    edge(){}
    edge(int to, int cap, int rev): to(to), cap(cap), rev(rev) {}
};
vector<edge> G[500];
int n, m;
bool used[500];


void add_edge(int from, int to, int cap){
    G[from].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(from, 0, G[from].size()-1));
}


int dfs(int v, int t, int f){
    if(v==t) return f;
    used[v] = true;
    for(int i=0; i<G[v].size(); i++){
        edge &e = G[v][i];
        if(!used[e.to]&&e.cap>0){
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
        else flow += f;
    }
}

int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    while(scanf("%d %d", &n, &m)!=EOF){
        for(int i=0; i<=n+m+1; i++)
            G[i].clear();
        for(int i=1; i<=n; i++)
            add_edge(0, i, 1);
        for(int i=1; i<=n; i++){
            int num_s, id_s;
            scanf("%d", &num_s);
            for(int j=0; j<num_s; j++){
                scanf("%d", &id_s);
                add_edge(i, n+id_s, 1);
            }
        }
        for(int i=1; i<=m; i++){
            add_edge(n+i, n+m+1, 1);
        }
        printf("%d\n", max_flow(0, n+m+1));
    }
    return 0;
}