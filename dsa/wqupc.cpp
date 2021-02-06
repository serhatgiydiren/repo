// Weighted Quick Union with Path Compression
class wqupc
{
private:
vector < int > parent;
vector < int > size;
int union_count;

public:
wqupc(const int &n)
{
 union_count=n;
 parent.resize(n);
 size.resize(n,1);
 for(int i=0;i<n;i++) parent[i]=i;
}

int root(int p)
{
 while(p!=parent[p])
 {
  parent[p]=parent[parent[p]]; // path compression
  p=parent[p];
 };
 return p;
}

bool is_connected(int p, int q)
{
 return root(p)==root(q);
}

void make_union(const int &p, const int &q)
{
int root_p=root(p);
int root_q=root(q);

 if (root_p==root_q) return;
 if (size[root_p]<size[root_q])
 {
  parent[root_p]=root_q;
  size[root_q]+=size[root_p];
 }
 else
 {
  parent[root_q]=root_p;
  size[root_p]+=size[root_q];
 }
 union_count--;
}
};
