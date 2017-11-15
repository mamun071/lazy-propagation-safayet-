#include<bits/stdc++.h>
using namespace std;

#define mx 100009
long long int ar[mx];
long long int lazy[3*mx];

struct info {
    int prop, sum;
} tree[mx * 3];

void update(int node, int b, int e, int i, int j, int x)
{
    if (i > e || j < b)
        return;
    if (b >= i && e <= j)
    {
        tree[node].sum += ((e - b + 1) * x);
        tree[node].prop += x;
        return;
    }
    int Left = node * 2;
    int Right = (node * 2) + 1;
    int mid = (b + e) / 2;
    update(Left, b, mid, i, j, x);
    update(Right, mid + 1, e, i, j, x);
    tree[node].sum = tree[Left].sum + tree[Right].sum + (e - b + 1) * tree[node].prop;
}

int query(int node, int b, int e, int i, int j, int carry = 0)
{
    if (i > e || j < b)
        return 0;

    if (b >= i and e <= j)
        return tree[node].sum + carry * (e - b + 1);

    int Left = node << 1;
    int Right = (node << 1) + 1;
    int mid = (b + e) >> 1;

    int p1 = query(Left, b, mid, i, j, carry + tree[node].prop);
    int p2 = query(Right, mid + 1, e, i, j, carry + tree[node].prop);

    return p1 + p2;
}

main()
{
    long long int n,c,p,v,q;
    int t;
    scanf("%d",&t);
    //t--;
    while(t--)
    {

        memset(ar,0,sizeof ar);
        memset(lazy,0,sizeof lazy);
        memset(tree,0,sizeof tree);
        scanf("%lld",&n);
        for(int i=1;i<=n;i++)
            ar[i]=0,lazy[i]=0;
        //make_tree(1,1,n);
        scanf("%d",&c);
        while(c--)
        {
            int flag;
            cin>>flag;
            if(flag==0)
            {
                //int p,q,v;
                scanf("%lld%lld%lld",&p,&q,&v);
                update(1,1,n,p,q,v);
            }
            else
            {
                scanf("%lld%lld",&p,&q);
                cout<<query(1,1,n,p,q)<<endl;
            }
        }
    }
}

