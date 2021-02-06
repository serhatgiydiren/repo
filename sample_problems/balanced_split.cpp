/*
Given a set of integers (which may include repeated integers), determine if there's a way to split the set into two subsets A and B such that the sum of the integers in both sets is the same, and all of the integers in A are strictly smaller than all of the integers in B.
Signature
bool balancedSplitExists(int[] arr)
Input
All integers in array are in the range [0, 1,000,000,000].
Output
Return true if such a split is possible, and false otherwise.
Example 1
arr = [1, 5, 7, 1]
output = true
We can split the set into A = {1, 1, 5} and B = {7}.
Example 2
arr = [12, 7, 6, 7, 6]
output = false
We can't split the set into A = {6, 6, 7} and B = {7, 12} since this doesn't satisfy the requirement that all integers in A are smaller than all integers in B.
*/

bool balancedSplitExists(const vector < int > &arr)
{
 int n=int(arr.size());
 vector < long long > x(n+1);
 for(int i=0;i<n;i++) x[i+1]=arr[i];
 sort(x.begin(),x.end());
 for(int i=1;i<n+1;i++) x[i]+=x[i-1];
 if (x[n]%2==0)
 {
  int lb=lower_bound(x.begin(),x.end(),x[n]/2)-x.begin();
  if (2*x[lb]==x[n] && x[lb]-x[lb-1]<x[lb+1]-x[lb]) return true;
 }
 return false;
}
