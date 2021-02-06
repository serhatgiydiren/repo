// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

int r,c;
vector < vector < int > > delivery;
vector < string > x;

bool check(const int &k)
{
 int e[4]={INT_MAX,INT_MIN,INT_MAX,INT_MIN};
 
 for(int i=0;i<r;i++)
 {
  for(int j=0;j<c;j++) if (delivery[i][j]>k)
  {
   e[0]=min(e[0],i+j);
   e[1]=max(e[1],i+j);
   e[2]=min(e[2],i-j);
   e[3]=max(e[3],i-j);
  }
 }

 for(int i=0;i<r;i++)
 {
  for(int j=0;j<c;j++)
  {
   if(e[1]-(i + j)<=k && (i+j)-e[0]<=k && e[3]-(i-j)<=k && (i-j)-e[2]<=k) return true;
  }
 }
 
 return false;
}

void bfs()
{
 const pair < int , int > w[4]={{1,0},{-1,0},{0,1},{0,-1}};

 vector < vector < bool > > vis(r, vector < bool > (c));
 queue < pair < pair < int , int > , int > > q;
 for(int i=0;i<r;i++) for(int j=0;j<c;j++) if (x[i][j]=='1')
 {
  vis[i][j]=true;
  q.push({{i,j},0});
 }

 while(!q.empty())
 {
  auto f=q.front();
  q.pop();
  for(int i=0;i<4;i++)
  {
   int new_i=f.first.first+w[i].first;
   int new_j=f.first.second+w[i].second;
   if (new_i<0 || new_i>r-1) continue;
   if (new_j<0 || new_j>c-1) continue;
   if (vis[new_i][new_j]) continue;
   delivery[new_i][new_j]=f.second+1;
   vis[new_i][new_j]=true;
   q.push({{new_i,new_j},f.second+1});
  }
 }
}

void solve(const int &test_id)
{
 cin >> r >> c;
 delivery.assign(r, vector < int > (c,0));
 x.resize(r);
 for(int i=0;i<r;i++) cin >> x[i];
 bfs();
 int lo=0;
 int hi=r+c;
 while(lo<hi)
 {
  int mid=(lo+hi)>>1;
  if (check(mid)) hi=mid;
  else lo=mid+1;
 }
 cout << "Case #" << test_id << ": " << hi << endl;
}
            
void solve_cases()
{
 int test_cases=1;
 cin >> test_cases;
 for(int i=1;i<=test_cases;i++) solve(i);
}

void fast_io()
{
 ios::sync_with_stdio(false);
 srand(time(NULL));
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
