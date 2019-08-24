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

class dfs
{
private:
vector < bool > marked;
vector < int > edge_to;
int s;
graph *g;

public:
dfs(graph &_g, const int &_s)
{
 s=_s;
 g=&_g;
 edge_to.resize(g->get_v());
 marked.resize(g->get_v());
 traverse(s);
}

void traverse(const int &v)
{
 marked[v]=true;
 for(int w:g->get_adj(v))
  if (!marked[w])
  {
   edge_to[w]=v;
   traverse(w);
  }
}

bool has_path_to(const int &v)
{
 return marked[v];
}

vector < int > path_to(const int &v)
{
vector < int > path;

 if (has_path_to(v))
 {
  for(int x=v;x!=s;x=edge_to[x]) path.push_back(x);
  path.push_back(s);
 }
 return path;
}
};
