#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
stack<char> op;
stack<int> num;
char str[100];
//如果当前读入操作符运算优先级不高于栈顶运算符，则弹出栈顶运算符执行运算

int Rank(char c){
	if(c=='*' || c=='/')	return 3;
	else if(c=='+' || c=='-') return 2;
	else if(c=='^') return 4;
	else return 0;
}


int cal(int a, int b, char c){
	//printf("%d %d %c = ", a, b, c);
	if(c=='+') return a + b;
	if(c=='-') return b - a;
	if(c=='*') return a * b;
	if(c=='/') return b / a;
	if(c=='^'){//b^a
		int ret = 1;
		for(int i=1; i<=a; i++)
			ret = ret * b;
		return ret;
	}	
}


int main(){
	freopen("in.txt", "r", stdin);
	while(scanf("%s", str)!=EOF){
		if((str[0]>='0'&&str[0]<='9')||(str[0]=='-'&&str[1]>='0'&&str[1]<='9'))
			num.push(atoi(str));
		else if(str[0]=='(')
			op.push('(');
		else if(str[0]==')'){
			while(op.top()!='('){
				int num1, num2;
				char this_op = op.top(); op.pop();
				num1 = num.top(); num.pop();
				num2 = num.top(); num.pop();
				num.push(cal(num1, num2, this_op));
				//printf("%d\n", cal(num1, num2, this_op));
			}
			op.pop();
		}else{
			while(!op.empty()&&op.top()!='('&&Rank(str[0])<=Rank(op.top())){  //注意留住左括号不能被弹出去
				int num1, num2;
				char this_op = op.top(); op.pop();
				num1 = num.top(); num.pop();
				num2 = num.top(); num.pop();
				num.push(cal(num1, num2, this_op));	
				//printf("%d\n", cal(num1, num2, this_op));		
			}
			op.push(str[0]);
		}
	}
	while(!op.empty()){
		int num1, num2;
		char this_op = op.top(); op.pop();
		num1 = num.top(); num.pop();
		num2 = num.top(); num.pop();
		num.push(cal(num1, num2, this_op));
		//printf("%d\n", cal(num1, num2, this_op));	
	}
	printf("%d\n", num.top());
	return 0;
}
