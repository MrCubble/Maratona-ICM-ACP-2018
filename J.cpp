#include "bits/stdc++.h"
#define MAXSP 110
#define MAXT 11
#define MAXST 1<<11
#define INF 1e20

using namespace std;

typedef pair<int,int> pii;
pii cord[MAXSP];
double pd[MAXSP][MAXST], res;

double dist(pii a, pii b)
{
    return hypot(a.first - b.first, a.second - b.second);
}

int main()
{
    int n, k;
    res = INF;
    scanf("%d %d%*c", &n, &k);
    for(int i=0; i<MAXSP; i++) for(int j=0; j<(1<<11); j++) pd[i][j] = INF;
    for(int i=0; i<n; i++) scanf("%d %d%*c", &cord[i].first, &cord[i].second);
    for(int i=0; i<k; i++)//Distância dos terminais para todos os pontos do espaço
    {
        for(int j=k; j<n; j++) pd[j][1<<i] = dist(cord[i], cord[j]);
    }
    for(int masc=1; masc<(1<<k); masc++)//Laço para todos os subconjuntos de terminais {00000000, 00000001... etc}
    {
        for(int j=k; j<n; j++)//Laço para todos os nós, ou seja, pontos de steiner
        {
            for(int sub = masc; sub>0; sub = (sub-1)&masc)//Laço para os subconjuntos desse atual
                pd[j][masc] = min(pd[j][masc], pd[j][sub] + pd[j][masc^sub]);
            for(int i=k; i<n; i++) pd[i][masc] = min(pd[i][masc], pd[j][masc] + dist(cord[i], cord[j]));//Atualizo os nós anteriores
            if(masc == ((1<<k)-1)) res = min(res, pd[j][masc]);
        }
    }
    printf("%.5lf\n", res);
}
