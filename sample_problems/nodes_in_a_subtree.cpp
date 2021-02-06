/*
You are given a tree that contains N nodes, each containing an integer u which corresponds to a lowercase character c in the string s using 1-based indexing.
You are required to answer Q queries of type [u, c], where u is an integer and c is a lowercase letter. The query result is the number of nodes in the subtree of node u containing c.
Signature
int[] countOfNodes(Node root, ArrayList<Query> queries, String s)
Input
A pointer to the root node, an array list containing Q queries of type [u, c], and a string s
Constraints
N and Q are the integers between 1 and 1,000,000
u is an integer between 1 and N
s is of the length of N, containing only lowercase letters
c is a lowercase letter contained in string s
Node 1 is the root of the tree
Output
An integer array containing the response to each query
Example

        1(a)
        /   \
      2(b)  3(a)

s = "aba"
RootNode = 1
query = [[1, 'a']]
Note: Node 1 corresponds to first letter 'a', Node 2 corresponds to second letter of the string 'b', Node 3 corresponds to third letter of the string 'a'.
output = [2]
Both Node 1 and Node 3 contain 'a', so the number of nodes within the subtree of Node 1 containing 'a' is 2.
*/

class Node
{
public:
int val;
vector < Node* > children;
  
Node()
{
 val=0;
 children=vector < Node* >();
}
  
Node(int _val)
{
 val=_val;
 children = vector < Node* >();
}
  
Node(int _val, vector < Node* > _children)
{
 val = _val;
 children = _children;
}
};

struct Query
{
 int v; 
 char c; 
};

const int N=26;

vector < vector < int > > dp;

vector < int > ut(Node* root, const string &s)
{
 vector < int > ans(N);
 if (root)
 {
  ans[s[root->val-1]-'a']++;
  for(auto e:root->children)
  {
   auto t=ut(e,s);
   for(int i=0;i<N;i++) ans[i]+=t[i];
  }
 }
 return dp[root->val-1]=ans;
}

vector < int > countOfNodes(Node* root, const vector < Query > &queries, const string &s)
{
 dp.assign(s.size(), vector < int > (N,0));
 int n=int(queries.size());
 vector < int > res(n);
 ut(root,s);
 for(int i=0;i<n;i++) res[i]=dp[queries[i].v-1][queries[i].c-'a'];
 return res;
}
