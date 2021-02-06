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
 
#define DF cout
#ifdef SGD
#define D(...) DF << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define D(...) 404
#endif

string to_string(string s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A> string to_string(A v) { bool first=true; string res="{"; for (const auto &x : v) { if (!first) res+=", "; first=false; res+=to_string(x); } res+="}"; return res; }
void debug_out() { DF << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { DF << " " << to_string(H); debug_out(T...); }

#define sz(a) int((a).size()) 
#define pb push_back 
#define all(c) (c).begin(),(c).end() 
#define rall(c) (c).rbegin(),(c).rend() 
#define tr(con,it) for (__typeof((con).begin()) it = con.begin(); it != con.end(); it++) 
#define wl(x) (cout << (x) << endl)
#define w(x) (cout << (x))
#define r(x) (cin >> (x))
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ROF(i,a,b) for (int i = (b-1); i >= (a); i--)
#define mp(x,y) make_pair((x),(y))
#define reset(x,val) memset((x),val,sizeof(x))
#define LSOne(S) (S & (-S))
#define MAXN 100005
#define MAXK 22
#define MDL 1000000007
#define INF 1ll<<50
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
ll _n=1;
int t;
bool x[MAXN][26];
ll n;
int l;
vector < string > s;
string res="-";
bool found=false;

 reset(x,0);
 r(n);r(l);
 s.resize(n);
 FOR(i,0,n)
 {
  r(s[i]);
  FOR(j,0,sz(s[i])) x[j][s[i][j]-'A']=true;
 }
 sort(all(s));
 FOR(i,0,l)
 {
  t=0;
  FOR(j,0,26) if (x[i][j]) t++;
  _n*=t;
  if (_n>n) break;
 }
 if (n!=_n)
 {
  FOR(k,0,n)
  {
   res=s[k];
   FOR(i,0,l)
   {
    FOR(j,0,26)
    {
     if (x[i][j])
     {
      res[i]='A'+j;
      if (!binary_search(all(s),res)) { found=true; break; }
     }
    }
    if (found) break;
   }
   if (found) break;
  }
 }
 cout << "Case #" << (tt+1) << ": " << res << endl;
 
 cerr << "Case #" << (tt+1) << " " << 1.0 * (clock() - t1) / CLOCKS_PER_SEC << " ms" << endl;
}

int main() {IO
r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return 0;
}
