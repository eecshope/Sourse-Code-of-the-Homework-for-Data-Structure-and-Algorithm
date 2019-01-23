#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> nodes;//中根+后根
int tree_size;
int output_num;
struct node{
    int val;
    node *lc;
    node *rc;
    node(){lc=NULL; rc=NULL;}
    ~node(){
        if(this->lc!=NULL)
            delete this->lc;
        if(this->rc!=NULL)
            delete this->rc;
        this->lc = NULL;
        this->rc = NULL;
    }
};
node *root;

void input(){
    int node_num;
    while(scanf("%d", &node_num)!=EOF)
        nodes.push_back(node_num);
    tree_size = nodes.size() >> 1; 
}

void build_tree(node* r, int ml, int mr, int bl, int br){
    int tar = ml, root_val = nodes[br];
    r->val = root_val;
    while(nodes[tar]!=root_val)
        ++tar;
    if(ml<=tar-1){
        r->lc = new node;
        build_tree(r->lc, ml, tar-1, bl, bl+(tar-ml)-1);
    }
    if(tar+1<=mr){
        r->rc = new node;
        build_tree(r->rc, tar+1, mr, bl+tar-ml, br-1);
    }   
    return;
}

void front_visit(node *r){
    ++output_num;
    printf("%d", r->val);
    if(output_num<tree_size)
        printf(" ");
    if(r->lc!=NULL)
        front_visit(r->lc);
    if(r->rc!=NULL)
        front_visit(r->rc);
    return;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    input();
    root = new node;
    build_tree(root, 0, tree_size-1, tree_size, (tree_size<<1)-1);
    output_num = 0;
    front_visit(root);
    delete root;
    return 0;
}