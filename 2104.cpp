#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n, m;
int num[100010];
int sorted_num[100010];
int b[100010];
int seq[100010];
int qi, qj, qk;
struct node{
    int *p;
    int l, r, len;
    node(){
        p = NULL;
    }
}tree[800040];
int gl, gr, ans;


int init(){
    for(int i=1; i<=n; i++)
        seq[i] = i;
    for(int i=0; i<n; i++)
        sorted_num[i] = num[i];
    sort(sorted_num, sorted_num+n);
    int *pe = unique(sorted_num, sorted_num+n);
    for(int i=0; i<n; i++)
        b[i+1] = upper_bound(sorted_num, pe, num[i]) - sorted_num;
    return pe - sorted_num;
}

void build_tree(int now_node, int now_l, int now_r){
    tree[now_node].l = now_l;
    tree[now_node].r = now_r;
    tree[now_node].p = new int[now_r-now_l+2];
    tree[now_node].len = now_r - now_l + 1;
    if(now_l == now_r){
        *tree[now_node].p = b[now_l];
    }else{
        int mid = (now_l+now_r)/2;
        build_tree(now_node*2, now_l, (now_l+now_r)/2);
        build_tree(now_node*2+1, (now_l+now_r)/2+1, now_r);
        int *p0 = tree[now_node].p, *p1 = tree[now_node*2].p, *p2 = tree[now_node*2+1].p;
        int l1 = mid - now_l + 1, l2 = now_r - mid;
        int i, j;
        for(i=0, j=0; i<l1&&j<l2;){
            if(p1[i]<=p2[j]){
                p0[i+j] = p1[i];
                ++i;
            }else{
                p0[i+j] = p2[j];
                ++j;
            }
        } 
        while(i<l1){
            p0[i+j] = p1[i];
            ++i;
        }
        while(j<l2){
            p0[i+j] = p2[j];
            ++j;
        }
   }
    return;
}


int cal_le(int id, int now_l, int now_r, int num){
    int ret;
    if(tree[id].l == now_l && tree[id].r == now_r)
        ret = upper_bound(tree[id].p, tree[id].p + tree[id].len, num) - tree[id].p;
    else{
        int mid = (tree[id].l + tree[id].r) / 2;
        if(now_r <= mid)
            ret = cal_le(id*2, now_l, now_r, num);
        else if(now_l >= mid+1)
            ret = cal_le(id*2+1, now_l, now_r, num);
        else 
            ret = cal_le(id*2, now_l, mid, num) + cal_le(id*2+1, mid+1, now_r, num);
    }
    return ret;
}


int main(){
    freopen("out.txt", "w", stdout);
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++)
        scanf("%d", &num[i]);
    gl = 1;
    gr = init();
    build_tree(1, gl, gr);
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &qi, &qj, &qk);
        int local_l = gl, local_r = gr, mid;
        while(local_l < local_r){
            mid = local_l + (local_r - local_l) / 2;
            if(cal_le(1, qi, qj, mid) < qk)
                local_l = mid + 1;
            else local_r = mid;
        }
        ans = local_l;
        printf("%d\n",sorted_num[ans-1]);
    }
    return 0;
}