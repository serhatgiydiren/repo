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
#define MAXN 105
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

class UnionFind
{
private:
vi parent,size;
int count;
vll temp;
ll mv;

public:
UnionFind(int n,vll a)
{
 count=n;
 mv=0;
 parent.resize(n);
 temp=a;
 D(temp);
 size.resize(n,1);
 FOR(i,0,n) parent[i]=i;
}

void setmax(ll val)
{
 mv=max(mv,val);
}

ll getmax()
{
 return mv;
}

int f(int p)
{
int root=p;

 while(root!=parent[root]) root=parent[root];
 while(p!=root)
 {
  int newp=parent[p];
  parent[p]=root;
  p=newp;
 }
 return root;
}

bool connected(int p, int q)
{
 return f(p)==f(q);
}

void u(int p, int q)
{
int rootP=f(p);
int rootQ=f(q);

 if (rootP==rootQ) return;
 if (size[rootP]<size[rootQ])
 {
  parent[rootP]=rootQ;
  size[rootQ]+=size[rootP];
  temp[rootQ]+=temp[rootP];
  setmax(temp[rootQ]);
 }
 else
 {
  parent[rootQ]=rootP;
  size[rootP]+=size[rootQ];
  temp[rootP]+=temp[rootQ];
  setmax(temp[rootP]);
 }
 count--;
 D(parent,size,temp,count);
}
};

void solve() {t1=clock();
int n;

 r(n);
 vll a(n);
 vi b(n);
 vb vis(n);
 FOR(i,0,n) r(a[i]);
 FOR(i,0,n) r(b[i]),b[i]--;
 D(a,b);
 UnionFind uf(n,a);
 vll res(n+1);
 ROF(i,0,n)
 {
  D(i,b[i]);
  uf.setmax(a[b[i]]);
  if (b[i]>0 && vis[b[i]-1]) uf.u(b[i]-1,b[i]);
  if (b[i]<n-1 && vis[b[i]+1]) uf.u(b[i]+1,b[i]);
  vis[b[i]]=true;
  res[n-i]=uf.getmax();
 }
 ROF(i,0,n) wl(res[i]);

PERF}

int main() {IO
//r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return EXIT_SUCCESS;
}
