/*
In this problem, you are given an integer N, and a permutation, P of the integers from 1 to N, denoted as (a_1, a_2, ..., a_N). You want to rearrange the elements of the permutation into increasing order, repeatedly making the following operation:
Select a sub-portion of the permutation, (a_i, ..., a_j), and reverse its order.
Your goal is to compute the minimum number of such operations required to return the permutation to increasing order.
Signature
int minOperations(int[] arr)
Input
Size N is between 1 and 8
Array arr is a permutation of all integers from 1 to N
Output
An integer denoting the minimum number of operations required to arrange the permutation in increasing order
Example
If N = 3, and P = (3, 1, 2), we can do the following operations:

    Select (1, 2) and reverse it: P = (3, 2, 1).
    Select (3, 2, 1) and reverse it: P = (1, 2, 3).

output = 2
*/

int minOperations(const vector < int > &arr)
{
 int n=int(arr.size());
 vector < int > target(n);
 iota(target.begin(),target.end(),1);
 map < vector < int > , int > m;
 do m[target]=INT_MAX;
  while(next_permutation(target.begin(),target.end()));
 queue < pair < vector < int > , int > > q;
 q.push({arr,0});
 while(!q.empty())
 {
  auto f=q.front();
  q.pop();
  m[f.first]=f.second;
  for(int i=0;i<n;i++)
  {
   for(int j=i+1;j<n;j++)
   {
    auto t=f.first;
    reverse(t.begin()+i,t.begin()+j+1);
    if (m[t]==INT_MAX) q.push({t,f.second+1});
   }
  }
 }
 return m[target];
}
