#include<bits/stdc++.h>
#define MAXN 2010
using namespace std;
typedef bitset<MAXN> tbs;
tbs gauss (vector < tbs > a, tbs b){
    int n = a.size();
    vector<int> where (n, -1);
    for (int col=0, row=0; col<n && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]){
                swap(a[i],a[row]);
                int t = b[i];
                b[i] = b[row];
                b[row] = t;
                break;
            }
        if (!a[row][col]) continue;
        where[col] = row;
        for (int i=row+1; i<n; ++i)
            if(a[i][col]){
                a[i]^=a[row];
                b[i]=b[i]^b[row];
            }
        ++row;
    }
    for(int i=0;i<n;i++){
        if(a[i].count()==0 && b[i]){
            printf("impossible\n");
            exit(0);
        }
    }
    tbs x;
    for(int i=n-1;i>=0;i--){
        if(where[i]==-1) x[i]=1;
        else x[i]=b[where[i]];
        if(x[i]) for(int j=0;j<i;j++) if(a[j][i]) b[j]=b[j]^1;
    }
    return x;
}
int main(){
    int n,m; scanf("%d %d",&m,&n);
    vector<tbs>mat(max(n,m),0);
    tbs res;
    for(int i=0;i<m;i++){
        scanf(" %*c");
        int impar=1;
        while(1){
            char c; scanf(" %c",&c);
            if(c=='n') scanf("%*c%*c %*c"),impar^=1;
            int id; scanf(" %d",&id); id--;
            mat[i][n-1-id]=mat[i][n-1-id]^1;
            scanf(" %c",&c);
            if(c=='o') scanf("%*c");
            else break;
        }
        if(i+1!=m) scanf(" %*c%*c%*c");
        if(impar) res.set(i);
        else res.reset(i);
    }
    res = gauss(mat, res);
    for(int i=0;i<n;i++) printf("%c",res[n-i-1]?'T':'F');
    printf("\n");
    return 0;
}
