#define __USE_MINGW_ANSI_STDIO 0

#include <bits/stdc++.h>


using namespace std;

long long n,k,temp=0,best=LLONG_MIN;
vector < long long > x;
vector < bool > exclude_best;

long long bound(const vector < bool > &ex)
{
long long value=0;

 for(int i=0;i<n;i++)
 {
  if (!ex[i])
  {
   value+=min(x[i],k-x[i]);
   if (value>=k) break;
  }
 }
 return value;
}

long long kn(int idx,vector < bool > exclude,long long room,long long value)
{
 if (value>best)
 {
  cerr << best << " " << value << endl;
  best=value;
  exclude_best=exclude;
 }
 if (idx==n) return value;
 if (best==k) return best;
 if (room<x[idx])
 {
  exclude[idx]=true;
  return kn(idx+1,exclude,room,value);
 }
 long long current_best=best;
 long long estimate_with_current=bound(exclude);
 if (estimate_with_current>=best) current_best=max(current_best,kn(idx+1,exclude,room-x[idx],value+x[idx]));
 exclude[idx]=true;
 long long estimate_without_current=estimate_with_current-x[idx];
 if (estimate_without_current>=best) current_best=max(current_best,kn(idx+1,exclude,room,value));
 return current_best;
}

void solve() {
 cin >> k >> n;
 x.resize(n);
 vector < bool > exclude(n), include(n);
 for(int i=0;i<n;i++) cin >> x[i];
 long long res=kn(0,exclude,k,0);
 cerr << "res=" << res << endl;
 for(int i=0;i<n;i++)
 {
  if (temp==res) break;
  if (!exclude_best[i])
  {
   temp+=x[i];
   include[i]=true;
  }
 }
 cerr << "temp=" << temp << endl;
 long long res2=0;
 for(int i=0;i<n;i++) if (include[i]) res2++;
 cout << res2 << endl;
 for(int i=0;i<n;i++) if (include[i]) cout << i << " ";
 cout << endl;
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
