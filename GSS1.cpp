//PROBLEM :: http://www.spoj.com/problems/GSS1/
//TAG :: SEGMENT TREE
#include<bits/stdc++.h>
using namespace std;
const int MAX = 1 << 16;
int a[MAX];
struct Node
{
    int left_max;
    int right_max;
    int max_value;
    int sum;
} Tree[MAX << 1];
void Build_Tree(int node,int L,int R)
{
    int b = node<<1;
    int mid = (L+R)>>1;
    if(L == R)
    {
        Tree[node].left_max = a[L];
        Tree[node].right_max = a[L];
        Tree[node].sum = a[L];
        Tree[node].max_value = a[L];
    }
    else{
        Build_Tree(b,L,mid);
        Build_Tree(b+1,mid+1,R);
        Tree[node].left_max = max(Tree[b].left_max,Tree[b+1].left_max+Tree[b].sum);
        Tree[node].right_max = max(Tree[b+1].right_max,Tree[b+1].sum+Tree[b].right_max);
        Tree[node].sum = Tree[b].sum + Tree[b+1].sum;
        Tree[node].max_value = max(Tree[b].right_max + Tree[b+1].left_max,max(Tree[b].max_value,Tree[b+1].max_value));

    }
}
Node query(int node,int L,int R,int i,int j)
{
    Node p;
    int b = node<<1;
    int mid = (L+R)>>1;
    if(L >= i && j >= R)
    {
        return Tree[node];
    }
    else if(mid >= j)
        return query(b,L,mid,i,j);
    else if(mid < i)
        return query(b+1,mid+1,R,i,j);
    else{
        Node m = query(b,L,mid,i,mid);
        Node n = query(b+1,mid+1,R,mid+1,j);

        p.left_max = max(m.left_max,n.left_max+m.sum);
        p.right_max = max(n.right_max,n.sum+m.right_max);
        p.sum = m.sum + n.sum;
        p.max_value = max(m.right_max + n.left_max,max(m.max_value,n.max_value));
        return p;
    }
}
int main()
{
    int N,Q,i;
    scanf("%d",&N);
    for(int i =0;i < N;i++)
    {
        scanf("%d",&a[i]);
    }
    Build_Tree(1,0,N-1);
    /*cout << Tree[1].sum << endl;
    cout << Tree[1].max_value << " " << Tree[1].left_max << " " << Tree[1].right_max << endl;
    */
    scanf("%d",&Q);
    for(i = 0;i < Q;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int value = query(1,0,N-1,l-1,r-1).max_value;
        printf("%d\n",value);
    }

}
