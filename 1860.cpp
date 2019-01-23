#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct edge{
    int to;
    double rate, conf;
    edge(){}
    edge(int to, double rate, double conf){
        this->to = to; 
        this->rate = rate; 
        this->conf = conf;
    }
};
int n, m, s;
double v;
vector<edge> G[110];
double max_cash[110];
bool bellmanFord(int s, double fv){
    bool isok = false;
    memset(max_cash, 0, sizeof(max_cash));
    max_cash[s] = fv;
    for(int i=1; i<n; i++){
        for(int j=1; j<=n; j++){
            int num_next = G[j].size();
            edge tmp;
            int u, v;
            double ruv, cuv;
            for(int k=0; k<num_next; k++){
                tmp = G[j][k];
                u = j;
                v = tmp.to;
                ruv = tmp.rate;
                cuv = tmp.conf;
                max_cash[v] = max(max_cash[v], (max_cash[u] - cuv) * ruv);
            }
        }
    }
    for(int i=1; i<=n; i++){
        int num_next = G[i].size();
        edge tmp;
        int u, v; double ruv, cuv;
        for(int j=0; j<num_next; j++){
            tmp = G[i][j];
            u = i; v = tmp.to; ruv = tmp.rate; cuv = tmp.conf;
            if(max_cash[v] < (max_cash[u] - cuv) * ruv){
                isok = true;
                break;
            }
        }
        if(isok) break;
    }
    return isok;
}
int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d %d %d %lf", &n, &m, &s, &v);
    for(int i=0; i<m; i++){
        int ka, kb;
        double rab, cab, rba, cba;
        scanf("%d %d %lf %lf %lf %lf", &ka, &kb, &rab, &cab, &rba, &cba);
        G[ka].push_back(edge(kb, rab, cab));
        G[kb].push_back(edge(ka, rba, cba));
    }
    if(bellmanFord(s, v)) printf("YES");
    else printf("NO");
    return 0;
}
