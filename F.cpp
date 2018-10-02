#include<bits/stdc++.h>
using namespace std;
int t, n, m, tam=0;
bool vis[1010][1<<10];
int tab[1010][1<<10];
int foi[1010];
vector <int> adj[1010];
struct show{
    int ini, fim, val, palco;
    void read(){
        scanf("%d %d %d",&ini, &fim, &val);
    }
} shows[1010];

bool cmp(show a, show b){
    if(a.fim != b.fim)return a.fim < b.fim;
    return a.ini > b.ini;
}
void dfs(int atu){
    foi[atu] = t;
    for(int pos = atu + 1; pos < tam; pos++)
        if(foi[pos] != t && shows[atu].fim <= shows[pos].ini) dfs(pos);
}
int acha(int atu, int mask){

    int &res = tab[atu][mask];
    if(vis[atu][mask]) return res;
    vis[atu][mask] = true;

    if(mask == (1 << n) - 1) res = shows[atu].val;
    else res = -1e9;

    for(int pos: adj[atu]) res = max(res, shows[atu].val + acha(pos, mask | (1 << shows[pos].palco)));
    return res;
}
int main(){
    scanf("%d", &n);
    for(int i=0; i < n; i++){
        int p; scanf("%d", &p);
        while(p--){
            shows[tam].read();
            shows[tam++].palco = i;
        }
    }
    sort(shows, shows + tam, cmp);
    t=1;
    for(int i = 0; i < tam; i++){
        for(int j = i + 1; j < tam; j++){
            if(foi[j] != t && shows[i].fim <= shows[j].ini){
                adj[i].push_back(j);
                dfs(j);
            }
        }
        t++;
    }
    int res = -1;
    for(int i = 0; i < tam; i++){
        res=max(res, acha(i, (1 << shows[i].palco)));
    }
    printf("%d\n", res);
    return 0;
}
