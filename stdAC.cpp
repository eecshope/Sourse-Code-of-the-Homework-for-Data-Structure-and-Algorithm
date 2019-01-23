#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct node{
    char val;
    node* has_son[26];
    bool is_danger;
    node *p_prev;
    node(){
        val = '0';
        for(int i=0; i<26; i++)
            has_son[i] = NULL;
        p_prev = NULL;
        is_danger = false;
    }
    int char2int(char c){
        return (int)(c-'a');
    }
};
node* head;
int n, m;
char s[1010];
queue <node*> que;

void buildTrie(char *s){
    int str_l = strlen(s);
    node *p = head, *son;
    for(int i=0; i<str_l; i++){
        if(p->has_son[s[i]-'a']==NULL)
            p->has_son[s[i]-'a'] = new node();
        son = p->has_son[s[i]-'a'];
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
        if(p->has_son[s[ps]-'a']!=NULL){
            p = p->has_son[s[ps]-'a'];
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


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    scanf("%d", &n);
    head = new node;
    for(int i=0; i<n; i++){
        scanf("%s", s);
        buildTrie(s);
    }
    bfs(head);
    scanf("%d", &m);
    for(int i=0; i<m; i++){
        scanf("%s", s);
        if(match(s, head))
            printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}