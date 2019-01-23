#include<stdio.h>
#include<string.h>
char x[50010], y[50010];
int n, m;
int next[50010];


void build_next(){
	int i, k;
	next[0] = -1;
	i = 0; k = -1;
	while(i < n-1){
		while(k>=1 && x[k]!=x[i])
			k = next[k];
		k++; i++;
		if(x[i] == x[k])
			next[i] = next[k];
		else next[i] = k;
	}
	return;
}


int main(){
	freopen("in.txt","r",stdin);
	while(scanf("%[^\n]\n%[^\n]\n", x, y)!=EOF){
		int i, j;
		n = strlen(x);
		m = strlen(y);
		build_next();		
		i = 0;
		if(n>=m) j = 0;
		else j = m - n;
		while(i<n && j<m){
			if(x[i]==y[j]||i==-1){
				++i;
				++j;
			}else
				i = next[i];
		}
		if(i!=0){
			for(j=0; j<i; j++)
				printf("%c", x[j]);
			printf(" %d\n", i);		
		}
		else printf("0\n");
	}
	return 0;
}
