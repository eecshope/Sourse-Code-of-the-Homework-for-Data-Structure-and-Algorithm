#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
struct edge{
    int from, to;
    double cost;
    edge(){}
    edge(int from, int to, double cost) : from(from), to(to), cost(cost){};
};
vector<edge> E;
int vis[105]; //isvis
int n, m;
int loc[105][2];
int pre[105]; //father point
int id[105];  // the circle id of each point
double in[105];  // the min weight of the in edge.

inline double Dist(int idu, int idv){
    double dx = loc[idu][0] - loc[idv][0];
    double dy = loc[idu][1] - loc[idv][1];
    return sqrt(dx*dx + dy*dy);
}

double zlAlgorithm(int root){
    int u, v;
    double ret = 0.0;
    while(1){
        for(int i=1; i<=n; i++)
            in[i] = 999999999;
        for(int i=0; i<m; i++){
            edge &e = E[i];
            if(e.from!=e.to && e.cost < in[e.to]){
                pre[e.to] = e.from;
                in[e.to] = e.cost;
            }
        }
        for(int i=1; i<=n; i++){
            if(i!=root && in[i] == 999999999)
                return -1; // we have an unconnected point
        }//else find the circle
        int tn = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0; //set the root parameter
        for(int i=1; i<=n; i++){
            ret += in[i];
            v = i;
            while(vis[v]!=i && id[v]==-1 && v!=root){
                vis[v] = i;
                v = pre[v];
            }
            if(v!=root && id[v]==-1){
                for(int u=pre[v]; u!=v; u=pre[u])
                    id[u] = tn;
                id[v] = tn++;
            }
        }
        if(tn==0) break; //if there is no simple circle
        for(int i=1; i<=n; i++)
            if(id[i]==-1)
                id[i] = tn++;
        for(int i=0; i<m; i++){
            v = E[i].to;
            E[i].from = id[E[i].from];
            E[i].to = id[E[i].to];
            if(E[i].from!=E[i].to)
                E[i].cost -= in[v];
        }
        n = tn;
        root = id[root];
    }
    return ret;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d", &n);
    while(scanf("%d", &m)!=EOF){
        E.clear(); 
        for(int i=1; i<=n; i++)
            scanf("%d %d", &loc[i][0], &loc[i][1]);
        for(int i=0; i<m; i++){
            int idu, idv;
            scanf("%d %d", &idu, &idv);
            if(idu!=idv)
                E.push_back(edge(idu, idv, Dist(idu, idv)));
        }
            double ans = zlAlgorithm(1);
            if(ans==-1) printf("NO");
            else printf("%.2lf", ans);
            if(scanf("%d", &n)!=EOF)
                printf("\n");
    }
    return 0; 
}