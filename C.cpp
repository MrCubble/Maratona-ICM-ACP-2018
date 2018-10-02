#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long llu;
struct point{
    llu v,id;
} p1[100010], p2[100010];
llu conta(vector <llu> &v){
    if(v.size()==1) return 0;
    vector <llu> a, b;
    for(llu i = 0; i < v.size() / 2; i++) a.push_back(v[i]);
    for(llu i = v.size() / 2; i < v.size(); i++) b.push_back(v[i]);
    llu cont = conta(a) + conta(b);
    a.push_back(1e9); b.push_back(1e9);
    llu i = 0, j = 0;
    for(llu atu = 0; atu < v.size(); atu++){
        if(a[i] <= b[j]) v[atu] = a[i++];
        else{
            v[atu] = b[j];
            cont += a.size() - i - 1;
            j++;
        }
    }
    return cont;
}
bool cmp(point a, point b){
    return a.v < b.v;
}
llu par[100010];
int main(){
    llu xf, yf; scanf("%llu %llu", &xf, &yf);
    llu h, v; scanf("%llu %llu", &h, &v);
    llu inter = 0;
    for(llu i = 0; i < h; i++){
        scanf("%llu %llu", &p1[i].v, &p2[i].v);
        p1[i].id = p2[i].id = i;
    }
    sort(p1, p1 + h, cmp);
    sort(p2, p2 + h, cmp);
    for(llu i = 0; i < h; i++){
        par[p2[i].id] = i;
    }
    vector<llu>vet;
    for(llu i = 0; i < h; i++){
        vet.push_back(par[p1[i].id]);
    }
    inter += conta(vet);
    for(llu i = 0; i < v; i++){
        scanf("%llu %llu", &p1[i].v, &p2[i].v);
        p1[i].id = p2[i].id = i;
    }
    sort(p1, p1 + v, cmp);
    sort(p2, p2 + v, cmp);
    for(llu i = 0; i < v; i++){
        par[p2[i].id] = i;
    }
    vet.clear();
    for(llu i = 0; i < v; i++){
        vet.push_back(par[p1[i].id]);
    }
    inter += conta(vet);
    llu res = inter + h*v + h + v + 1;
    printf("%llu\n", res);
    return 0;
}

