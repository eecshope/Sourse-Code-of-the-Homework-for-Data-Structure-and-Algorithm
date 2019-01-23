#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
char expr[55], front_seq[55], back_seq[55];
int len_seq, num_var, stack_p, max_height;
char graph_tree[50][5000];
int c2int[30];
struct node{
    char c;
    int height;
    node *lp;
    node *rp;
    node(){lp=NULL; rp=NULL;}
    ~node(){
        if(this->lp!=NULL)
            delete this->lp;
        if(this->rp!=NULL)
            delete this->rp;
        this->lp = NULL;
        this->rp = NULL;
    }
};
node *root;


int rk(char op){
    if(op=='*'||op=='/')
        return 2;
    else return 1;
}

void input(){
    scanf("%s", expr);
    scanf("%d\n", &num_var);
    for(int i=0; i<num_var; i++){
        char tmpc;
        int tmpv;
        scanf("%c %d\n", &tmpc, &tmpv);
        c2int[tmpc-'a'] = tmpv;
    }
}
stack<char> op_stack;
void mid2bak(){
    int len_ori = strlen(expr);
    len_seq = 0;
    for(int i=0; i<len_ori; i++){
        if(expr[i]>='a'&&expr[i]<='z')
            back_seq[len_seq++] = expr[i];
        else if(expr[i]=='(')
            op_stack.push('(');
        else if(expr[i]==')'){
            while(op_stack.top()!='('){
                char tmp = op_stack.top();
                op_stack.pop();
                back_seq[len_seq++] = tmp;
            }
            op_stack.pop();
        }else{
            while(!op_stack.empty()&&op_stack.top()!='('&&rk(op_stack.top())>=rk(expr[i])){
                char tmp = op_stack.top();
                op_stack.pop();
                back_seq[len_seq++] = tmp;
            }
            op_stack.push(expr[i]);
        }
    }
    while(!op_stack.empty()){
        char tmp = op_stack.top();
        op_stack.pop();
        back_seq[len_seq++] = tmp;
    }
    back_seq[len_seq] = '\0';
}
int rightest[20];
int build_tree(node* p, int h){
    char val = back_seq[stack_p--];
    p->c = val;
    p->height = h;
    max_height = max(h, max_height);
    if(val>='a'&&val<='z')
        return c2int[val-'a'];
    else{
        p->lp = new node;
        p->rp = new node;
        int valr = build_tree(p->rp, h+1);
        int vall = build_tree(p->lp, h+1);
        if(p->c=='+') return vall + valr;
        if(p->c=='-') return vall - valr;
        if(p->c=='*') return vall * valr;
        if(p->c=='/') return vall / valr;
    }
}

void make_graph(node* r, int row, int col){
   rightest[row] = max(rightest[row], col);
   graph_tree[row][col] = r->c;
   if(r->lp!=NULL){
       graph_tree[row+1][col-1] = '/';
       rightest[row+1] = max(rightest[row+1], col-1);
       make_graph(r->lp, row+2, col-(1<<(max_height-r->height-1)));
   }
   if(r->rp!=NULL){
       graph_tree[row+1][col+1] = '\\';
       rightest[row+1] = max(rightest[row+1], col+1);
       make_graph(r->rp, row+2, col+(1<<(max_height-r->height-1)));
   } 
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    input();
    mid2bak();
    printf("%s\n", back_seq);
    root = new node;
    stack_p = len_seq - 1;
    max_height = -1;
    int ans = build_tree(root, 0);
    memset(graph_tree, 0, sizeof(graph_tree));
    memset(rightest, 255, sizeof(rightest));
    make_graph(root, 0, (1<<max_height)-1);
    for(int i=0; i<=2*max_height; i++){
        for(int j=0; j<=rightest[i]; j++){
            if(graph_tree[i][j]==0)
                printf(" ");
            else printf("%c", graph_tree[i][j]);
        }
        printf("\n");
    }
    printf("%d", ans);
    delete root;
    return 0;
}