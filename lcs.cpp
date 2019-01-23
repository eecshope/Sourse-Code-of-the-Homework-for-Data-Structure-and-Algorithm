#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, c[300010];
struct node{
	int value, place;
	bool operator < (const node &a) const{
		if(this->value == a.value)
			return this->place > a.place;
		else return this->value < a.value;
	}
}a[300010];
int lis[300010];
int ans;


int lowbit(int i){
	return i & (-i);
}


int query(int x){
	int ret = 0;
	for(; x>0; x-=lowbit(x))
		ret = max(ret,  c[x]);
	return ret;
}


void update(int x, int value){
	for(; x<=n; x+=lowbit(x))
		c[x] = max(c[x], value);
}


int main(){
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		scanf("%d", &a[i].value);
		a[i].place = i;
	}
	sort(a+1, a+1+n);
	memset(c, 0, sizeof(c));
	memset(lis, 0, sizeof(lis));	
	for(int i=1; i<=n; i++){
		lis[a[i].place] = query(a[i].place) + 1;
		update(a[i].place, lis[a[i].place]);
	}
	ans = 0;
	for(int i=1; i<=n; i++)
		ans = max(ans, lis[i]);
	printf("%d\n", ans);
	return 0;
}
