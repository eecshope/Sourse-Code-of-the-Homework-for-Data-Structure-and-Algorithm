#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include<map>
using namespace std;  //注意考虑转义和字符串，因为是顺序执行所以在优先级相同的前提下无所谓把程序弄得那么复杂
int main()
{
	char c;
	while((c=getchar())!=EOF) 
	{
		if(c=='/')
		{
			char s=getchar();
			if(s=='*')
			{
				char m,n;
				m=getchar();
				n=getchar();
				while(m!='*'||n!='/')
				{
					m=n;
					n=getchar();
				}
			}
			else
			{
				putchar(c);
				putchar(s);
			}
		}
		else if(c=='\''||c=='"')
		{
			putchar(c);
			char s;
			while((s=getchar())!=c)
			{
				putchar(s);
				if(s=='\\') 
					putchar(getchar());
			}
			putchar(s);
		}
		else
		{
			putchar(c);
		}
	}
	return 0;
}


//本文来自 不要失望故事还长 的CSDN 博客 ，全文地址请点击：https://blog.csdn.net/m0_37975647/article/details/77505390?utm_source=copy 
