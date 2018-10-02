#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
const short int M = 25;

struct segTree
{
  int tr[300010];
  int lazy[300010];
  segTree(){};
  void relaxa(int no,int l,int r){
    if(lazy[no]==0)return;
    int v=lazy[no];
    tr[no]+=(r-l+1)*v;
    if(l!=r){
        lazy[no*2]+=v;
        lazy[no*2+1]+=v;
    }
    lazy[no]=0;
  }
  void update( int no, int l, int r, int i, int j ,int val)
  {
    relaxa(no,l,r);
    if(l>j || r<i || l>r)return;
    if(i<=l && r<=j){
      lazy[no]+=val;
      relaxa(no,l,r);
      return;
    }
    int nxt = (no<<1), mid = (l+r)>>1;
    update(nxt,l,mid,i,j,val);
    update(nxt+1,mid+1,r,i,j,val);
    tr[no] = tr[nxt] + tr[nxt+1];
  }
  int query( int no, int l, int r, int i, int j )
  {
    relaxa(no,l,r);
    if( r < i || l > j || l>r) return 0;
    if( i<=l && r<=j ){
        return tr[no];
    }
    int nxt = (no<<1), mid = (l+r)>>1;
    return query(nxt,l,mid,i,j) + query(nxt+1,mid+1,r,i,j);
  }
};
segTree mySeg;
int treeSize[100010];
int n=0;
int chain[100010], pai[100010], chainSize[100010], head[100010], chainPos[100010], chainNo, posInBase[100010], h[100010];
int ptr;
vi g[100010];
void dfs( int x){
  treeSize[x] = 1;
  for(int i=0;i<g[x].size();++i){
    int v = g[x][i];
    if( v == pai[x]) continue;
    pai[v] = x;
    h[v]=h[x]+1;
    dfs(v);
    treeSize[x] += treeSize[v];
  }
}
void hld( int x, int ult )
{
  if( head[chainNo] == -1 ) head[chainNo] = x;
  chain[x] = chainNo;
  chainPos[x] = chainSize[chainNo]++;
  posInBase[x] = ptr++;
  int ind = -1, mai = -1;
  for(int i=0;i<g[x].size();++i)
  {
    int y = g[x][i];
    if( ult == y ) continue;
    if( treeSize[y] > mai )
    {
      mai = treeSize[y];
      ind = i;
    }
  }
  if( ind >= 0 ) hld(g[x][ind],x);
  for(int i=0;i<g[x].size();++i)
  {
    if( i == ind ) continue;
    int y = g[x][i];
    if( ult == y ) continue;
    chainNo++;
    hld(y,x);
  }
}
void init()
{
  for(int i=0;i<100010;++i)
  {
    g[i].clear();
    head[i] = -1;
    chainSize[i] = 0;
  }
  ptr = 1;
  chainNo = 0;
}

void update(int u, int v, int x){
	int cu = chain[u], cv = chain[v];
	while (cu != cv){
		if(h[head[cu]] < h[head[cv]]){
            swap(u,v);
            swap(cu,cv);
		}

		mySeg.update(1, 1, n, posInBase[head[cu]], posInBase[u], x);
		u = pai[head[cu]];
		cu = chain[u];
	}
	if(h[u] > h[v]) swap(u,v);
	mySeg.update(1, 1, n, posInBase[u], posInBase[v], x);
}

int query(int u, int v){
	int cu = chain[u], cv = chain[v],res=0;
	while (cu != cv){
		if(h[head[cu]] < h[head[cv]]){
            swap(u,v);
            swap(cu,cv);
		}
		res+=mySeg.query(1, 1, n, posInBase[head[cu]], posInBase[u]);
		u = pai[head[cu]];
		cu = chain[u];
	}

	if(h[u] > h[v]) swap(u,v);
	res+=mySeg.query(1, 1, n, posInBase[u], posInBase[v]);
	return res;
}
int main()
{
  int q;
  scanf("%d %d",&n,&q);
  init();
  for(int i = 1; i < n; ++i) {
    int a,b; scanf("%d %d",&a,&b);
    g[a].push_back(b);
    g[b].push_back(a);
  }
  h[1]=0; pai[1]=0;
  dfs(1);
  hld(1,0);
  while(q--) {
    int a,b,c,d; scanf("%d %d %d %d",&a,&b,&c,&d);
    update(a,b,1);
    printf("%d\n",query(c,d));
    update(a,b,-1);
  } 
  return 0;
}
