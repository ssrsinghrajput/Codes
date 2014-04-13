//PROBLEM :: http://www.spoj.com/problems/FREQUENT/
//TAG :: SEGMENT TREE
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const double EPS = 1e-10;
const int MAX = 1<<17;

struct Node{
    int frequent;
    int right_frequent;
    int left_frequent;
} Tree[MAX<<1];

int a[MAX];
void Build_Tree(int node,int L,int R)
{
    int mid = (L+R)>>1;
    int o = node<<1;
    if(L == R)
    {
        Tree[node].frequent = 1;
        Tree[node].left_frequent = 1;
        Tree[node].right_frequent = 1;
    }
    else{
        Build_Tree(o,L,mid);
        Build_Tree(o+1,mid+1,R);
        int val1 = 0;
        if(a[mid] == a[mid+1])
        {
            val1 = Tree[o].right_frequent+Tree[o+1].left_frequent;
        }
        Tree[node].frequent = max(val1,max(Tree[o].frequent,Tree[o+1].frequent));
        if(a[L] == a[mid] && a[mid+1] == a[mid])
        {
            Tree[node].left_frequent = Tree[o].right_frequent+Tree[o+1].left_frequent;
        }
        else
            Tree[node].left_frequent = Tree[o].left_frequent;

        if(a[mid+1] == a[R] && a[mid+1] == a[mid])
        {
            Tree[node].right_frequent = Tree[o].right_frequent+Tree[o+1].left_frequent;
        }

        else
            Tree[node].right_frequent = Tree[o+1].right_frequent;

    }
}
Node query(int node,int L,int R,int i,int j)
{
    int mid = (L+R) >> 1;
    int o = node<<1;
    Node p;
    p.frequent = 0;
    p.left_frequent = 0;
    p.right_frequent = 0;
    if(i <= L && j >= R)
    {

        //cout << Tree[node].frequent << endl;;
        return Tree[node];
    }
    else if(mid >= j)
        return query(o,L,mid,i,j);
    else if(mid<i)
        return query(o+1,mid+1,R,i,j);
    else{

            Node k = query(o,L,mid,i,mid);
            Node s = query(o+1,mid+1,R,mid+1,j);
         //   cout << k.frequent << " "  << k.left_frequent << " " << k.right_frequent<<" "<< s.frequent <<" " << s.left_frequent << " " << s.right_frequent<< endl;
            int val1 = 0;
        if(a[mid] == a[mid+1])
        {
            val1 = k.right_frequent+s.left_frequent;
        }
        int m = k.frequent;
        if(val1 > k.frequent)
            m = val1;
        if(s.frequent > m)
            m = s.frequent;
        //cout << m << endl;
        p.frequent = m;
        if(a[i] == a[mid] && a[mid+1] == a[mid])
        {
            p.left_frequent = k.right_frequent+s.left_frequent;
        }
        else
            p.left_frequent = k.left_frequent;

        if(a[mid+1] == a[j] && a[mid+1] == a[mid])
        {
            p.right_frequent = k.right_frequent+s.left_frequent;
        }

        else
            p.right_frequent = s.right_frequent;
        return p;

    }
}
int main()
{

    int n,q;
    while(scanf("%d",&n) == 1 && n != 0){
        scanf("%d",&q);
        for(int i = 0;i < n;i++)
            scanf("%d",&a[i]);

        Build_Tree(1,0,n-1);
        for(int i = 0;i < q;i++)
        {
            int b,c;
            scanf("%d%d",&b,&c);
            //cout << Tree[5].frequent << endl;
            Node l = query(1,0,n-1,b-1,c-1);
            printf("%d\n",l.frequent);
        }
    }
    return 0;
}
