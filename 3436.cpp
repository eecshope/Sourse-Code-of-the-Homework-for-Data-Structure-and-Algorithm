#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct edge{
    int to, cap, rev, ori_cap;
    bool isrev;
    edge(){}
    edge(int to, int cap, int rev, bool isrev): to(to), cap(cap), ori_cap(cap), rev(rev), isrev(isrev) {};
};
bool isvis[55];
int p, n, q, ans;
int in[55][15];
int out[55][15];
int node_cap[55];
vector<edge> G[55];
int ans_pairs[10000][3];

bool match(int a, int b){
    bool ret = true;
    for(int i=0; i<p; i++){
        if(out[a][i]!=in[b][i]&&in[b][i]!=2){
            ret = false;
            break;
        }
    }
    return ret;
}


void add_edge(int from, int to, int cap){
    G[from].push_back(edge(to, cap, G[to].size(), false));
    G[to].push_back(edge(from, 0, G[from].size()-1, true));
}


void make_graph(){
    for(int i=1; i<=n; i++){
        bool isok = true;
        for(int j=0; j<p; j++)
            if(in[i][j]==1){
                isok = false;
                break;
            }
        if(isok)
            add_edge(0, i, node_cap[i]);
        add_edge(i, i+n, node_cap[i]);
    }
        
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++){
        if(i!=j&&match(i, j))
            add_edge(i+n, j, max(node_cap[i], node_cap[j]));
    }

    for(int i=1; i<=n; i++){
        bool isok = true;
        for(int j=0; j<p; j++)
            if(out[i][j]!=1){
                isok = false;
                break;
            }
        if(isok)
            add_edge(i+n, 2*n+1, node_cap[i]);
    }
}


int dfs(int v, int t, int f){
    if(v==t) return f;
    isvis[v] = true;
    for(int i=0; i<G[v].size(); i++){
        edge &e = G[v][i];
        if(!isvis[e.to] && e.cap>0){
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
        memset(isvis, 0, sizeof(isvis));
        int f = dfs(s, t, 100000);
        if(f==0) return flow;
        flow += f;
    }
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d %d", &p, &n);
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    for(int i=1; i<=n; i++){
        scanf("%d", &node_cap[i]);
        for(int j=0; j<p; j++)
            scanf("%d", &in[i][j]);
        for(int j=0; j<p; j++)
            scanf("%d", &out[i][j]);
    }
    make_graph();
    ans = max_flow(0, 2*n+1);
    int cnt=0;
   
    for(int i=1; i<=n; i++){
        for(int j=0; j<G[i+n].size(); j++){
            edge &e = G[i+n][j];
            if(e.to!=i+n&&e.to!=2*n+1&&e.cap<e.ori_cap){
                ans_pairs[cnt][0] = i;
                ans_pairs[cnt][1] = e.to;
                ans_pairs[cnt++][2] = e.ori_cap - e.cap;
            }
        }
    }
    printf("%d %d\n", ans, cnt);
    for(int i=0; i<cnt; i++)
        printf("%d %d %d\n", ans_pairs[i][0], ans_pairs[i][1], ans_pairs[i][2]);
    return 0;
}