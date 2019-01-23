#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n, m, num_block, ans;
int cmp[10010];
vector<int> G[10010];
vector<int> rG[10010];
vector<int> top;
bool isvis[10010];

void dfs(int this_node){
    isvis[this_node] = true;
    int num_child = G[this_node].size();
    for(int i=0; i<num_child; i++){
        if(!isvis[G[this_node][i]])
            dfs(G[this_node][i]);
    }
    top.push_back(this_node);
    return;
}


void rdfs(int this_node, int block_id){
    isvis[this_node] = true;
    cmp[this_node] = block_id;
    int num_child = rG[this_node].size();
    for(int i=0; i<num_child; i++){
        if(!isvis[rG[this_node][i]])
            rdfs(rG[this_node][i], block_id);
    }
    return;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        rG[v].push_back(u);
    }
    memset(isvis, 0, sizeof(isvis));
    for(int i=1; i<=n; i++){
        if(!isvis[i])
            dfs(i);
    }
    memset(isvis, 0, sizeof(isvis));
    num_block = 0;
    for(int i=n-1; i>=0; i--){
        if(!isvis[top[i]]){
            rdfs(top[i], num_block);
            ++num_block;
        }
    } 
    ans = 0;
    int test_node = -1;
    for(int i=1; i<=n; i++){
        if(cmp[i]==num_block-1){
            ++ans;
            test_node = i;
        }
    }
    memset(isvis, 0, sizeof(isvis));
    rdfs(test_node, -1);
    for(int i=1; i<=n; i++){
        if(cmp[i]!=-1){
            ans = 0;
            break;
        }
    }
    printf("%d", ans);
    return 0;
}