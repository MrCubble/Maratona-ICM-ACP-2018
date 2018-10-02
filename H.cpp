#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int,int> ii;
const int N = 101010;
const int LOGN = 22;
char P[N],T[N];
int b[N];
int n, m, q, nvl[N], sz[N], pai[N], big[N];
int head[N], position, cntChain, chain[N], posChain[N], anc[N][LOGN];
vector <int> adj[N];
void kmpPreprocess()                // call this before calling kmpSearch()
{
    int i = 0, j = -1;
    b[0] = -1;                          // starting values
    while (i < m)                         // pre-process the pattern string P
    {
        while (j >= 0 && P[i] != P[j])
            j = b[j];  // different, reset j using b
        i++;
        j++;                             // if same, advance both pointers
        b[i] = j; // observe i = 8, 9, 10, 11, 12, 13 with j = 0, 1, 2, 3, 4, 5
    }
}
ii anda(int j, char c)     // this is similar as kmpPreprocess(), but on string T
{
    while (j >= 0 && c != P[j])
        j = b[j];  // different, reset j using b
    j++;                             // if same, advance both pointers
    int qtd = 0;
    if (j == m)                                // a match found when j == m
    {
        qtd ++;
        j = b[j];                    // prepare j for the next possible match
    }
    return ii(j, qtd);
}
char base[N];
struct Node{
    ii res[110];
    Node(){
        for(int i=0; i < m; i++) res[i]=ii(i, 0);
    }
    void reseta(char c){
        for(int i=0; i < m; i++) res[i]=anda(i, c);//printf("%d (%c) = (%d, %d)\n",i,x,res[i].x,res[i].y);
    }
    ii & operator[](int id){ return res[id]; }
} st1[N << 2], st2[N << 2];

Node merge(Node a, Node b){
    Node c;
    for(int i=0; i < m; i++) c[i] = ii(b[a[i].x].x, a[i].y + b[a[i].x].y);
    return c;
}
void printa(int no, int l, int r){
    if(l == r){
        st1[no].reseta(base[l]);
        st2[no].reseta(base[l]);
        //printf("@%d %d = %d %d = %c\n",l,r,st1[no][0].y,st2[no][0].y,base[l]);
        return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    printa(nxt, l, mid);
    printa(nxt + 1, mid + 1, r);
    st1[no] = merge(st1[nxt], st1[nxt+1]);
    st2[no] = merge(st2[nxt+1], st2[nxt]);
    //printf("@%d %d = %d %d\n",l,r,st1[no][0].y,st2[no][0].y);
}
void update_st(int no, int l, int r, int id, char val) {
    if(l > id || r < id)return;
    if(l == r){
        st1[no].reseta(val);
        st2[no].reseta(val);
        return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    update_st(nxt, l, mid, id, val);
    update_st(nxt + 1, mid + 1, r, id, val);
    st1[no] = merge(st1[nxt], st1[nxt+1]);
    st2[no] = merge(st2[nxt+1], st2[nxt]);
}
Node query_st( int no, int l, int r, int i,int j, bool sobi){
    if(r < i || l > j) return Node();
    if(i <= l && r <= j){
        if(sobi) return st2[no];
        return st1[no];
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(sobi) return merge(query_st(nxt + 1, mid + 1, r, i, j, sobi), query_st(nxt, l, mid, i, j, sobi));
    return merge(query_st(nxt, l, mid, i, j, sobi), query_st(nxt + 1, mid + 1, r, i, j, sobi));
}
int LCA(int u, int v) {
	if(nvl[u] < nvl[v]) swap(u,v);
	int diff = nvl[u] - nvl[v];
	for(int i=LOGN-1;i>=0;i--) if((1<<i) <= diff) u = anc[u][i], diff -= (1<<i);
	if(u == v) return u;
	for(int i=LOGN-1;i>=0;i--) if(anc[u][i] != anc[v][i]) {
		u = anc[u][i];
		v = anc[v][i];
	}
	return anc[u][0];
}
void dfs(int u, int p){
	sz[u] = 1;
	big[u] = -1;
	nvl[u] = nvl[p] + 1;
    anc[u][0] = p;
    for(int j=1;j<LOGN;j++) anc[u][j] = anc[anc[u][j-1]][j-1];
	int v, i;
	for(i = 0; i < adj[u].size(); i++){
		v = adj[u][i];
		if(v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
		if(big[u] == -1 || sz[v] > sz[big[u]]) big[u] = v;
	}

}

void hld(int u, int p){
    base[position] = T[u];
	posChain[u] = position++;
	chain[u] = cntChain;
	if(big[u] == -1) return;
	hld(big[u], u);
	int v, i;
	for(i = 0; i < adj[u].size(); i++){
		v = adj[u][i];
		if(v == p || v == big[u]) continue;
		head[++cntChain] = v;
		hld(v, u);
	}
}

void build_hld(){
	position = 0;
	cntChain = 0;
	dfs(0, -1);
	hld(0, -1);
}
int sobe(int v,int dif){
    for(int i = 0; i < LOGN; i++) if(dif & (1 << i)) v = anc[v][i];
    return v;
}
Node query_up(int u, int v, bool sobi){
    int cu, cv = chain[v];
    Node res;
    while(1){
        cu = chain[u];
        if(cu == cv){
            if(sobi) res = merge(res, query_st(1, 0, n - 1, posChain[v], posChain[u], sobi));
            else res = merge(query_st(1, 0, n-1, posChain[v], posChain[u], sobi), res);
            break;
        }
        if(sobi) res = merge(res, query_st(1, 0, n-1, posChain[head[cu]], posChain[u], sobi));
        else res = merge(query_st(1, 0, n-1, posChain[head[cu]], posChain[u], sobi), res);
        u=head[cu];
        u=anc[u][0];
    }
    return res;
}
int query(int u, int v){
    bool mudou=false;
    if(nvl[v] > nvl[u]) swap(u, v), mudou=true;
    int lca = LCA(u, v);
    if(lca == v) return query_up(u, lca, !mudou)[0].y;
    if(mudou) swap(u, v);
    int cima = sobe(u, nvl[u] - nvl[lca] - 1);
    //printf("%d(%d) %d(%d) = %d %d => %d\n", u,nvl[u], v,nvl[v], lca,mudou,cima);
    return merge(query_up(u, cima, 1), query_up(v, lca, 0))[0].y;
}
int main(){
    int q;
    scanf("%d %d",&n,&q);
    scanf(" %s %s",P,T);
    m=strlen(P);
    kmpPreprocess();
    for(int i=0; i < n-1; i++){
        int a, b; scanf("%d %d", &a, &b);
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    build_hld();
    printa(1, 0, n-1);
    while(q--) {
        int op; scanf("%d", &op);
        if(op==2){
            int a; char b;
            scanf("%d %c", &a, &b);
            a--;
            update_st(1, 0, n-1, posChain[a], b);
        }
        else{
            int a,b; scanf("%d %d",&a ,&b);
            a--; b--;
            printf("%d\n",query(a, b));
        }
    }
    return 0; 
}
