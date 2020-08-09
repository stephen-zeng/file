#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;
struct node{
	long long l,r;
	long long sum;
};
node tree[4*MAXN];
long long  s[MAXN];
long long n,m;
long long tag[4*MAXN];
long long tag1[4*MAXN];
long long p;
long long build(long long l,long long r,long long num)
{
	tree[num].l=l;
	tree[num].r=r;
	tag1[num]=1;
	if (l==r)
	{
		tree[num].sum=s[l]%p;
		return tree[num].sum%p;
	}
	long long mid=(r+l)/2;
	tree[num].sum+=build(l,mid,num*2)%p;
	tree[num].sum+=build(mid+1,r,num*2+1)%p;
	return tree[num].sum%p;
}
void up_tag(long long num,long long k,long long k2)
{
	long long l=tree[num].l;
	long long r=tree[num].r;
	tree[num].sum=(tree[num].sum*k2%p+k*(r-l+1)%p)%p;
	tag1[num]=(tag1[num]*k2)%p;
	tag[num]=(tag[num]*k2+k)%p;
}
void push_tag(long long num)
{
	long long l=tree[num].l;
	long long r=tree[num].r;
	up_tag(num*2,tag[num]%p,tag1[num]%p);
	up_tag(num*2+1,tag[num]%p,tag1[num]%p);
	tag[num]=0;
	tag1[num]=1;
}
void add(long long kl,long long kr,long long k,long long num)
{
	long long l=tree[num].l;
	long long r=tree[num].r;
	if (kl<=l&&r<=kr)
	{
		tree[num].sum+=(r-l+1)*k%p;
		tag[num]=(tag[num]+k)%p;
		return;
	}
	push_tag(num);
	long long mid=(r+l)/2;
	if (kl<=mid) add(kl,kr,k,num*2);
	if (kr>mid) add(kl,kr,k,num*2+1);
	tree[num].sum=(tree[num*2].sum%p+tree[num*2+1].sum%p)%p;

}
void addplus(long long kl,long long kr,long long k,long long num)
{
	long long l=tree[num].l;
	long long r=tree[num].r;
	if (kl<=l&&r<=kr)
	{
		tree[num].sum=tree[num].sum*k%p;
		tag1[num]=tag1[num]*k%p;
		tag[num]=tag[num]*k%p;
		return;
	}
	push_tag(num);
	long long mid=(r+l)/2;
	if (kl<=mid) addplus(kl,kr,k,num*2);
	if (kr>mid) addplus(kl,kr,k,num*2+1);
	tree[num].sum=(tree[num*2].sum%p+tree[num*2+1].sum%p)%p;

}
long long gsum(long long kl,long long kr,long long num)
{
	long long l=tree[num].l;
	long long r=tree[num].r;
	long long sum=tree[num].sum%p;
	if (kl<=l&&r<=kr) return sum%p;
	push_tag(num);
	long long ret=0;
	long long mid=(r+l)/2;
	if (kl<=mid) ret+=gsum(kl,kr,num*2)%p;
	if (kr>mid) ret+=gsum(kl,kr,num*2+1)%p;
	return ret%p;
}
int main()
{
//	freopen("t.txt","r",stdin);
	cin>>n>>m>>p;
	for (int i=1;i<=n;i++)
	cin>>s[i];
	build(1,n,1);
	for (int i=1;i<=m;i++)
	{
		long long mo;
		long long x,y,k;
		cin>>mo;
		if (mo==1)
		{
			cin>>x>>y>>k;
			addplus(x,y,k,1);
//			cout<<mo<<endl;
//			for (int i=1;i<=9;i++)
//			cout<<i<<"-->"<<tree[i].l<<" "<<tree[i].r<<" "<<tree[i].sum<<endl;
//			cout<<endl;
		}
		if (mo==2)
		{
			cin>>x>>y>>k;
			add(x,y,k,1);
//			cout<<mo<<endl;
//			for (int i=1;i<=9;i++)
//			cout<<i<<"-->"<<tree[i].l<<" "<<tree[i].r<<" "<<tree[i].sum<<endl;
//			cout<<endl;
		 } 
		if (mo==3)
		{	
			cin>>x>>y;
			cout<<gsum(x,y,1)<<endl;
		}
	}
	return 0;
}
