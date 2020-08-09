#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;
double tree[MAXN];
double tree1[MAXN];
double tag[MAXN];
int n,m;
int R,L;
double a;
void build(int l,int r,int num)
{
    if(l==r)
    {
        scanf("%lf",&tree[num]);
        tree1[num]=tree[num]*tree[num];
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,num*2);
    build(mid+1,r,(num*2)+1);
    tree[num]=(tree[num*2]*(mid-l+1)+tree[(num*2)+1]*(r-mid))/(r-l+1.0);
    tree1[num]=tree1[num*2]+tree1[(num*2)+1];
}
void down(int l,int r,int num)
{
    int mid=(l+r)/2;
    tag[num*2]+=tag[num];
    tag[(num*2)+1]+=tag[num];
    tree1[num*2]+=(mid-l+1)*(2*tree[num*2]*tag[num]+tag[num]*tag[num]);
    tree1[(num*2)+1]+=(r-mid)*(2*tree[(num*2)+1]*tag[num]+tag[num]*tag[num]);
    tree[num*2]+=tag[num];
    tree[(num*2)+1]+=tag[num];
    tag[num]=0;
}
void add(int l,int r,int num)
{
    if(L<=l&&r<=R)
    {
        tag[num]+=a;
        tree1[num]+=(r-l+1)*(a*2*tree[num]+a*a);
        tree[num]+=a;
        return ;
    }
    int mid=(l+r)/2;
    down(l,r,num);
    if(L<=mid) add(l,mid,num*2);
    if(R>=mid+1) add(mid+1,r,(num*2)+1);
    tree[num]=(tree[num*2]*(mid-l+1)+tree[(num*2)+1]*(r-mid))/(r-l+1.0);
    tree1[num]=tree1[num*2]+tree1[(num*2)+1];
}

double sum(int l,int r,int num)
{
    double su=0;
    if(L<=l&&r<=R) return tree[num]*(r-l+1);
    int mid=(l+r)/2;
    down(l,r,num);
    if(L<=mid) su+=sum(l,mid,num*2);
    if(R>=mid+1) su+=sum(mid+1,r,(num*2)+1);
    return su;
}

double sum1(int l,int r,int num)
{
    double su=0;
    if(L<=l&&r<=R) return tree1[num];
    int mid=(l+r)/2;
    down(l,r,num);
    if(L<=mid) su+=sum1(l,mid,num*2);
    if(R>=mid+1) su+=sum1(mid+1,r,(num*2)+1);
    return su;
}
int main()
{
    double ans,k;
    cin>>n>>m;
    build(1,n,1);
    for (int i=1;i<=m;i++)
    {
    	int b;
        cin>>b;
        if(b==1)
        {
            cin>>L>>R;
            cin>>a;
            add(1,n,1);
        }
        if(b==2)
        {
            cin>>L>>R;
            ans=sum(1,n,1)/(R-L+1);
            printf("%.4lf\n",ans);
        }
        if(b==3)
        {
            cin>>L>>R;
            ans=sum(1,n,1)/(R-L+1);
            ans=ans*ans;
            k=sum1(1,n,1);
            ans=k/(R-L+1)-ans;
            printf("%.4lf\n",ans);
        }
    }
}
