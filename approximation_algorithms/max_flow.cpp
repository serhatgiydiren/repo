#include <bits/stdc++.h>

using namespace std;

struct lib
{
 int id;
 int n;
 int t;
 int m;
 vector < int > bid;
};

vector < lib > q;

struct book
{
 int sc;
};

vector < book > p;

int b,l,d;
map < pair < int , int > , int > cost,capacity;

struct edge
{
 int from;
 int to;
 int capacity;
 int cost;
};

vector < vector < int > > adj;

const int INF=1e9;

void shortest_paths(int n, int v0, vector < int > &d, vector < int > &p)
{
 d.assign(n,INF);
 d[v0]=0;
 vector < bool > inq(n,false);
 queue < int > q;
 q.push(v0);
 p.assign(n,-1);

 while (!q.empty())
 {
  int u=q.front();
  q.pop();
  inq[u]=false;
  for (int v:adj[u])
  {
   if (capacity[make_pair(u,v)]>0 && d[v]>d[u]+cost[make_pair(u,v)])
   {
    d[v]=d[u]+cost[make_pair(u,v)];
    p[v]=u;
    if (!inq[v])
    {
     inq[v]=true;
     q.push(v);
    }
   }
  }
 }
}

int min_cost_flow(const int &N, const vector < edge > &edges, const int &K, const int &s, const int &t)
{
 cerr << "N=" << N << " K=" << K << " s=" << s << " t=" << t << " edges size=" << edges.size() << endl;
 adj.assign(N,vector < int >());
 cost.clear();
 capacity.clear();
 for (edge e:edges)
 {
  //cerr << e.from << " " << e.to << " " << e.capacity << " " << e.cost << endl;
  adj[e.from].push_back(e.to);
  adj[e.to].push_back(e.from);
  cost[make_pair(e.from,e.to)]=e.cost;
  cost[make_pair(e.to,e.from)]=-e.cost;
  capacity[make_pair(e.from,e.to)]=e.capacity;
 }

 int flow=0;
 int value=0;
 vector < int > d,p;
 while(flow<K)
 {
  shortest_paths(N,s,d,p);
  for(unsigned i=0;i<d.size();i++) cerr << "i=" << i << " d[i]=" << d[i] << " "; cerr << endl;
  for(unsigned i=0;i<p.size();i++) cerr << "i=" << i << " p[i]=" << p[i] << " "; cerr << endl;
  cerr << "d[t]=" << d[t] << endl;
  cerr << "d.size()=" << d.size() << " p.size()=" << p.size() << endl;
  if (d[t]==INF) break;
  // find max flow on that path
  int f=K-flow;
  int cur=t;
  while (cur!=s)
  {
   f=min(f,capacity[make_pair(p[cur],cur)]);
   cur=p[cur];
  }

  // apply flow
  flow+=f;
  value+=f*d[t];
  cur=t;
  while(cur!=s)
  {
   capacity[make_pair(p[cur],cur)]-=f;
   capacity[make_pair(cur,p[cur])]+=f;
   cur=p[cur];
  }
  cerr << "flow=" << flow << " value=" << value << endl;
 }

 if (flow<K) return -1;
 else return value;
}

void solve() {
 int s=0,t;
 srand(time(NULL));
 cin >> b >> l >> d;
 t=b+l+1;
 p.resize(b);
 vector < edge > edges;
 edge e;
 for(int i=0;i<b;i++)
 {
  cin >> p[i].sc;
  e.from=s;
  e.to=i+1;
  e.capacity=1;
  e.cost=-p[i].sc;
  edges.push_back(e);
 }
 q.resize(l);
 for(int i=0;i<l;i++)
 {
  q[i].id=i;
  cin >> q[i].n >> q[i].t >> q[i].m;
  q[i].bid.resize(q[i].n);
  for(int j=0;j<q[i].n;j++)
  {
   cin >> q[i].bid[j];
   e.from=q[i].bid[j]+1;
   e.to=b+1+i;
   e.capacity=1;
   e.cost=0;
   edges.push_back(e);
  }
  e.from=b+1+i;
  e.to=t;
  //e.capacity=min((d-q[i].t)*q[i].m,q[i].n);
  e.capacity=(d-q[i].t)*q[i].m;
  e.cost=0;
  edges.push_back(e);
 }
 cerr << min_cost_flow(b+l+2,edges,b,s,t) << endl;
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
