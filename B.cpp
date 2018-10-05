#include <bits/stdc++.h>
 
using namespace std;
 
typedef pair<int,int> ii;
typedef vector<ii> vii;
 
int tab[120][120];
 
int grungy(int x, int y) {
  int &res = tab[x][y];
  //printf("##%d %d\n",x,y);
  if(res!=-2) return res;
  if(x==0 || y==0 || x==y) return res=-1;
  int i,j;
  res=0;
  int foi[1000];
  for(i=0;i<1000;i++) foi[i]=0;
  for(i=x-1;i>=0;i--) {
      foi[grungy(i,y)+1]=1;
  }
  for(i=y-1;i>=0;i--) {
      foi[grungy(x,i)+1]=1;
  }
  int mn=min(x,y);
  for(i=1;i<mn;i++) {
      foi[grungy(x-i,y-i)+1]=1;
  }
  for(i=0;foi[i];i++);
  return res=i-1;
}
 
 
int main() {
  int n,i,j;
  vii bolas;
  scanf("%d",&n);
  for(i=0;i<120;i++) for(j=0;j<120;j++) tab[i][j]=-2;
  for(i=0;i<n;i++) {
    int a,b;
    scanf("%d %d",&a,&b);
    bolas.push_back(ii(a,b));
  }
  int xr=0;
  int flag=0;
  for(i=0;i<bolas.size();i++) {
    int ax=grungy(bolas[i].first,bolas[i].second);
    if(ax==-1) flag=1;
    xr^=ax;
  }
  if(flag || xr) printf("Y\n");
  else printf("N\n");
}