#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair < int , int > ii;
typedef vector < ii > vii;
typedef vector < bool > vb;
typedef vector < int > vi;
typedef vector < ll > vll;
typedef vector < string > vs;
typedef vector < vll > matrix;
 
#define sz(a) int((a).size()) 
#define sl(a) int((a).length()) 
#define pb push_back 
#define all(c) (c).begin(),(c).end() 
#define rall(c) (c).rbegin(),(c).rend() 
#define tr(con,it) for (__typeof((con).begin()) it = con.begin(); it != con.end(); it++) 
#define wl(x) (cout << (x) << endl)
#define w(x) (cout << (x))
#define r(x) (cin >> (x))
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ROF(i,a,b) for (int i = (b-1); i >= (a); i--)
#define PP(x) tr(x,it) cout << it->first << " " << it->second << endl
#define mp(x,y) make_pair((x),(y))
#define reset(x) memset((x),0,sizeof((x)))
#define D1(x) cout << #x << " = " << x << endl
#define D2(x,y) cout << #x << " = " << x << " " << #y << " = " << y << endl
#define D3(x,y,z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << endl
#define D4(x,y,z,t) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " " << #t << " = " << t << endl
#define D5(x,y,z,t,v) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " " << #t << " = " << t << " " << #v << " = " << v << endl
#define LSOne(S) (S & (-S))
#define MAXN 1000005
#define MAXK int(sqrt(MAXN))
#define MDL 1000000007
#define EPS 1e-10
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
string to_str(const int &n){ostringstream stm; stm << n;return stm.str();}
string to_str(const ll &n){ostringstream stm; stm << n;return stm.str();}
template<class T> string tostring(T x, int len = 0) {stringstream ss; ss << x; string r = ss.str(); if(sz(r) < len) r = string(len - sz(r), '0') + r; return r;}
template<class T> void convert(string x, T& r) {stringstream ss(x); ss >> r;}
ll powmod(ll a,ll b) {ll res=1;a%=MDL;for(;b;b>>=1){if(b&1)res=res*a%MDL;a=a*a%MDL;}return res;}
ll modinv(ll a) { return powmod(a, MDL-2); }
ll nCkMp(ll n, ll k) { ll numerator = 1,denominator = 1;for (int i=0; i<k; i++) numerator = (numerator * (n-i) ) % MDL;for (int i=1; i<=k; i++) denominator = (denominator * i) % MDL;return (numerator*modinv(denominator)) % MDL; }
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
ll lcm(ll a,ll b) {return a*(b/gcd(a,b));}
int TT=1,tt;
clock_t t1;

void solve() {t1=clock();
int n,p,q,z,res=0;

 r(n);r(p);
 vi y(p);
 FOR(i,0,n)
 {
  r(q);
  y[q%p]++;
 }
 if (p==2) res=y[0]+(y[1]+1)/2;
 else if (p==3) res=y[0]+min(y[1],y[2])+(max(y[1],y[2])-min(y[1],y[2])+2)/3;
 else if (p==4)
 {
  res=y[0]+(y[2]+1)/2;
  y[2]%=2;
  z=min(y[1],y[3]);
  res+=z;
  y[1]-=z;
  y[3]-=z;
  if (y[2])
  {
   if (y[1]) y[1]-=min(y[1],2);
   else if (y[3]) y[3]-=min(y[3],2);
  }
  if (y[1]) res+=((y[1]+3)/4);
  else if (y[3]) res+=((y[3]+3)/4);
 }

 cout << "Case #" << (tt+1) << ": " << res << endl;

 cerr << "Case #" << (tt+1) << " " << 1.0 * (clock() - t1) / CLOCKS_PER_SEC << " ms" << endl;
}

int main() {IO
r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return 0;
}
