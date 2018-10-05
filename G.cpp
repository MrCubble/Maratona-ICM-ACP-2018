#include <bits/stdc++.h>
#define INF 1e15

using namespace std;
typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;


int a, b, m, va[202020], vb[202020];
pair<int,pii> ar[202020];

ll sum;

ll inf = 1e15;
  
const int M=202020,N=3030;
ll second[M],nxt[M],gap[N],fst[N],c[N],pre[N],q[N],dis[N];
//Pra onde aresta vai
//Próximo da lista de adj
//Quantidade de elementos a uma certa distância (usado na sap)
//Primeiro da lista de adjacência
//Pra percorrer na lista de adjacência
//Predecessor pra augment
//Fila pra pegar as distâncias
//Distância de um certo elemento (na sap)
ll prea[N];
ll f[M];
//A capacidade de uma certa aresta
ll S,T,tot,Tn;
//Source, Target, tot de arestas, Tn é num de vertices
void init(int s,int t,int tn) {
  tot=1;
  for(int i=0; i<tn; i++)
    fst[i]=0;
  //0 quer dizer que ele não liga a nada
  S=s;T=t;Tn=tn;
}

void add(int u,int v,ll c1) {
  tot++;
  second[tot]=v;
  f[tot]=c1;
  nxt[tot]=fst[u];
  fst[u]=tot;

  tot++;
  second[tot]=u;
  f[tot]=0;
  nxt[tot]=fst[v];
  fst[v]=tot;
}
ll sap() {
  int u=S,t=1;ll flow=0;
  for(int i=0; i<Tn; i++) c[i]=fst[i],dis[i]=Tn,gap[i]=0;
  q[0]=T;dis[T]=0;pre[S]=0;
  for(int i=0; i<t; i++) {
    int u=q[i];
    for (int j=fst[u];j;j=nxt[j]) if (dis[second[j]]>dis[u]+1&&f[j^1])
    q[t++]=second[j],dis[second[j]]=dis[u]+1;
  }
  for(int i=0; i<Tn; i++) gap[dis[i]]++;
  while (dis[S]<=Tn) {
    while (c[u]&&(!f[c[u]]||dis[second[c[u]]]+1!=dis[u])) c[u]=nxt[c[u]];
    if (c[u]) {
      pre[second[c[u]]]=c[u]^1;
      u=second[c[u]];
      if (u==T) {
        ll minf=inf;
        for (int p=pre[T];p;p=pre[second[p]]) minf=min(minf,f[p^1]);
        for (int p=pre[T];p;p=pre[second[p]]) f[p^1]-=minf,f[p]+=minf;
        flow+=minf;u=S;
      }
    } else {
      if (!(--gap[dis[u]])) break;
      int mind=Tn;
      c[u]=fst[u];
      for (int j=fst[u];j;j=nxt[j]) if (f[j]&&dis[second[j]]<mind) mind=dis[second[j]],c[u]=j;
      dis[u]=mind+1;
      gap[dis[u]]++;
      if (u!=S) u=second[pre[u]];
    }
  }
  return flow;
}

bool bb(int k){
  int Nz = a+b+5, s = a+b+2, t = a+b+3;
  init(s,t,Nz);
  for(int i=0; i<a; i++) add(i+1, t, va[i]);
  for(int i=0; i<b; i++) add(s,i+a+1,vb[i]);
  for(int i=0; i<k+1; i++) add(1+a+ar[i].second.second, 1+ar[i].second.first, 1e11);
  ll val = sap();
  return val == sum;
}

int main(){
  scanf("%d%d%d", &a, &b, &m);
  for(int i=0; i<a; i++) scanf("%d", va+i), sum += va[i];
  for(int i=0; i<b; i++) scanf("%d", vb+i);
  for(int i=0; i<m; i++) scanf("%d%d%d", &ar[i].second.first, &ar[i].second.second, &ar[i].first), ar[i].second.first--, ar[i].second.second--;
  sort(ar,ar+m);
  int l = 0, r = m-1, ans = -1;
  while(l <= r){
    int mid = (l+r)/2;
    if(bb(mid)){
      ans = ar[mid].first;
      r = mid-1;
    }else l = mid+1;
  }
  printf("%d\n", ans);
}