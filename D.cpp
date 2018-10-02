#include "bits/stdc++.h"

using namespace std;

int main()
{
    int n, a, ans=0;
    scanf("%d%*c", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d%*c", &a);
        if(a!=1) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
