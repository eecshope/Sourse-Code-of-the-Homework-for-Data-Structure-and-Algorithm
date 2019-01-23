#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int case_num;
int n;
struct node{
    int lb, rb;
    bool is_covered;
}tree[500000];
int l[100100], r[100100]; 
vector <int> points;


int init(){
   
    for(int i=0; i<n; i++)
        points.push_back(l[i]);
    for(int i=0; i<n; i++)
        points.push_back(r[i]);
    sort(points.begin(), points.end());
    vector<int>::iterator e = unique(points.begin(), points.end());
    int tree_r = e - points.begin();
    /*for(int i=1;i<=n;i++)
        arr[i]=lower_bound(xs.begin(),e,arr[i])-xs.begin()+1;*/
    for(int i=0; i<n; i++){
        l[i] = lower_bound(points.begin(), e, l[i]) - points.begin()+1;
        r[i] = lower_bound(points.begin(), e, r[i]) - points.begin()+1;
        --r[i];
    }
    points.clear();
    return tree_r;
}


void build_tree(int id, int lb, int rb){
    int mid = (lb+rb) / 2;
    tree[id].lb = lb;
    tree[id].rb = rb;
    tree[id].is_covered = false;
    if(lb!=rb){
        build_tree(id*2, lb, mid);
        build_tree(id*2+1, mid+1, rb);
    }
    return;
}


void cover(int id, int lb, int rb){
    int mid = (tree[id].lb+tree[id].rb) / 2;
    if(tree[id*2].is_covered&&tree[id*2+1].is_covered) 
        tree[id].is_covered = true;
    if(tree[id].is_covered==true) ;
    else if(lb==tree[id].lb&&rb==tree[id].rb)
        tree[id].is_covered = true;
    else if(rb<=mid)
        cover(id*2, lb, rb);
    else if(lb>mid)
        cover(id*2+1, lb, rb);
    else{
        cover(id*2, lb, mid);
        cover(id*2+1, mid+1, rb);
    }
    if(tree[id*2].is_covered&&tree[id*2+1].is_covered) 
       tree[id].is_covered = true;
    return;
}


bool request(int id, int lb, int rb){
       // if(tree[id*2].is_covered&&tree[id*2+1].is_covered) 
       // tree[id].is_covered = true; 在这里更新是不行的，因为有可能它需要更新需要好多层信息才能传上来，比如[1, 7]，[1 2]已更新，3和4s是翻开单独更新的，这时就隔了四层，需要
       // 在cover的时候就更新完毕
    //printf("%d %d\n", id, tree[id].is_covered);
    int mid = (tree[id].lb+tree[id].rb) / 2;
    bool ret;
    if(tree[id].is_covered==true) ret = true;
    else if(lb==tree[id].lb&&rb==tree[id].rb)
        ret = tree[id].is_covered;
    else if(rb<=mid)
        ret = request(id*2, lb, rb);
    else if(lb>mid)
        ret = request(id*2+1, lb, rb);
    else
        ret = request(id*2, lb, mid) && request(id*2+1, mid+1, rb);
      
    return ret;
}


int main(){
    freopen("ans.txt", "w", stdout);
    scanf("%d", &case_num);
    while(case_num--){
        scanf("%d", &n);
        for(int i=0; i<n; i++){
            scanf("%d %d", &l[i], &r[i]);
            ++r[i];
        }
        int tree_r = init();
        int ans = 0;
        build_tree(1, 1, tree_r);
        for(int i=n-1; i>=0; i--){;
            //printf("l:%d r:%d\n", l[i], r[i]);
            //printf("id:%d\n", i);
            if(request(1, l[i], r[i])==false) 
               ans++;
            cover(1, l[i], r[i]);
        }
        printf("%d\n", ans);
    }
}
