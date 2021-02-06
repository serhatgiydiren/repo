/*
Suppose we have a list of N numbers, and repeat the following operation until we're left with only a single number: Choose any two consecutive numbers and replace them with their sum. Moreover, we associate a penalty with each operation equal to the value of the new number, and call the penalty for the entire list as the sum of the penalties of each operation.
Note: Consecutive numbers means that their indices in the array are consecutive, not that their values are consecutive.
For example, given the list [1, 2, 3, 4, 5], we could choose 2 and 3 for the first operation, which would transform the list into [1, 5, 4, 5] and incur a penalty of 5. The goal in this problem is to find the worst possible penalty for a given input.
Signature:
int getTotalTime(int[] arr)
Input:
An array arr containing N integers, denoting the numbers in the list.
Output format:
An int representing the worst possible total penalty.
Constraints:
1 ≤ N ≤ 106
1 ≤ Ai ≤ 107, where *Ai denotes the ith initial element of an array.
The sum of values of N over all test cases will not exceed 5 * 106.
Example
arr = [4, 2, 1, 3]
output = 23
First, add 4 + 2 for a penalty of 6. Now the array is [6, 1, 3]
Add 6 + 1 for a penalty of 7. Now the array is [7, 3]
Add 7 + 3 for a penalty of 10. The penalties sum to 23.
*/

int getTotalTime_brute_force(const vector < int > &arr)
{
 int res=0;
 queue < pair < vector < int > , int > > q;
 q.push({arr,0});
 while(!q.empty())
 {
  auto f=q.front();
  auto g=f.first;
  res=max(res,f.second);
  q.pop();
  for(int i=0;i<int(g.size())-1;i++)
  {
   auto t=g;
   t[i]+=t[i+1];
   t.erase(t.begin()+i+1);
   q.push({t,f.second+t[i]});
  }
 }
 return res;
}

int getTotalTime_optimal(const vector < int > &arr)
{
 int res=0;
 for(int j=1;j<=int(arr.size());j++)
 {
  int i=j;
  vector < int > f=arr;
  f.insert(f.begin(),-1);
  f.push_back(-1);
  int tres=0;
  while(f[i-1]!=-1 || f[i+1]!=-1)
  {
   int max_left=*max_element(f.begin(),f.begin()+i);
   int max_right=*max_element(f.begin()+i+1,f.end());
   int max_elem=max(max_left,max_right),c;
   if (max_left>max_right) c=-1;
   else c=1;
   bool seen=false;
   while(!seen)
   {
    if (f[i+c]==max_elem) seen=true;
    f[i]+=f[i+c];
    tres+=f[i];
    f.erase(f.begin()+i+c);
    if (c==-1) i--;
   }
  }
  res=max(res,tres);
 }
 return res;
}
