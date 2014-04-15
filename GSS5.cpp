//PROBLEM :: http://www.spoj.com/problems/GSS5/
//TAG :: SEGMENT TREE
#include<bits/stdc++.h>
using namespace std;
const int MAX = 1 << 14;
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
void update(int node,int L,int R,int i,int value)
{
    int mid = (L+R)>>1;
    int b = (node)<<1;
   if(L == R)
    {
        Tree[node].left_max = value;
        Tree[node].right_max = value;
        Tree[node].sum = value;
        Tree[node].max_value = value;
        return ;
    }
    if(mid >= i)
        update(b,L,mid,i,value);
    else if(mid < i)
        update(b+1,mid+1,R,i,value);

    Tree[node].left_max = max(Tree[b].left_max,Tree[b+1].left_max+Tree[b].sum);
    Tree[node].right_max = max(Tree[b+1].right_max,Tree[b+1].sum+Tree[b].right_max);
    Tree[node].sum = Tree[b].sum + Tree[b+1].sum;
    Tree[node].max_value = max(Tree[b].right_max + Tree[b+1].left_max,max(Tree[b].max_value,Tree[b+1].max_value));

    return ;
}
Node query(int node,int L,int R,int i,int j)
{
    if(i>j)return Tree[0];
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
int main() {
	//READ("in.txt");
	//WRITE("out.txt");
	int test, cs, n, q, i, x1, y1, x2, y2, res;
	scanf("%d", &test);
	for(cs = 1; cs <= test; cs++) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d", a + i);
		Build_Tree(1, 0, n-1);
		scanf("%d", &q);
		while(q--) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x1--, y1--, x2--, y2--;
			if(y1 < x2) {
				res = query(1, 0, n-1, x1, y1).right_max;
				res += query(1, 0, n-1, y1+1, x2-1).sum;
				res += query(1, 0, n-1, x2, y2).left_max;
			}
			else {
				res = query(1, 0, n-1, x2, y1).max_value;
				res = max(res, max(
					query(1, 0, n-1, x1, x2-1).right_max + query(1, 0, n-1, x2, y2).left_max,
					query(1, 0, n-1, x1, y1).right_max + query(1, 0, n-1, y1+1, y2).left_max
				));
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
