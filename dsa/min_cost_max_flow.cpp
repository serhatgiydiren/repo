// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/05/28 22:33:16

#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

class timer:high_resolution_clock
{
 const time_point start_time;
 
 public:
  timer(): start_time(now()) {}
  rep elapsed_time() const { return duration_cast<milliseconds>(now()-start_time).count();} 
};

mt19937 rng(steady_clock::now().time_since_epoch().count());
//uniform_int_distribution distr(1,123456789);

timer ttt;





// https://serhatgiydiren.github.io

#pragma GCC optimize ("O2")

auto _ = []() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    return 0;
}();


struct Edge
{
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int costx = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        costx += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }
    return costx;
}

class Solution
{
public:
 int minimumXORSum(vector<int>& nums1, vector<int>& nums2)
 {
  int n=(int)nums2.size();
  int V=2*n+2;
  int s=0;
  int t=V-1;
  vector < Edge > edges;
  for(int i=0;i<n;i++)
  {
   edges.push_back({s,i+1,1,0});
   edges.push_back({n+i+1,t,1,0});
  }
  for(int i=0;i<n;i++) for(int j=0;j<n;j++)
  {
   edges.push_back({i+1,n+1+j,1,nums1[i]^nums2[j]});
  }
  return min_cost_flow(V,edges,INT_MAX,s,t);
 }
};

void solve(const int &test_id)
{
 int n;
 cin >> n;
 vector < int > x(n),y(n);
 for(auto &e:x) cin >> e;
 for(auto &e:y) cin >> e;
 Solution sol;
 auto res=sol.minimumXORSum(x,y);
 D(res);
}

void solve_cases()
{
 int test_cases = 1;
 //cin >> test_cases;
 for(int i = 1; i <= test_cases; i++)
 {
  solve(i);
  D(ttt.elapsed_time());
 }
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
