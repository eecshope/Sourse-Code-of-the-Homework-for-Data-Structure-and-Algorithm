#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n, node_num;
char s[5050];


int char2int(char c){
    if(c=='A') return 0;
    else if(c=='G') return 1;
    else if(c=='C') return 2;
    else return 3;
}

struct node{
    char val;
    node* has_son[4];
    bool is_danger;
    node *p_prev;
    node(){
        val = '0';
        for(int i=0; i<4; i++)
            has_son[i] = NULL;
        p_prev = NULL;
        is_danger = false;
    }
    void clear(){
        val = '0';
        for(int i=0; i<4; i++){
            if(has_son[i]!=NULL){
                has_son[i]->clear();
                has_son[i]=NULL;
            }
        }
        is_danger = false;
        p_prev = NULL;
        return;
    }
}ac_m[1050];

void build_trie(int n, node *chart){
    for(int i=0; i<4; i++)
        chart[0].has_son[i] = chart+1;
    chart[1].p_prev = chart;
    chart[1].val = '1';
    node_num = 2;
    for(int i=0; i<n; i++){
        node *p = chart + 1;
        int l_str;
        scanf("%s", s);
        l_str = strlen(s);
        for(int j=0; j<l_str; j++){
            if(p->has_son[char2int(s[j])]!=NULL)
                p = p->has_son[char2int(s[j])];
            else{
                p->has_son[char2int(s[j])] = chart + node_num;
                p = chart + node_num;
                p->val = s[j];
                ++node_num;
            }
            if(j==l_str-1)
                p->is_danger = true;
        }
    }
}

queue <node*> que;
void bfs(node *head){
    node *p = NULL;
    que.push(head);
    while(!que.empty()){
        p = que.front();
        que.pop();
        //printf("%c %c\n", p->val, p->p_prev->val);
        for(int i=0; i<4; i++){
            if(p->has_son[i]!=NULL){
                que.push(p->has_son[i]);
                node *son = p->has_son[i];
                node *fail = p->p_prev;
                while(fail->has_son[i]==NULL)
                    fail = fail->p_prev;
                son->p_prev = fail->has_son[i];
                if(son->p_prev->is_danger==true)
                    son->is_danger = true;
            }
        }
    }
    return;
}

int dp[1010][1010];  // dim 1: the length of the prefix; dim 2: the id of the point in AC Machine
void solve(char *s, node *head){
    memset(dp, 10, sizeof(dp));
    dp[0][1] = 0;
    int str_l = strlen(s);
    for(int i=0; i<str_l; i++)
    for(int j=1; j<node_num; j++){
        node *p = NULL;
        node *son = NULL;
        for(int k=0; k<4; k++){
            p = head + j;
            while(p->has_son[k]==NULL)
                p = p->p_prev;
            son = p->has_son[k];
            if(son->is_danger==false)
                dp[i+1][son-head] = min(dp[i+1][son-head], dp[i][j] + (char2int(s[i])!=k));
        }
    }
}
int ans;
int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    int Case = 0;
    while(scanf("%d", &n)&&n!=0){
        Case ++;
        build_trie(n, ac_m);
        bfs(ac_m+1);
        scanf("%s", s);
        solve(s, ac_m);
        ans = 0x7fff;
        int l_str = strlen(s);
        for(int i=1; i<node_num; i++)
            ans = min(ans, dp[l_str][i]);
        /*
        for(int i=0; i<=l_str; i++){
            for(int j=0; j<node_num; j++)
                printf("%d ", dp[i][j]);
            printf("\n");
        }
        */
        if(ans==0x7fff)
            printf("Case %d: -1\n", Case);
        else printf("Case %d: %d\n", Case, ans);
        ac_m->clear();
        node_num = 0;
    }
        return 0;
}