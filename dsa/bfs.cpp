class graph
{
private:
int v;
int e;
vector < vector < int > > adj;

public:
graph(const int &_v)
{
 v=_v;
 e=0;
 adj.resize(v);
}

void add_edge(const int &u, const int &v)
{
 e++;
 adj[u].push_back(v);
 adj[v].push_back(u);
}

int get_v()
{
 return v;
}

int get_e()
{
 return e;
}

vector < int > get_adj(const int &u)
{
 return adj[u];
}
};

class bfs
{
private:
int s;
graph *g;
vector < bool > marked;
vector < int > edge_to;
vector < int > dist_to;

public:
bfs(graph &_g, const int &_s)
{
 s=_s;
 g=&_g;
 dist_to.resize(g->get_v(),INT_MAX);
 edge_to.resize(g->get_v());
 marked.resize(g->get_v());
 traverse(s);
}

void traverse(const int &s)
{
 queue < int > q;
 dist_to[s]=0;
 marked[s]=true;
 q.push(s);
 while(!q.empty())
 {
  int v=q.front();
  q.pop();
  for(int w:g->get_adj(v))
  {
   if (!marked[w])
   {
    edge_to[w]=v;
    dist_to[w]=dist_to[v]+1;
    marked[w]=true;
    q.push(w);
   }
  }
 }
}

bool has_path_to(const int &v)
{
 return marked[v];
}

int get_dist_to(const int &v)
{
 return dist_to[v];
}

vector < int > path_to(const int &v)
{
vector < int > path;
 
 if (has_path_to(v))
 {
  int x;
  for(x=v;dist_to[x]!=0;x=edge_to[x]) path.push_back(x);
  path.push_back(x);
 }
 return path;
}
};
