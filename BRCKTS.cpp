//PROBLEM :: http://www.spoj.com/problems/BRCKTS/
//TAG :: SEGMENT TREE

#include<bits/stdc++.h>
using namespace std;

#define NMAX 32768
#define TMAX 65536
struct Node
{
    int closed_pair;
    int opened_pair;
} Tree[TMAX];
char s[NMAX];
void build_Tree(int node,int left,int right)
{
    int mid = (left+right)>>1;
    if(left == right)
    {
        if(s[left] == ')')
        {
            Tree[node].closed_pair = 1;
            Tree[node].opened_pair = 0;
        }
        else
        {
            Tree[node].closed_pair = 0;
            Tree[node].opened_pair = 1;

        }
    }

    else{
        build_Tree(2*node,left,mid);
        build_Tree(2*node+1,mid + 1,right);

        int value = min(Tree[node*2].opened_pair,Tree[node*2+1].closed_pair);
        Tree[node].closed_pair = Tree[node*2].closed_pair+Tree[node*2+1].closed_pair-value;
        Tree[node].opened_pair = Tree[node*2].opened_pair+Tree[node*2+1].opened_pair-value;
    }
}
/*int query(int node,int left,int right,int i,int j)
{
    int mid = (left+right)/2;
    if(i >= left && j<=right)
    {
        return Tree[node].total;
    }
    if(mid >= j)
        return query(2*node,left,mid,i,j);
    else if(mid<i)
        return query(2*node+1,mid+1,right,i,j);
    else{
            int k = query(2*node,left,mid,i,mid);
            int l = query(2*node+1,mid+1,right,mid+1,j);
            return Tree[node*2].total+Tree[node*2+1].total+min(Tree[node*2].opened_pair,Tree[node*2+1].closed_pair);
    }
}*/
void update(int node,int left,int right,int i)
{
    int mid = (left+right)>>1;
    if(left == right)
    {
        if(Tree[node].closed_pair == 1)
            Tree[node].closed_pair = 0;
        else
            Tree[node].closed_pair = 1;

        if(Tree[node].opened_pair == 1)
            Tree[node].opened_pair = 0;
        else
            Tree[node].opened_pair = 1;
            return ;
    }
    else if(i <= mid)
        update(2*node,left,mid,i);
    else
        update(2*node+1,mid+1,right,i);

    int value = min(Tree[node*2].opened_pair,Tree[node*2+1].closed_pair);
    Tree[node].closed_pair = Tree[node*2].closed_pair+Tree[node*2+1].closed_pair-value;
    Tree[node].opened_pair = Tree[node*2].opened_pair+Tree[node*2+1].opened_pair-value;
}
int main()
{
    int t,test = 1;
   while(scanf("%d", &t)==1) {
    scanf("%s",s);
    printf("Test %d:\n", test++);
    build_Tree(1,0,t-1);
    int q,i;
   scanf("%d", &q);
   for(i = 0;i < q;i++)
    {
        int k;
        scanf("%d", &k);
        if(k > 0){
            update(1,0,t-1,k-1);
        }
        else{
        if(!Tree[1].closed_pair && !Tree[1].opened_pair)
            printf("YES\n");
        else
            printf("NO\n");
        }
    }
   }
    return 0;
}
