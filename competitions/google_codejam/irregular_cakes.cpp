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
#define MAXN 1005
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
int w,l,u,g;
double res=0;

 r(w);r(l);r(u);r(g);
 vector < pair < int , pair < double , double > > > x(l+u);
 FOR(i,0,l) { r(x[i].first); r(x[i].second.first); x[i].second.second=-2000; }
 FOR(i,l,l+u) { r(x[i].first); r(x[i].second.second); x[i].second.first=-2000; }
 sort(all(x));
 FOR(i,1,sz(x))
 {
  if (x[i].first==x[i-1].first)
  {
   x[i-1].second.first=max(x[i-1].second.first,x[i].second.first);
   x[i-1].second.second=max(x[i-1].second.second,x[i].second.second);
   x.erase(x.begin()+i);
   i--;
  }
 }
 FOR(i,1,sz(x)-1)
 {
  if (x[i].second.first==-2000)
  {
   FOR(j,i+1,sz(x))
   {
    if (x[j].second.first!=-2000)
    {
     x[i].second.first=(((x[j].second.first-x[i-1].second.first)/(x[j].first-x[i-1].first))*(x[i].first-x[i-1].first))+x[i-1].second.first;
     break;
    }
   }
  }
 }
 FOR(i,1,sz(x)-1)
 {
  if (x[i].second.second==-2000)
  {
   FOR(j,i+1,sz(x))
   {
    if (x[j].second.second!=-2000)
    {
     x[i].second.second=(((x[j].second.second-x[i-1].second.second)/(x[j].first-x[i-1].first))*(x[i].first-x[i-1].first))+x[i-1].second.second;
     break;
    }
   }
  }
 }
 vector < double > a(sz(x)-1);
 double ta=0,eta=0,cta=0;
 int curr_a_index=0;
 FOR(i,0,sz(x)-1) { a[i]=(x[i+1].second.second-x[i+1].second.first+x[i].second.second-x[i].second.first)*(x[i+1].first-x[i].first)/2.0; ta+=a[i]; }
 cout << "Case #" << (tt+1) << ": " << endl;
 FOR(i,1,g)
 {
  eta=(ta*i)/g;
  while(a[curr_a_index]<(eta-cta)) cta+=a[curr_a_index++];
  double v1=x[curr_a_index].second.second-x[curr_a_index].second.first;
  double v2=x[curr_a_index+1].second.second-x[curr_a_index+1].second.first;
  
  if (v1-v2>EPS)
  {
   double b=(x[curr_a_index+1].first-x[curr_a_index].first)*v2/(v1-v2);
   double s1=v2*b/2.0;
   double z=b/sqrt(s1/(s1+(a[curr_a_index]-(eta-cta))));
   res=x[curr_a_index+1].first+b-z;
  }
  else if (v2-v1>EPS)
  {
   double b=(x[curr_a_index+1].first-x[curr_a_index].first)*v1/(v2-v1);
   double s1=v1*b/2.0;
   double z=b/sqrt(s1/(s1+(eta-cta)));
   res=x[curr_a_index].first+z-b;
  }
  else
  {
   double z=(x[curr_a_index+1].first-x[curr_a_index].first)*((eta-cta)/a[curr_a_index]);
   res=x[curr_a_index].first+z;
  }
  cout << fixed << setprecision(6) << res << endl;

  if ((ta*(i+1))/g-cta+a[curr_a_index]<EPS) cta+=a[curr_a_index++];
 }

 cerr << "Case #" << (tt+1) << " " << 1.0 * (clock() - t1) / CLOCKS_PER_SEC << " ms" << endl;
}

int main() {IO
r(TT);
 for(tt=0;tt<TT;tt++) solve();
 return 0;
}
