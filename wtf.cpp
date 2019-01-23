#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
vector<int>nextApple[100010];
int n, u, v, p, numQuery, tmp;
char op;
int c[200010];
int appleStart[100010], appleEnd[100010];
bool isvis[100010];
int lowbit(int x){
	return x & (-x);
}

void init(){
	for(int i=1; i<=2*n+1; i++)
		c[i] = lowbit(i);
}

void dfs(int nowNode){
	int nextNode;
	++p;
	appleStart[nowNode] = p;
	for(int i=0; i<nextApple[nowNode].size(); i++){
		nextNode = nextApple[nowNode][i];
		if(!isvis[nextNode]){
			isvis[nextNode] = true;
			dfs(nextNode);
		}		
	}	
	++p;
	appleEnd[nowNode] = p;
}


int sum_query(int x){
	int ret = 0;
	for(; x>0; x-=lowbit(x))
		ret += c[x];
	return ret;
}

void change(int x, int a){
	for(; x<=2*n; x+=lowbit(x))
		c[x] += a;
}

int query(int t){
	int sum1, sum2; 
	sum1 = sum_query(appleStart[t]-1);
	sum2 = sum_query(appleEnd[t]);
	return (sum2 - sum1) >> 1;
}

int main(){
	freopen("in.txt","r",stdin);
	scanf("%d", &n);
	init();
	for(int i=0; i<n-1; i++){
		scanf("%d %d", &u, &v);
		nextApple[u].push_back(v);
		nextApple[v].push_back(u);	
	}
	p = 0;
	memset(isvis, 0, sizeof(isvis));
	isvis[1] = true;
	dfs(1);
	scanf("%d\n", &numQuery);
	for(int i=0; i<numQuery; i++){
		scanf("%c %d\n", &op, &tmp);
		if(op=='Q')
			printf("%d\n", query(tmp));
		else{
			int tmp_apple = sum_query(appleStart[tmp]) - sum_query(appleStart[tmp]-1);
			if(tmp_apple==0){
				change(appleStart[tmp], 1);
				change(appleEnd[tmp], 1);
			}else{
				change(appleStart[tmp], -1);
				change(appleEnd[tmp], -1);			
			}
		}
	}
	return 0;
}


