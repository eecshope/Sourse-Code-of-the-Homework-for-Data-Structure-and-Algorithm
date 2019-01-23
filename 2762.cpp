#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<queue>
using namespace std;
bool isvis[1010];
int cases;
int n, m, num_mem;
int degree[1010], mem[1010];
set <int> has_edge[1010]; 
vector<int> G[1010];
vector<int> rG[1010];
vector<int> new_G[1010];
vector<int> seq;
queue<int> que;

void dfs(int now_node){
    isvis[now_node] = true;
    int num_child = G[now_node].size(), next_node;
    for(int i=0; i<num_child; i++){
        next_node = G[now_node][i];
        if(!isvis[next_node])
            dfs(next_node);
    }
    seq.push_back(now_node);
    return;
}


void rdfs(int now_node, int id_mem){
    isvis[now_node] = true;
    mem[now_node] = id_mem;
    int num_child = rG[now_node].size(), next_node;
    for(int i=0; i<num_child; i++){
        next_node = rG[now_node][i];
        if(!isvis[next_node])
            rdfs(next_node, id_mem);
    }
    return;
}


void korasaju(){
    memset(isvis, 0, sizeof(isvis));
    for(int i=1; i<=n; i++){
        if(!isvis[i])
            dfs(i);
    }
    memset(isvis, 0, sizeof(isvis));
    memset(mem, 255, sizeof(mem));
    num_mem = 0;
    for(int i=n-1; i>=0; i--){
        if(!isvis[seq[i]]){
            ++num_mem;
            rdfs(seq[i], num_mem);
        }
    }
}


void buildNew(){
    for(int i=1; i<=n; i++){
        int num_child  = G[i].size(), k;
        set<int>::iterator jud;
        for(int j=0; j<num_child; j++){
            int k = G[i][j];  // <i, k>, k is the (j+1)th child of i
            if(mem[i]==mem[k])
                continue;
            jud = has_edge[mem[i]].find(mem[k]);
            //printf("%d %d\n", mem[i], mem[k]);
            if(jud==has_edge[mem[i]].end()){
                new_G[mem[i]].push_back(mem[k]);
                has_edge[mem[i]].insert(mem[k]);
                ++degree[mem[k]];
            } 
        }
    }
}


bool top(){
    bool ret = true;
    while(!que.empty())
        que.pop();
    for(int i=1; i<=num_mem; i++){
        if(degree[i]==0){
            que.push(i);
        }
    }
    while(!que.empty()){
        /*for(int i=1; i<=num_mem ;i++)
            printf("%d ", degree[i]);
        printf("\n");*/
        if(que.size()>1){
            //printf("break point:%d\n", que.front());
            ret = false;
            break;
        }
        int now_node = que.front();
        degree[now_node] = -1;
        que.pop();
        int num_child = new_G[now_node].size();
        for(int i=0; i<num_child; i++){
            int next_node = new_G[now_node][i];
            if(degree[next_node]==-1) 
                continue;
            --degree[next_node];
            if(degree[next_node]==0){
                que.push(next_node);
            }
        }
    }
    return ret;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d", &cases);
    while(cases--){
        scanf("%d %d", &n, &m);
        memset(degree, 0, sizeof(degree));
        for(int i=1; i<=n; i++){
            G[i].clear();
            rG[i].clear();
            has_edge[i].clear();
            new_G[i].clear();
        }
        seq.clear();
        for(int i=0; i<m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            rG[v].push_back(u);
        } 
        korasaju();
        buildNew();
        /*for(int i=1; i<=n; i++)
            printf("node:%d's color is %d\n", i, mem[i]);
        for(int i=1; i<=num_mem; i++){
            printf("%d: ", i);
            for(int j=0; j<new_G[i].size(); j++)
                printf("%d ", new_G[i][j]);
            printf("\n");
        }*/
        bool ans = top();
        if(ans)
            printf("Yes\n");
        else 
            printf("No\n");
    }
    return 0;
}