class node
{
public:
char key;
int val;
int size;
node *left;
node *right;

node(const char &_key, const int &_val)
{
 key=_key;
 val=_val;
 size=1;
 left=right=NULL;
}
};

int node_size(node *x)
{
 if (x==NULL) return 0;
 return x->size;
}

class bst
{
private:
node *root;

node *put(node *x, const char &key, const int &value)
{
 if (x==NULL) x=new node(key,value);
 {
  if (key<x->key) x->left=put(x->left,key,value);
  else if (key>x->key) x->right=put(x->right,key,value);
  else x->val=value;
 }
 x->size=1+node_size(x->left)+node_size(x->right);
 return x;
}

int get(node *x, const char &key)
{
 if (x==NULL) return -1;
 if (key<x->key) return get(x->left,key);
 else if (key>x->key) return get(x->right,key);
 else return x->val;
}

node *min_node(node *x)
{
 if (x==NULL) return NULL;
 if (x->left==NULL) return x;
 return min_node(x->left);
}

node *max_node(node *x)
{
 if (x==NULL) return NULL;
 if (x->right==NULL) return x;
 return max_node(x->right);
}

node *floor_node(node *x, const char &key)
{
 if (x==NULL) return NULL;
 if (key==x->key) return x;
 if (key<x->key) return floor_node(x->left,key);
 if (key>x->key)
 {
  node *temp=floor_node(x->right,key);
  if (temp==NULL) return x;
  else return temp;
 }
}

node *ceil_node(node *x, const char &key)
{
 if (x==NULL) return NULL;
 if (key==x->key) return x;
 if (key>x->key) return ceil_node(x->right,key);
 if (key<x->key)
 {
  node *temp=ceil_node(x->left,key);
  if (temp==NULL) return x;
  else return temp;
 }
}

void inorder(node *x)
{
 if (x==NULL) return;
 inorder(x->left);
 cerr << x->key << " " << x->val << " " << x->size << endl;
 inorder(x->right);
}

void preorder(node *x)
{
 if (x==NULL) return;
 cerr << x->key << " " << x->val << " " << x->size << endl;
 preorder(x->left);
 preorder(x->right);
}

void postorder(node *x)
{
 if (x==NULL) return;
 postorder(x->left);
 postorder(x->right);
 cerr << x->key << " " << x->val << " " << x->size << endl;
}

// rank between (1,node_size(root))
node *ranked_node(node *x, const int &rank)
{
 if (x==NULL) return NULL;
 int t=node_size(x->left);
 if (t+1==rank) return x;
 if (t+1>rank) return ranked_node(x->left,rank);
 return ranked_node(x->right,rank-t-1);
}

// key count <= key
int rank(node *x, const char &key)
{
 if (x==NULL) return 0;
 if (key==x->key) return 1+node_size(x->left);
 if (key<x->key) return rank(x->left,key);
 return 1+node_size(x->left)+rank(x->right,key);
}

public:
bst()
{
 root=NULL;
}

int get(const char &key)
{
 return get(root,key);
}

void put(const char &key, const int &value)
{
 root=put(root,key,value);
}

node *min_node()
{
 return min_node(root);
}

node *max_node()
{
 return max_node(root);
}

node *floor_node(const char &key)
{
 return floor_node(root,key);
}

node *ceil_node(const char &key)
{
 return ceil_node(root,key);
}

void inorder()
{
 inorder(root);
}

void preorder()
{
 preorder(root);
}

void postorder()
{
 postorder(root);
}

node *ranked_node(const int &rank)
{
 return ranked_node(root,rank);
}

int rank(const char &key)
{
 return rank(root,key);
}
};
