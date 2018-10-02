#include<bits/stdc++.h>
using namespace std;
struct circle{
    double x,y,r;
    circle(){};
    void read(){
        scanf("%lf %lf %lf",&x,&y,&r);
    }
};
circle c[200010];
int res=0,n;
vector<int>adj[200010];
bool cmp(circle a,circle b){
    return a.r<b.r;
}
bool tem_inter(circle maior,circle menor){
    return maior.r < menor.r + hypot( maior.x - menor.x, maior.y - menor.y);
}
void dfs(int ini,int atu){
    if(!tem_inter(c[ini],c[atu])) return;
    res+=2;
    if(res>2*n){
        printf("greater\n");
        exit(0);
    }
    for(int i : adj[atu]) dfs(ini,i);
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++) c[i].read();
    sort(c,c+n,cmp);
    set<int>raiz;
    for(int i=0;i<n;i++){
        for(int j : raiz){
            if(tem_inter(c[i],c[j]))dfs(i,j);
            else adj[i].push_back(j);
        }
        for(int j : adj[i]) raiz.erase(j);
        raiz.insert(i);
    }
    printf("%d\n",res);
    return 0; 
}
