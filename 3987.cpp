#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct node{
    char val;
    node* has_son[26];
    bool is_danger;
    bool is_vis;
    node *p_prev;
    node(){
        val = '0';
        for(int i=0; i<26; i++)
            has_son[i] = NULL;
        p_prev = NULL;
        is_danger = false;
        is_vis = false; 
    }
    ~node(){
        p_prev = NULL;
        for(int i=0; i<26; i++){
            if(has_son[i]!=NULL){
                delete has_son[i];
                has_son[i] = NULL;
            }
        }
    }
    int char2int(char c){
        return (int)(c-'a');
    }
};
node* head;
int n, m;
char s[5100010];
char tars[5100010];
queue <node*> que;
int testcase;

void buildTrie(char *s){
    int str_l = strlen(s);
    node *p = head, *son;
    for(int i=0; i<str_l; i++){
        if(p->has_son[s[i]-'A']==NULL)
            p->has_son[s[i]-'A'] = new node();
        son = p->has_son[s[i]-'A'];
        son->val = s[i];
        if(i==str_l-1)
            son->is_danger = true;            
        else 
            p = son;
    }
}

void bfs(node *head){
    node *p = head, *son, *prev;
    que.push(p);
    while(!que.empty()){
        node *front = que.front();
        que.pop();
        for(int i=0; i<26; i++){
            if(front->has_son[i]!=NULL){
                que.push(front->has_son[i]);
                son = front->has_son[i];
                prev = front->p_prev;
                while(prev!=NULL && prev->has_son[i]==NULL)
                    prev = prev->p_prev;
                if(prev==NULL)
                    son->p_prev = p;
                else 
                    son->p_prev = prev->has_son[i]; 
            }
        }
    }
}


int match(char *s, node *head){
    int ret = 0;
    int ps = 0, l = strlen(s);
    node *p = head;
    while(ps < l){
        if(p->has_son[s[ps]-'A']!=NULL){
            p = p->has_son[s[ps]-'A'];
            ++ps;
            for(node *tmp=p; tmp!=head&&tmp->is_vis==false; tmp=tmp->p_prev){
                if(tmp->is_danger==true)
                    ret++;
                tmp->is_vis = true;
            }
        }else{
            p = p->p_prev;
            if(p==NULL){
                p = head;
                ++ps;
            }
        }
    }
    return ret;
}


void unPack(char *s, char *tars){
    int l = strlen(s),i, j;
    int p, q;
    bool isin = false;
    for(i=0, j=0; i<l; i++){
        if(isin){
            if(s[i]==']'){
                char cnum[10];
                for(int k=p; k<=q; k++)
                    cnum[k-p] = s[k];
                int r_num = atoi(cnum);
                for(int k=0; k<r_num; k++){
                    tars[j] = s[i-1];
                    j++;
                }
                isin = false;
            }
            else if(s[i]>='A'&&s[i]<='Z')
                q = i;
        }else{
            if(s[i]=='['){
                isin = true;
                p = i + 1;
                q = i + 1;
            }
            else{
                tars[j] = s[i];
                j++;
            }
        }
    }
    tars[j] = '\0';
    return;
}

void Reverse(char *s,int n){
    for(int i=0,j=n-1;i<j;i++,j--){
        char c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}

int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d", &testcase);
    while(testcase--){
        scanf("%d", &n);
        head = new node;
        for(int i=0; i<n; i++){
            scanf("%s", s);
            buildTrie(s);
        }
        bfs(head);
        scanf("%s", s);
        unPack(s, tars);
        int ans = 0;
        ans += match(tars, head);
        Reverse(tars, strlen(tars));
        ans += match(tars, head);
        printf("%d\n", ans);
        delete head;
    }
       return 0;
}