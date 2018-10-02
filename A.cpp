#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb emplace_back
#define x first
#define y second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define EPS 3e-8
#define fcin ios_base::sync_with_stdio(false)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<
#define MAXN 101010
#define LOGN 20
typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;

ll n, m, mobius[MAXN], mod = 1e9+7;
char nprimo[MAXN];

ll solve(ll k, int estrito){
	ll ret = 0;
	for(ll d = 1; d <= n; d++){
		ll sd = 0;
		for(ll i = 1; i*d < n; i++){
			if(i*d > k - estrito) break;
			ll qt = min((ll)(sqrtl(k*k-(i*d)*(i*d))/d), m/d);
			ll a1 = m - d;
			while(m>(qt + 1)*d && k*k - estrito >= (i*d)*(i*d) + (qt + 1)*d*(qt +1)*d) qt++;
			while(!(m>qt*d && k*k - estrito >= (i*d)*(i*d) + qt*d*qt*d)) qt--;
			if(qt <= 0) continue;
			ll an = m - qt*d;
			ll cur = (a1 + an)*qt/2;
			cur %= mod;
			sd += (n-d*i) * cur;
			sd %= mod;
		}
		ret += sd*mobius[d] + mod;
		ret %= mod;
	}
	return (2*ret)%mod;
}

int main(){
	rep(i,0,MAXN) mobius[i]=1;
	rep(i,2,MAXN) if(!nprimo[i]){
		mobius[i] = -mobius[i];
		for(int j = i+i; j < MAXN; j+=i){
			if(j%(i*i) == 0) mobius[j] = 0;
			mobius[j] = -mobius[j];
			nprimo[j]=1;
		}
	}
	int l, r;
	scanf("%lld%lld%d%d", &n, &m, &l, &r);
	ll extra = (n*(m-1) + (n-1)*m)%mod;
	if(l > 1) extra = 0;
	printf("%lld\n", (solve(r,0) - solve(l,1) + extra + mod)%mod);
}
