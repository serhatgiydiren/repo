// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

int sc,uc;
struct story
{
 int creator;
 vector < int > followers;
};
vector < story > stories;
vector < vector < bool > > z1,z2,us,ufu,ufs;

int f_a(int uid1,int uid2)
{
 if (uid1==uid2) return 0;
 if (ufu[uid1][uid2]) return 3;
 if (z1[uid1][uid2]) return 2;
 if (z2[uid1][uid2]) return 1;
 return 0;
}

int f_b(int uid2,int sid)
{
 if (us[uid2][sid]) return 2;
 if (ufs[uid2][sid]) return 1;
 return 0;
}

int score(int uid,int sid)
{
 if (us[uid][sid]) return -1;
 if (ufs[uid][sid]) return -1;
 int score=0;
 for(int i=1;i<=uc;i++) score+=(f_a(uid,i)*f_b(i,sid));
 return score;
}

void solve(const int &test_id)
{
 int user1,user2,st,ufu_count,ufs_count;
 cin >> sc >> uc;
 stories.resize(sc+1);

 ufu.assign(uc+1, vector < bool > (uc+1,false));
 z1.assign(uc+1, vector < bool > (uc+1,false));
 z2.assign(uc+1, vector < bool > (uc+1,false));

 ufs.assign(uc+1, vector < bool > (sc+1,false));
 us.assign(uc+1, vector < bool > (sc+1,false));

 for(int i=1;i<=sc;i++)
 {
  cin >> user1;
  stories[i].creator=user1;
  us[user1][i]=true;
 }
 cin >> ufu_count >> ufs_count;
 for(int i=0;i<ufu_count;i++)
 {
  cin >> user1 >> user2;
  ufu[user1][user2]=true;
 }
 for(int i=0;i<ufs_count;i++)
 {
  cin >> user1 >> st;
  stories[st].followers.push_back(user1);
  ufs[user1][st]=true;
 }
 for(auto s:stories)
 {
  for(auto f:s.followers)
  {
   z1[f][s.creator]=true;
   for(auto g:s.followers) z2[f][g]=true;
  }
 }
 for(int i=1;i<=uc;i++)
 {
  priority_queue < pair < int , int > > pq;
  for(int j=1;j<=sc;j++) pq.push({score(i,j),-j});
  int out=3;
  while(out--)
  {
   auto f=pq.top();
   pq.pop();
   cout << -f.second << " ";
  }
  cout << endl;
 }
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
