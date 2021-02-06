// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e05

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
 
//#define DF cout
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
#define MAXN (1<<20)+5
#define MAXK 4000
#define MDL 1000000007
#define INF 1ll<<60
#define EPS 1e-9
#define IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); cout << fixed << setprecision(15);
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
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<> start(0,a*b);

const int ALPHABET_SIZE=26; 
const char FIRST_CHAR='A';

class trie
{ 
public:
trie* children[ALPHABET_SIZE];
bool isLeaf; // is true if the node represents end of a word
bool isRoot; // is true if the node represents end of a word

trie(const bool &is_root=false)
{
 isLeaf=false;
 isRoot=is_root;
 FOR(i,0,ALPHABET_SIZE) children[i]=NULL;
}

int get_index(const char &c)
{
 return c-FIRST_CHAR;
}

char set_char(const int &i)
{
 return char(FIRST_CHAR+i);
}

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(const string &key)
{ 
 trie* cur=this; 
 FOR(i,0,sz(key))
 {  
  int index=get_index(key[i]); 
  if (!cur->children[index]) cur->children[index]=new trie; 
  cur=cur->children[index]; 
 } 
 // mark last node as leaf 
 cur->isLeaf=true; 
} 

// Returns true if key presents in trie, else false
bool search(const string &key)
{ 
 trie* cur=this; 
 FOR(i,0,sz(key))
 {
  int index=get_index(key[i]);
  if (!cur->children[index]) return false; 
  cur=cur->children[index]; 
 } 
 return (cur!=NULL && cur->isLeaf); 
} 

void display(const string &str="", const int &level=0)
{ 
 trie* cur=this; 
 if (cur==NULL) return;
 if (cur->isLeaf) D(str);
 FOR(i,0,ALPHABET_SIZE)  
 { 
  if (cur->children[i])  
  {
   string temp=str+set_char(i); 
   cur->children[i]->display(temp,level+1); 
  } 
 } 
} 

// Returns true if root has no children, else false 
bool isEmpty()
{
 FOR(i,0,ALPHABET_SIZE) if (this->children[i]) return false; 
 return true; 
} 
 
// Recursive function to delete a key from given Trie 
trie* remove(const string &key, const int &depth=0) 
{
 trie *cur=this; 

 // If tree is empty 
 if (!cur) return NULL; 
  
 // If last character of key is being processed 
 if (depth==sz(key))
 { 
  // This node is no more end of word after removal of given key 
  if (cur->isLeaf) cur->isLeaf=false; 
  
  // If given is not prefix of any other word 
  if (cur->isEmpty())
  {
   delete(cur); 
   cur=NULL; 
  } 
  
  return cur; 
 } 
  
 // If not last character, recur for the child 
 // obtained using ASCII value 
 int index=get_index(key[depth]); 
 D(index);
 cur->children[index]=cur->children[index]->remove(key,depth+1);
 D(cur->children[index]==NULL);
  
 // If root does not have any child (its only child got  
 // deleted), and it is not end of another word. AND it is not ROOT 
 if (cur->isEmpty() && cur->isLeaf==false && !cur->isRoot)
 { 
  delete(cur);
  cur=NULL; 
 } 
  
 return cur; 
} 

int unpaired()
{
int res=0;

 trie *cur=this;
 if (cur->isLeaf) res++;
 FOR(i,0,ALPHABET_SIZE) if (cur->children[i])
 {
  res+=cur->children[i]->unpaired();
  D(set_char(i),res);
 }
 if (!cur->isRoot && res>=2) res-=2;
 return res;
}
}; 

int lcp(const string &a, const string &b)
{
 FOR(i,0,min(sz(a),sz(b))) if (a[i]!=b[i]) return i;
 return min(sz(a),sz(b));
}

void solve() {t1=clock();
int n;
string q;

 r(n);
 trie *root=new trie(true);
 FOR(i,0,n) r(q),reverse(all(q)),root->insert(q);
 root->display();
 cout << "Case #" << (tt+1) << ": " << n-root->unpaired() << endl;

PERF}

int main() {IO
r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return EXIT_SUCCESS;
}
