#include "bits/stdc++.h"

using namespace std;

int main()
{
    int ans = 0;
    string a, b;
    cin>>a>>b;
    for(int i=0; i<((int)a.size() - (int)b.size() + 1); i++)
    {
        bool ki = false;
        string temp = a.substr(i, (int)b.size()); 
        for(int j=0; j<(int)b.size(); j++)
        {
            if(temp[j] == b[j]) ki=true;
        }
        if(!ki) ans++;
    }
    printf("%d\n", ans);
}
