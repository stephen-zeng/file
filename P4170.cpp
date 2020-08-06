#include <bits/stdc++.h>
#define MAXN 55
using namespace std;
char ch[MAXN];
int f[MAXN][MAXN];
int s[MAXN];
int n;
void input()
{
	gets(ch);
	n=strlen(ch);
	for (int i=0;i<n;i++)
	s[i+1]=ch[i]-'A'+1;
}
void let_us_color_it()
{
	for (int i=1;i<=n;i++)
	f[i][i]=1;
	for (int i=1;i<n;i++)
	{
		for (int j=i+1;j<=n;j++)
		f[i][j]=INT_MAX;
	}
	for (int i=1;i<n;i++)
	{
		for (int l=1;l<=n-i;l++)
		{
			int r=l+i;
//			cout<<l<<" "<<r<<endl;
			if (s[l]==s[r]) f[l][r]=min(f[l+1][r],f[l][r-1]);
			else for (int k=l;k<r;k++) f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
		}
	}
}
int main()
{
	input();
	let_us_color_it();
//	for (int i=1;i<=n;i++)
//	{
//		for (int j=1;j<=n;j++)
//		cout<<f[i][j]<<" ";
//		cout<<endl;
//	 } 
	cout<<f[1][n]-1<<endl;
	return 0;
}
