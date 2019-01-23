#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
struct edge{
    int to, val;
    edge(){to=0; val=0;}
    edge(int _to, int _val){this->to=_to; this->val=_val;}
};
bool isvis[1010];
int num_edge[1010][1010];
int n, m, tc, ans;  //n islands, m bridges, n<=1000, 1<=x<=n
int dfn[1010], low[1010];
vector<edge> G[1010];


void init(){
    for(int i=1; i<=n; i++)
        G[i].clear();
    memset(dfn, 255, sizeof(dfn));
    memset(low, 255, sizeof(low));
    memset(num_edge, 0, sizeof(num_edge));
    tc = 0;
    ans = -1;
}

void input(){
    int u, v, k;
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &u, &v, &k);
        ++num_edge[u][v];
        ++num_edge[v][u];
        G[u].push_back(edge(v, k));
        G[v].push_back(edge(u, k));
    }
}


void dfs(int now_node, int father){
    isvis[now_node] = true;
    dfn[now_node] = low[now_node] = tc++;
    int num_child, next_node, num_soldier;
    num_child = G[now_node].size();
    for(int i=0; i<num_child; i++){
        edge e = G[now_node][i];
        next_node = e.to;
        num_soldier = e.val;
        if(!isvis[next_node]){
            dfs(next_node, now_node);
            low[now_node] = min(low[now_node], low[next_node]);
            if(dfn[now_node]<low[next_node]&&num_edge[now_node][next_node]==1){
                ans = (ans==-1) ? num_soldier : min(num_soldier, ans);
            }
        }else if(next_node!=father){
            low[now_node] = min(low[now_node], dfn[next_node]);
        }
    }
}


void scc(){
    bool iscon = true;
    memset(isvis, 0, sizeof(isvis));
    for(int i=1; i<=n; i++){
        //printf("i:%d \n", i);
        if(!isvis[i]){
           if(i!=1){
               iscon = false;
               break;
           }
           dfs(i, -1);
        }
    }
    //printf("ans:%d\n", ans);
    //printf("%d", iscon);
    if(!iscon) ans = 0;
    else if(ans==0) ans = 1;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    while(scanf("%d %d", &n, &m), !(n==0&&m==0)){
        init();
        input();
        scc();
        //for(int i=1; i<=n; i++)
        //    printf("i:%d, dfn:%d, low:%d\n", i, dfn[i], low[i]);
        printf("%d\n", ans);
    }
    return 0;
}