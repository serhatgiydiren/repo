// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

struct stone
{
 int eat;
 int energy;
 int loss;
};

int n;
vector < stone > s;
vector < vector < int > > dp;

bool lt(const stone &s1, const stone &s2)
{
 return s1.eat*s2.loss<s1.loss*s2.eat;
}

int ut(const int &elapsed, const int &idx)
{
 if (idx==n) return 0;
 if (dp[elapsed][idx]!=-1) return dp[elapsed][idx];
 return dp[elapsed][idx]=max(ut(elapsed,idx+1),ut(elapsed+s[idx].eat,idx+1)+max(0,s[idx].energy-elapsed*s[idx].loss));
}

void solve(const int &test_id)
{
 int ts=0;
 cin >> n;
 s.resize(n);
 for(int i=0;i<n;i++) cin >> s[i].eat >> s[i].energy >> s[i].loss,ts+=s[i].eat;
 dp.assign(ts, vector < int > (n,-1));
 sort(s.begin(),s.end(),lt);
 cout << "Case #" << test_id << ": " << ut(0,0) << endl;
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
