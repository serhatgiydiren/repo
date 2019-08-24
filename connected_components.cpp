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

class connected_components
{
vector < bool > marked;
vector < vector < int > > groups;
vector < int > group;
graph *g;

public:
connected_components(graph &_g)
{
 g=&_g;
 marked.resize(g->get_v());
 for(int v=0;v<g->get_v();v++)
 {
  if (!marked[v])
  {
   group.clear();
   traverse(v);
   groups.push_back(group);
  }
 }
}

void traverse(const int &v)
{
 group.push_back(v);
 marked[v]=true;
 for(int w:g->get_adj(v)) if (!marked[w]) traverse(w);
}

vector < vector < int > > get_groups()
{
 return groups;
}
};
