const int ALPHABET_SIZE=26; 
const char FIRST_CHAR='a';
const int NOT_EXISTS=INT_MIN;

class node
{
public:
 int val=NOT_EXISTS;
 node *next[ALPHABET_SIZE];
};

int get_index(const char &c)
{
 return c-FIRST_CHAR;
}

char set_char(const int &i)
{
 return char(FIRST_CHAR+i);
}

class trie
{ 
private:
node *root;

node *put(node *x, const string &key, const int &val, const unsigned &d)
{
 if (x==NULL) x=new node();
 if (d==key.size()) x->val=val;
 else x->next[get_index(key[d])]=put(x->next[get_index(key[d])], key, val, d+1);
 return x;
}

node *get(node *x, const string &key, const unsigned &d)
{
 if (x==NULL) return NULL;
 if (d==key.size()) return x;
 return get(x->next[get_index(key[d])], key, d+1);
}

node *delete_node(node *x, const string &key, const unsigned &d)
{
 if (x==NULL) return NULL;
 if (d==key.size()) x->val=NOT_EXISTS;
 else x->next[get_index(key[d])]=delete_node(x->next[get_index(key[d])], key, d+1);
 if (x->val!=NOT_EXISTS) return x;
 for(int c=0;c<ALPHABET_SIZE;c++) if (x->next[c]!=NULL) return x;
 return NULL;
}

void collect(node *x, string prefix, vector < string > &res)
{
 if (x==NULL) return;
 if (x->val!=NOT_EXISTS) res.push_back(prefix);
 for(int i=0;i<ALPHABET_SIZE;i++)
 {
  prefix+=set_char(i);
  collect(x->next[i], prefix, res);
  prefix.resize(prefix.size()-1);
 }
}

int longest_prefix_of(node *x, const string &query, const unsigned &d, int length)
{
 if (x==NULL) return length;
 if (x->val!=NOT_EXISTS) length=d;
 if (d==query.size()) return length;
 return longest_prefix_of(x->next[get_index(query[d])], query, d+1, length);
}

void collect(node *x, string prefix, const string &pattern, vector < string > &res)
{
 if (x==NULL) return;
 unsigned d=prefix.size();
 if (d==pattern.size() && x->val!=NOT_EXISTS) res.push_back(prefix);
 if (d==pattern.length()) return;
 char c=pattern[d];
 if (c=='.')
 {
  for(int i=0;i<ALPHABET_SIZE;i++)
  {
   prefix+=set_char(i);
   collect(x->next[i], prefix, pattern, res);
   prefix.resize(prefix.size()-1);
  }
 }
 else
 {
  prefix+=c;
  collect(x->next[get_index(c)], prefix, pattern, res);
  prefix.resize(prefix.size()-1);
 }
}

public:
trie()
{
 root=NULL;
}

void put(const string &key, const int &val)
{
 root=put(root, key, val, 0);
}

bool contains(const string &key)
{
 return get(key)!=NOT_EXISTS;
}

int get(const string &key)
{
 node *x=get(root, key, 0);
 if (x==NULL) return NOT_EXISTS;
 return x->val;
}

void delete_node(const string &key)
{
 root=delete_node(root, key, 0);
}

vector < string > keys_with_prefix(const string &prefix)
{
 vector < string > res;
 node *x=get(root, prefix, 0);
 collect(x, prefix, res);
 return res;
}

vector < string > keys()
{
 return keys_with_prefix("");
}

string longest_prefix_of(const string &query)
{
 return query.substr(0, longest_prefix_of(root, query, 0, 0));
}

vector < string > keys_that_match(const string &pattern)
{
 vector < string > res;
 collect(root, "", pattern, res);
 return res;
}
};
