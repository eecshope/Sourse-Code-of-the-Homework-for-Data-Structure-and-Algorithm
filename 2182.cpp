#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node{
	int id;
	int l, r, mid, sum_cow, index_right;
}tree[500000];
int n, p[100050], b[100050];


void buildTree(int index, int l, int r){
	tree[index].id = index;
	tree[index].l = l;
	tree[index].r = r;
	tree[index].mid = (l+r)/2;
	tree[index].sum_cow = r - l + 1;
	tree[index].index_right = r;
	if(l==r) return;
	buildTree(index*2, l, tree[index].mid);
	buildTree(index*2+1, tree[index].mid+1, r);
}


void change(int change_index, int point_index){
	tree[point_index].sum_cow -= 1;
	if(tree[point_index].l!=tree[point_index].r){
		if(change_index<=tree[point_index].mid) 
			change(change_index, 2*point_index);
		else change(change_index, 2*point_index+1);
	}	
	if(tree[point_index].sum_cow==0) 
		tree[point_index].index_right = -1;
	else tree[point_index].index_right = tree[point_index*2+1].sum_cow==0 ? tree[point_index*2].index_right : tree[point_index*2+1].index_right;
	return;
}


int search(int point_index, int sum){
	//printf("%d\n", point_index);
	if(tree[point_index].l == tree[point_index].r) return tree[point_index].index_right;
	if(tree[point_index].sum_cow == sum) 
		return tree[point_index].index_right;
	else if(tree[point_index].sum_cow > sum)
			if(tree[point_index*2].sum_cow<sum)
				return search(point_index*2+1, sum-tree[point_index*2].sum_cow);
			else return search(point_index*2, sum);
	
}


int main(){
	freopen("ans.txt", "w", stdout);
	scanf("%d", &n);
	p[1] = 0;
	for(int i=2; i<=n; i++)
		scanf("%d", &p[i]);
	buildTree(1, 1, n);
	for(int i=n; i>=1; i--){
		b[i] = search(1, p[i]+1);
		change(b[i], 1);
	}
	for(int i=1; i<=n; i++)
		printf("%d\n", b[i]);
	return 0;
}
