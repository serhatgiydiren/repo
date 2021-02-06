// https://codeforces.com/contest/659/problem/E

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
#define MAXN (1<<18)
#define MAXK 18
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

class graph
{
int v,e;
vector < vi > adj;
public:
graph()
{
}

graph(const int &_v)
{
 v=_v;
 e=0;
 adj.resize(v);
}

void add_edge(const int &u, const int &v)
{
 e++;
 adj[u].pb(v);
 adj[v].pb(u);
}

int get_v()
{
 return v;
}

int get_e()
{
 return e;
}

int degree(const int &u)
{
 return sz(adj[u]);
}

vi get_adj(const int &u)
{
 return adj[u];
}
};

class CC
{
vb marked;
vi id;
vi size;
int count;        
graph g;
int gv;
vector < vi > groups;

public:
CC(graph &_g)
{
 count=0;
 g=_g;
 gv=g.get_v();
 marked.resize(gv);
 id.resize(gv);
 size.resize(gv);
 FOR(v,0,gv) if (!marked[v]) dfs(v),count++;
}

void dfs(const int &v)
{
 marked[v]=true;
 id[v]=count;
 size[count]++;
 for(int w:g.get_adj(v)) if (!marked[w]) dfs(w);
}

vector < vi > get_groups()
{
 groups.resize(count);
 FOR(i,0,gv) groups[id[i]].pb(i);
 return groups;
}
};

// Determines whether the undirected graph {@code G} has a cycle and,
// if so, finds such a cycle.
// @param G the undirected graph
class cycle
{
vb marked;
vi edge_to;
vi c;
graph g;

public:
cycle(const graph &_g)
{
 g=_g;
 marked.resize(g.get_v());
 edge_to.resize(g.get_v());
 //if (has_self_loop(g)) return;
 //if (has_parallel_edges(g)) return;
}

void cycle_scan(const int &start)
{
 c.clear();
 if (start==-1) { FOR(v,0,g.get_v()) if (!marked[v]) dfs(-1, v); }
 else dfs(-1, start);
}

// does this graph have a self loop?
// side effect: initialize cycle to be self loop
bool has_self_loop()
{
 FOR(v,0,g.get_v())
 {
  for(int w:g.get_adj(v))
  {
   if (v==w)
   {
    c.pb(v);
    c.pb(v);
    return true;
   }
  }
 }
 return false;
}

// does this graph have two parallel edges?
// side effect: initialize cycle to be two parallel edges
bool has_parallel_edges()
{
 FOR(v,0,g.get_v())
 {
  // check for parallel edges incident to v
  for(int w:g.get_adj(v))
  {
   if (marked[w])
   {
    c.pb(v);
    c.pb(w);
    c.pb(v);
    return true;
   }
   marked[w] = true;
  }

  for(int w:g.get_adj(v)) marked[w]=false;
 }
 return false;
}

// Returns true if the graph {@code G} has a cycle.
// @return {@code true} if the graph has a cycle; {@code false} otherwise
bool has_cycle()
{
 return !c.empty();
}

// Returns a cycle in the graph {@code G}.
// @return a cycle if the graph {@code G} has a cycle,
// and {@code null} otherwise
vi get_cycle()
{
 return c;
}

void dfs(const int &u, const int &v)
{
 marked[v]=true;
 for(int w:g.get_adj(v))
 {
  // short circuit if cycle already found
  if (has_cycle()) return;
  if (!marked[w])
  {
   edge_to[w]=v;
   dfs(v,w);
  }

  // check for cycle (but disregard reverse of edge leading to v)
  else if (w!=u)
  {
   c.clear();
   for (int x=v;x!=w;x=edge_to[x]) c.pb(x);
   c.pb(w);
   c.pb(v);
  }
 }
}
};

void solve() {t1=clock();
int n,m,a,b,res=0;

 r(n);r(m);
 graph g(n);
 FOR(i,0,m)
 {
  r(a);r(b);
  g.add_edge(--a,--b);
 }
 CC cc(g);
 auto groups=cc.get_groups();
 D(groups);
 cycle c(g);
 FOR(i,0,sz(groups))
 {
  c.cycle_scan(groups[i][0]);
  if (!c.has_cycle()) res++,D(c.get_cycle());
 }
 D(res);
 wl(res);

PERF}

int main() {IO
//r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return EXIT_SUCCESS;
}
