// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE=26; 
const char FIRST_CHAR='A';
const int NOT_EXISTS=0;

int n,k,res;

class node
{
public:
 int val=NOT_EXISTS;
 int cnt=0;
 node *next[ALPHABET_SIZE];
};

int get_index(const char &c)
{
 return c-FIRST_CHAR;
}

class trie
{ 
private:
node *root;

node *put(node *x, const string &key, const int &val, const unsigned &d)
{
 if (x==NULL) x=new node();
 x->cnt++;
 if (d==key.size()) x->val=d;
 else x->next[get_index(key[d])]=put(x->next[get_index(key[d])], key, val, d+1);
 return x;
}

int dfs(node *x, const unsigned &d)
{
 if (x==NULL) return 0;
 int rem=0;
 for(int i=0;i<ALPHABET_SIZE;i++) rem+=dfs(x->next[i],d+1);
 int ret=(x->cnt-rem)/k;
 res+=d*ret;
 return rem+ret*k;
}

node *get(node *x, const string &key, const unsigned &d)
{
 if (x==NULL) return NULL;
 if (d==key.size()) return x;
 return get(x->next[get_index(key[d])], key, d+1);
}

public:
trie()
{
 root=NULL;
}

int dfs()
{
 return dfs(root,0);
}

void put(const string &key, const int &val)
{
 root=put(root, key, val, 0);
}
};

void solve(const int &test_id)
{
 res=0;
 string s;
 cin >> n >> k;
 trie t;
 for(int i=0;i<n;i++)
 {
  cin >> s;
  t.put(s,i+1);
 }
 t.dfs();
 cout << "Case #" << test_id << ": " << res << endl;
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
