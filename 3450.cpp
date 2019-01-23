#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;
int n, k;
int myrank[800050];
int tmp[800050];

bool compare_sa(int i, int j){
    if(myrank[i]!=myrank[j]) return myrank[i] < myrank[j];
    else{
        int ri = i+k<=n ? myrank[i+k] : -1;
        int rj = j+k<=n ? myrank[j+k] : -1;
        return ri < rj;
    }
}

void construct_sa(string S, int *sa){
    n = S.length();
    for(int i=0; i<=n; i++){
        sa[i] = i;
        myrank[i] = i < n ? S[i] : -1;
    }
    for(k=1; k<=n; k*=2){
        sort(sa, sa+n+1, compare_sa);
        tmp[sa[0]] = 0;
        for(int i=1; i<=n; i++){
            tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1], sa[i]) ? 1 : 0);
        }
        for(int i=0; i<=n; i++){
            myrank[i] = tmp[i];
        }
    }
}

void construct_lcp(string S, int *sa, int *lcp){
    n = S.length();
    for(int i=0; i<=n; i++) myrank[sa[i]] = i;
    int h = 0;
    lcp[0] = 0;
    for(int i=0; i<n; i++){
        int j = sa[myrank[i]-1];
        if(h>0) h--;
        for(; j+h<n && i+h<n; h++){
            if(S[j+h] != S[i+h]) break;
        }
        lcp[myrank[i]-1] = h;
    }
}
string a, b;
int belong[800050];
int num_c;
int num_str;
int sa[800050];
int lcp[800050];
char ans[800050];
int lenans;
bool isvis[5000];
bool check(int len){
    lenans = 0;
    int cnt = 0;
    memset(isvis, 0, sizeof(isvis));
    for(int i=1; i<num_c; i++){
        if(belong[sa[i]]==-1) continue;
        if(cnt==0){
            isvis[belong[sa[i]]] = true;
            ++cnt;
        }
        if(lcp[i]>=len&&!isvis[belong[sa[i+1]]]){
            ++cnt;
            isvis[belong[sa[i+1]]] = true;
        }else{
            lenans = 0;
            cnt = 0;
            memset(isvis, 0, sizeof(isvis));
        }
        if(cnt>=num_str){
            lenans = len;
            for(int j=0; j<len; j++)
                ans[i] = a[sa[i]+j];
            ans[lenans+1] = '\0';
            return true;
        }
    }
    return false;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    while(scanf("%d", &num_str), num_str!=0){
        memset(belong, 0, sizeof(belong));
        memset(sa, 0, sizeof(sa));
        memset(lcp, 0, sizeof(lcp));
        cin >> a;
        num_c = a.length();
        for(int i=1; i<num_str; i++){
            cin >> b;
            a += "&";
            a += b;
            belong[num_c++] = -1;
            for(; num_c<a.length(); num_c++)
                belong[num_c] = i;
        }
        construct_sa(a, sa);
        construct_lcp(a, sa, lcp); 
        int l = 1,r = num_c,mid,flag = 0;
        while(l<=r)
        {
            mid = (l+r)/2;
            if(check(mid))
            {
                flag = 1;
                l=mid+1;
            }
            else
                r=mid-1;
        }
        if(flag){
            printf("%s\n", ans);
        }else printf("Fuck\n");
    }
}