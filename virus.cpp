#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct node{
    char val;
    node* has_son[26];
    bool is_danger;
    bool is_instack;
    node *p_prev;
    node(){
        val = 'a';
        for(int i=0; i<26; i++)
            has_son[i] = NULL;
        p_prev = NULL;
        is_danger = false;
        is_instack = false;
    }
    int char2int(char c){
        return (int)(c-'a');
    }
};
node* head;
int n;
char s[30010];
queue <node*> que;
bool ans;

void buildTrie(char *s, node *head){
    int str_l = strlen(s);
    node *p = head, *son;
    for(int i=0; i<str_l; i++){
        if(p->has_son[s[i]-'0']==NULL)
            p->has_son[s[i]-'0'] = new node();
        son = p->has_son[s[i]-'0'];
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
                if(son->p_prev->is_danger==true)
                    son->is_danger = true;
            }
        }
    }
}


bool match(char *s, node *head){
    int ps = 0, l = strlen(s);
    node *p = head;
    bool is_match = false;
    while(ps < l){
        if(p->has_son[s[ps]-'0']!=NULL){
            p = p->has_son[s[ps]-'0'];
            ++ps;
            if(p->is_danger){
                is_match = true;
                break;
            }
        }else{
            p = p->p_prev;
            if(p==NULL){
                p = head;
                ++ps;
            }
        }
    }
    return is_match;
}


bool dfs(node* p){
    node *son = NULL, *tmp = NULL;
    bool ret = false;
    p->is_instack = true;
    for(int i=0; i<2; i++){
        tmp = p;
        bool is_found = true;
        while(tmp!=NULL){
            if(tmp->has_son[i]!=NULL){
                if(tmp->has_son[i]->is_danger==false){
                    son = tmp->has_son[i];
                    break;
                }
                else{
                    is_found = false;
                    break;
                }
            }else tmp = tmp->p_prev;
        }
        if(is_found==false) continue;
        else{
            if(tmp==NULL) son = head;
            if(son->is_instack==true){
                ret = true;
                break;
            }else{
                ret = dfs(son);
                if(ret==true)
                    break;
            }
        }
    }
    p->is_instack = false;
    return ret;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    head = new node;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%s", s);
        buildTrie(s, head);
    }
    bfs(head);
    ans = dfs(head);
    if(ans==true) printf("TAK\n");
    else printf("NIE\n");
    return 0;
}