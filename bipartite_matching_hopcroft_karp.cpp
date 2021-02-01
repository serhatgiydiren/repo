class BipGraph
{
 int m, n;
 vector < vector < int > > adj;
 vector < int > pairU;
 vector < int > pairV;
 vector < int > dist;
 
public:
 BipGraph(int _m, int _n)
 {
  this->m = _m;
  this->n = _n;
  adj.assign(m+1, vector < int > ());
 }

 bool bfs()
 {
  queue < int > Q;
  for(int u=1;u<=m;u++)
  {
   if (pairU[u] == 0)
   {
    dist[u] = 0;
    Q.push(u);
   }
   else dist[u] = INT_MAX;
  }
  dist[0] = INT_MAX;
  
  while (!Q.empty())
  {
   int u = Q.front();
   Q.pop();
   if (dist[u] < dist[0])
   {
    for(auto v:adj[u])
    {
     if (dist[pairV[v]] == INT_MAX)
     {
      dist[pairV[v]] = dist[u] + 1;
      Q.push(pairV[v]);
     }
    }
   }
  }

  return (dist[0] != INT_MAX);
 }
 
 bool dfs(int u)
 {
  if (u)
  {
   for(auto v:adj[u])
   {
    if (dist[pairV[v]]==dist[u]+1)
    {
     if (dfs(pairV[v]))
     {
      pairV[v]=u;
      pairU[u]=v;
      return true;
     }
    }
   }

   dist[u]=INT_MAX;
   return false;
  }
  return true;
 } 

 void addEdge(int u, int v)
 {
  adj[u].push_back(v);
 }

 int hopcroftKarp()
 {
  pairU.assign(m+1,0);
  pairV.assign(n+1,0);
  dist.assign(m+1,0);
  int result=0;
  while (bfs()) for(int u=1;u<=m;u++) if (pairU[u]==0 && dfs(u)) result++;
  return result;
 }
 
 vector < int > matchingsU()
 {
  vector < int > res(m);
  for(int i=1;i<=m+1;i++)
  {
   if (pairU[i]==0) res[i-1]=-1;
   else res[i-1]=pairU[i];
  }
  return res;
 }
};
