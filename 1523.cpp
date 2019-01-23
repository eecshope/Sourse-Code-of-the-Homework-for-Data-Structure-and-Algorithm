#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int num_node;
int ans;
int time_step;
int dfn[1010], low[1010];
bool isvis[1010];
vector<int>G[1010];
struct mypair{
    int no, num_slices;
    mypair(){}
    mypair(int _no, int _num_slices){
        this->no = _no; this->num_slices = _num_slices;
    }
    bool operator < (const mypair &a) const{
        return this->no < a.no;
    }
};
vector<mypair>ans_list;
vector<int> tree_edge;

void tarjan(int u, int f){// points indexed from 1, so let 0 be the father of node 1
    isvis[u] = true;
    dfn[u] = time_step;
    low[u] = time_step;
    ++time_step;
    int v, num_next = G[u].size(), num_subtree = 0;;
    for(int i=0; i<num_next; i++){
        v = G[u][i];
        if(v!=f&&!isvis[v]){
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v]>=dfn[u])
                ++num_subtree;
        }else if(v!=f)
            low[u] = min(low[u], dfn[v]);
    }
    if(f==0 && num_subtree>=2)
        ans_list.push_back(mypair(u, num_subtree));
    else if(f!=0){
        bool isok = false;
        for(int i=0; i<num_next; i++){
            v = G[u][i];
            if(dfn[u]<=low[v]){
                isok = true;
                break;
            }
        }
        if(isok)
           ans_list.push_back(mypair(u, num_subtree+1));
    } 
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    int u, v;
    int test_case = 0;
    while(scanf("%d", &u), u!=0){
        ++test_case;
        scanf("%d", &v);
        num_node = 0;
        num_node = max(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
        while(scanf("%d", &u), u!=0){
            scanf("%d", &v);
            G[u].push_back(v);
            G[v].push_back(u);
            u = max(u, v);
            num_node = max(num_node, u);
        }
        memset(isvis, 0, sizeof(isvis));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        time_step = 1;
        ans = -1;
        for(int i=1; i<=num_node; i++){
            if(!isvis[i]){
                ++ans;
                tarjan(i, 0);
            }
        }
        sort(ans_list.begin(), ans_list.end());
        printf("Network #%d\n", test_case);
        if(ans_list.size()!=0)
            for(int i=0; i<ans_list.size(); i++)
                printf("  SPF node %d leaves %d subnets\n", ans_list[i].no, ans_list[i].num_slices+ans);
        else 
            printf("  No SPF nodes\n");
        printf("\n");
        for(int i=1; i<=num_node; i++)
            G[i].clear();
        ans_list.clear();
    }
    return 0;
}