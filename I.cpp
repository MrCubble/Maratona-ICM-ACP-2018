#include "bits/stdc++.h"
#define MAXN 1001
using namespace std;

int main()
{
    int n, m, l;//Número de interruptores, lâmpadas e quantidade de lâmpadas acesas no início
    bitset<MAXN> v, u;
    vector <int> adj[MAXN];
    v.reset();
    u.reset();
    scanf("%d %d%*c", &n, &m);
    scanf("%d%*c", &l);
    for(int i=0; i<l; i++){
        int temp; scanf("%d%*c", &temp);
        v.flip(temp);
        u.flip(temp);
    }
    for(int i=1; i<=n; i++)
    {
        int a; scanf("%d", &a);
        for(int j=0; j<a; j++)
        {
            int b; scanf("%d", &b);
            adj[i].push_back(b);
        }
    }
    int ans = 0;
    while(true)
    {
        for(int i=1; i<=n; i++)
        {
            ans++;
            for(int j=0; j<(int)adj[i].size(); j++){
              v.flip(adj[i][j]);
            }
            if(v.none())
            {
                printf("%d\n", ans);
                return 0;
            }
        }
        if(v == u)
        {
            printf("-1\n");
            return 0;
        } 
    }
}
