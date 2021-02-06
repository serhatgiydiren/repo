#define __USE_MINGW_ANSI_STDIO 0
 
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
 
#define DF cerr
#ifdef SGD
#define D(...) DF << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#define PERF cerr << "Case #" << (tt+1) << " " << 1.0 * (clock() - t1) / CLOCKS_PER_SEC << " ms" << endl;
#else
#define D(...) 404
#define PERF
#endif
 
string to_string(string s) { return '"' + s + '"'; }
string to_string(char c) { return '\'' + string(1,c) + '\''; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A> string to_string(A v) { bool first=true; string res="{"; for (const auto &x : v) { if (!first) res+=", "; first=false; res+=to_string(x); } res+="}"; return res; }
string to_string(vb v) { bool first=true; string res="{"; for(unsigned i=0;i<v.size();i++) { if (!first) res+=", "; first=false; res+=to_string(bool(v[i])); } res+="}"; return res; }
void debug_out() { DF << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { DF << " " << to_string(H); debug_out(T...); }
 
#define sz(a) int((a).size()) 
#define pb push_back 
#define F first
#define S second
#define all(c) (c).begin(),(c).end() 
#define rall(c) (c).rbegin(),(c).rend() 
#define tr(con,it) for (__typeof((con).begin()) it = con.begin(); it != con.end(); it++) 
#define wl(x) (cout << (x) << endl)
#define w(x) (cout << (x))
#define r(x) (cin >> (x))
#define FOR(i,a,b) for (auto i = (a); i < (b); i++)
#define ROF(i,a,b) for (auto i = (b-1); i >= (a); i--)
#define mp(x,y) make_pair((x),(y))
#define reset(x,v) memset((x),(v),sizeof(x))
#define LSOne(S) (S & (-S))
#define MAXN 1005
#define MAXK 300000
#define MDL 1000000007
#define INF 1ll<<60
#define EPS 1e-9
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define M_PI 3.14159265358979323846
#define V(vw,x,n,m,val) vector < vw > x(n,vw(m,val))
#define uniq(x) sort(all(x)), x.resize(unique(all(x))-x.begin())
 
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
string to_str(const int &n){ostringstream stm; stm << n;return stm.str();}
string to_str(const ll &n){ostringstream stm; stm << n;return stm.str();}
template<class T> string tostring(T x, int len = 0) {stringstream ss; ss << x; string r = ss.str(); if(sz(r) < len) r = string(len - sz(r), '0') + r; return r;}
template<class T> void convert(string x, T& r) {stringstream ss(x); ss >> r;}
ll powmod(ll a,ll b) {ll res=1;a%=MDL;for(;b;b>>=1){if(b&1)res=res*a%MDL;a=a*a%MDL;}return res;}
ll modinv(ll a) { return powmod(a, MDL-2); }
ll modinv(ll a,ll m) { return powmod(a, m-2); }
ll nCkMp(ll n, ll k) { ll numerator = 1,denominator = 1;for (int i=0; i<k; i++) numerator = (numerator * (n-i) ) % MDL;for (int i=1; i<=k; i++) denominator = (denominator * i) % MDL;return (numerator*modinv(denominator)) % MDL; }
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
ll lcm(ll a,ll b) {return a*(b/gcd(a,b));}
int TT=1,tt;
clock_t t1;

int n,k,best=INT_MIN;
vector < pair < pair < double , int > , ii > > x;
vb exclude_best;

int bound(vb ex)
{
int weight=0,value=0;

 FOR(i,0,n)
 {
  if (!ex[i])
  {
   value+=int(double(x[i].S.F)*double(min(x[i].S.S,k-weight))/x[i].S.S);
   weight+=min(x[i].S.S,k-weight);
   if (weight==k) break;
  }
 }
 return value;
}

int kn(int idx,vb exclude,int room,int value)
{
int r1=INT_MIN,r2=INT_MIN;
 
 if (value>best)
 {
  best=value;
  exclude_best=exclude;
 }
 if (idx==n) return value;
 if (room<x[idx].S.S)
 {
  exclude[idx]=true;
  return kn(idx+1,exclude,room,value);
 }
 int estimate_with_current=bound(exclude);
 if (estimate_with_current>=best) r1=kn(idx+1,exclude,room-x[idx].S.S,value+x[idx].S.F);
 exclude[idx]=true;
 int estimate_without_current=bound(exclude);
 if (estimate_without_current>=best) r2=kn(idx+1,exclude,room,value);

 return max(best,max(r1,r2));
}

void solve() {t1=clock();
 r(n);r(k);
 x.resize(n);
 vb exclude(n);
 FOR(i,0,n) r(x[i].S.F),r(x[i].S.S),x[i].F.F=double(x[i].S.F)/x[i].S.S,x[i].F.S=i;
 sort(rall(x));
 int res=kn(0,exclude,k,0);
 vb include(n,false);
 int tot1=0,tot2=0;
 FOR(i,0,n)
 {
  if (tot1==res) break;
  if (!exclude_best[i])
  {
   tot1+=x[i].S.F,tot2+=x[i].S.S;
   include[x[i].F.S]=true;
  }
 }
 cout << res << " 1" << endl;
 FOR(i,0,sz(include)) cout << include[i] << " ";

PERF}

int main() {//IO
//r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return EXIT_SUCCESS;
}
