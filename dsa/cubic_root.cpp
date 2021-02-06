// https://codeforces.com/problemset/problem/833/A

ll cubic_root(ll x)
{
ll l=0,r=MAXN;

 while (l!=r)
 {
  ll m=(l+r+1)/2;
  if (m*m*m>x) r=m-1;
  else l=m;
 }
 return l;
}
