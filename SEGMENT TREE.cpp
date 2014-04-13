//author :: Shani Singh
//Tag :: Segment Tree single point update
//date :: 18/03/2014

#include<bits/stdc++.h>
using namespace std;
int a[1000000];
int Tree[1000000];
void init(int node ,int L, int R)
{
    if(L == R){
        Tree[node] = a[L];
    }
    else{
        int mid = (L+R) >> 1;
        init(2*node,L,mid);
        init(2*node + 1,mid+1,R);
        Tree[node] = Tree[2*node] + Tree[2*node+1];
    }

}

int query(int node,int L,int R,int i,int j)
{
    int mid = (L+R) >> 1;
    if(i == L && j == R)
        return Tree[node];
    if(mid >= j)
        return query(2*node,L,mid,i,j);
    else if(mid<i)
        return query(2*node+1,mid+1,R,i,j);
    else{
            int k = query(2*node,L,mid,i,mid);
            int l = query(2*node+1,mid+1,R,mid+1,j);
            return k+l;
    }
}

void update(int node,int L,int R,int i,int value)
{
    int mid = (L+R) >> 1;
    if(L == R){
        Tree[node] = value;
        return ;
    }
    else if(i <= mid)
        update(2*node,L,mid,i,value);
    else if(i > mid)
        update(2*node+1,mid+1,R,i,value);

    Tree[node] = Tree[2*node] + Tree[2*node+1];
    return ;
}

int main()
{
	ios_base::sync_with_stdio (false);
	int n;
	cin >> n;
	for(int i= 0;i < n;i++){
        cin >> a[i];
	}
    init(1,0,n-1);
   // update(1,0,n-1,2,-1);

/*    for(int i= 0;i < 10;i++)
        cout << Tree[i] << endl;
*/
	for(int i = 0;i < n;i++)
    {
        int a1,b;
        cin >> a1 >> b;
        cout << query(1,0,n-1,a1,b) << endl;
    }
	return 0;
}
