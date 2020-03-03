// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

struct fenwick
{
 vector < long long > B1;
 vector < long long > B2;

 fenwick(const vector < long long > &a)
 {
  B1.resize(a.size()+1);
  B2.resize(a.size()+1);
  for(size_t i=0;i<a.size();i++) range_add(i,i,a[i]);
 }

 long long sum(const vector < long long > &b, int idx)
 {
  long long ret=0;
  for (++idx;idx>0;idx-=idx&-idx) ret+=b[idx];
  return ret;
 }

 void add(vector < long long > &b, int idx, const long long &delta)
 {
  for(++idx;idx<int(b.size());idx+=idx&-idx) b[idx]+=delta;
 }

 //a[l]+=delta...a[r]+=delta
 void range_add(const int &l, const int &r, const long long &delta)
 {
  add(B1,l,delta);
  add(B1,r+1,-delta);
  add(B2,l,delta*(l-1));
  add(B2,r+1,-delta*r);
 }

 long long prefix_sum(const int &idx)
 {
  return sum(B1,idx)*idx-sum(B2,idx);
 }

 //sum(a[l]..a[r])
 long long range_sum(const int &l, const int &r)
 {
  return prefix_sum(r)-prefix_sum(l-1);
 }
};

void solve(const int &test_id)
{
 int n,lb;
 long long res=0;
 cin >> n;
 vector < pair < int , int > > x(n);
 vector < int > v(n);
 for(int i=0;i<n;i++) cin >> x[i].first;
 for(int i=0;i<n;i++) cin >> x[i].second,v[i]=x[i].second;
 sort(x.begin(),x.end());
 sort(v.begin(),v.end());
 v.resize(unique(v.begin(),v.end())-v.begin());
 vector < long long > ff(v.size());
 vector < long long > gg(v.size());
 fenwick f(ff);
 fenwick g(gg);
 for(int i=0;i<n;i++)
 {
  lb=lower_bound(v.begin(),v.end(),x[i].second)-v.begin();
  res+=g.range_sum(0,lb)*x[i].first-f.range_sum(0,lb);
  f.range_add(lb,lb,x[i].first);
  g.range_add(lb,lb,1);
 }
 cout << res << endl;
}
            
void solve_cases()
{
 int test_cases=1;
 //cin >> test_cases;
 for(int i=1;i<=test_cases;i++) solve(i);
}

void fast_io()
{
 ios::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cout << fixed << setprecision(15);
 cerr << fixed << setprecision(15);
}

int main()
{
 fast_io();
 solve_cases();
 return EXIT_SUCCESS;
}
