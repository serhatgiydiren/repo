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
#ifdef SGD
#define PERF cerr << "Case #" << (tt+1) << " " << 1.0 * (clock() - t1) / CLOCKS_PER_SEC << " ms" << endl;
#else
#define PERF
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
#define F first
#define S second
#define all(c) (c).begin(),(c).end() 
#define rall(c) (c).rbegin(),(c).rend() 
#define tr(con,it) for (__typeof((con).begin()) it = con.begin(); it != con.end(); it++) 
#define wl(x) (cout << (x) << endl)
#define w(x) (cout << (x))
#define r(x) (cin >> (x))
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ROF(i,a,b) for (int i = (b-1); i >= (a); i--)
#define mp(x,y) make_pair((x),(y))
#define reset(x,v) memset((x),(v),sizeof(x))
#define LSOne(S) (S & (-S))
#define MAXN 100005
#define MAXK 22
#define MDL 1000000007
#define INF 1ll<<60
#define EPS 1e-10
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

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

class dfs_path
{
vb marked;
vi edge_to;
int s,count;
graph g;

public:
dfs_path(const graph &_g, const int &_s)
{
 count=0;
 s=_s;
 g=_g;
 edge_to.resize(g.get_v());
 marked.resize(g.get_v()); dfs(s);
}

void dfs(const int &v)
{
 count++;
 marked[v]=true;
 for(int w:g.get_adj(v))
  if (!marked[w])
  {
   edge_to[w]=v;
   dfs(w);
  }
}

bool has_path_to(const int &v)
{
 return marked[v];
}

vi path_to(const int &v)
{
vi path;

 if (has_path_to(v))
 {
  for(int x=v;x!=s;x=edge_to[x]) path.pb(x);
  path.pb(s);
 }
 return path;
}

int get_count()
{
 return count;
}
};

class bfs_path
{
int s,count;
graph g;
vb marked;
vi edge_to,dist_to;

public:
bfs_path(const graph &_g, const int &_s)
{
 count=0;
 s=_s;
 g=_g;
 dist_to.resize(g.get_v(),INT_MAX);
 edge_to.resize(g.get_v());
 marked.resize(g.get_v());
 bfs(s);
}

void bfs(const int &s)
{
 queue < int > q;
 dist_to[s]=0;
 marked[s]=true;
 q.push(s);
 count++;
 while(!q.empty())
 {
  int v=q.front();
  q.pop();
  for(int w:g.get_adj(v))
  {
   if (!marked[w])
   {
    edge_to[w]=v;
    dist_to[w]=dist_to[v]+1;
    marked[w]=true;
    q.push(w);
    count++;
   }
  }
 }
}

bool has_path_to(const int &v)
{
 return marked[v];
}

int get_dist_to(const int &v)
{
 return dist_to[v];
}

vi path_to(const int &v)
{
vi path;
 
 if (has_path_to(v))
 {
  int x;
  for(x=v;dist_to[x]!=0;x=edge_to[x]) path.pb(x);
  path.pb(x);
 }
 return path;
}

int get_count()
{
 return count;
}
};

class bipartite
{
bool is_bip;
vi color;

public:
bipartite(graph &g)
{
 is_bip=true;
 color.resize(g.get_v(),INT_MAX);
 queue < int > q;
 FOR(i,0,g.get_v())
 {
  if (color[i]!=INT_MAX) continue;
  q.push(i);
  color[i]=0;
  while(!q.empty() && is_bip)
  {
   int v=q.front();
   q.pop();
   for(int w:g.get_adj(v))
   {
    if (color[w]==INT_MAX)
    {
     color[w]=1-color[v];
     q.push(w);
    }
    else if (color[w]==color[v])
    {
     is_bip=false;
     break;
    }
   }
  }
  if (!is_bip) break;
 }
}

bool is_bipartite()
{
 return is_bip;
}

pair < vi , vi > get_colors()
{
vi c[2];

 FOR(i,0,sz(color)) c[color[i]].pb(i);
 return mp(c[0],c[1]);
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
 D(v);
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

void solve() {t1=clock();
int a,b,c,d;

 r(a);r(b);
 graph g(a);
 FOR(i,0,b)
 {
  r(c);r(d);
  g.add_edge(c,d);
 }

 bipartite bp(g);
 if (bp.is_bipartite())
 {
  pair < vi , vi > colors=bp.get_colors();
  wl(sz(colors.F));
  FOR(i,0,sz(colors.F)) cout << colors.F[i] << " "; cout << endl;
  wl(sz(colors.S));
  FOR(i,0,sz(colors.S)) cout << colors.S[i] << " "; cout << endl;
 }
 else wl(-1);

 FOR(s,0,g.get_v())
 {
  dfs_path dfsp(g,s);
  cout << "number of vertices connected to " << s << " : " << dfsp.get_count() << endl;
  FOR(v,0,g.get_v())
  {
   cout << s << " to " << v << " : ";
   if (dfsp.has_path_to(v))
   {
    vi path=dfsp.path_to(v);
    ROF(x,0,sz(path)) cout << path[x] << " ";
    cout << endl;
   }
   else cout << "NOT CONNECTED" << endl;
  }

  bfs_path bfsp(g,s);
  cout << "number of vertices connected to " << s << " : " << bfsp.get_count() << endl;
  FOR(v,0,g.get_v())
  {
   cout << s << " to " << v << " : (" << bfsp.get_dist_to(v) << ") : ";
   if (bfsp.has_path_to(v))
   {
    vi path=bfsp.path_to(v);
    ROF(x,0,sz(path)) cout << path[x] << " ";
    cout << endl;
   }
   else cout << "NOT CONNECTED" << endl;
  }
 }
  
 CC cc(g);
 D(cc.get_groups());

PERF}

int main() {IO
//r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return 0;
}	
