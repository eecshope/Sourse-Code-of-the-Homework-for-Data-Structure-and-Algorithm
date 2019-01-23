#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
struct Point{
    int x, y;
    Point(){}
    Point(int x, int y): x(x), y(y) {}
    bool operator < (const Point &a) const{
        if(x==a.x) return y < a.y;
        else return x < a.x;
    }
}point[2020];
stack<Point> sta;

int makeShell(int n){
    sta.push(point[0]);
    sta.push(point[1]);
    Point a, b, c, d;
    for(int i=2; i<n; i++){
        while(sta.size()>1){
            a = sta.top(); sta.pop();
            b = sta.top();
            c = Point(point[i].x-a.x, point[i].y-a.y);
            d = Point(a.x-b.x, a.y-b.y);
            if(c.x*d.y-d.x*c.y>=0){
                sta.push(a);
                break;   
            }
            else ;
        }
        sta.push(point[i]);
    }
    sta.push(point[n-2]);
    for(int i=n-3; i>=0; i--){
        while(sta.size()>1){
            a = sta.top(); sta.pop();
            b = sta.top();
            c = Point(point[i].x-a.x, point[i].y-a.y);
            d = Point(a.x-b.x, a.y-b.y);
            if(c.x*d.y-d.x*c.y>=0){
                sta.push(a);
                break;   
            }
            else ;
        }
        sta.push(point[i]);
    }
    int ret = sta.size();
    int tmp = 0;
    while(!sta.empty()){
        point[tmp++] = sta.top();
        sta.pop();
    }
    return tmp;
}


bool checkline(int n){
    bool isok = true;
    for(int i=2; i<n; i++){
        Point a(point[i].x-point[i-1].x, point[i].y-point[i-1].y);
        Point b(point[i-1].x-point[i-2].x, point[i-1].y-point[i-2].y);
        if((a.x*b.y - b.x*a.y)!=0){
            isok = false;
            break;
        }
    }
    return isok;
}


int main(){
    freopen("in.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%d %d", &point[i].x, &point[i].y);
        sort(point, point+n);
        if(n==1||n==2)
            printf("NO\n");
        else{
            if(checkline(n)){
                printf("NO\n");
                continue;
            }
            int shell_size = makeShell(n);
            
            bool has_three = false;
            bool isok = true;
            point[shell_size++] = point[1]; 
            for(int i=2; i<shell_size; i++){
                Point a(point[i].x-point[i-1].x, point[i].y-point[i-1].y);
                Point b(point[i-1].x-point[i-2].x, point[i-1].y-point[i-2].y);
                if(a.x*b.y-b.x*a.y==0)
                    has_three = true;
                else{
                    if(has_three)
                        has_three = false;
                    else{
                        isok = false;
                        break;
                    }
                }
            }
            if(isok)
                printf("YES\n");
            else 
                printf("NO\n");
        }
           
    }
    return 0;
}