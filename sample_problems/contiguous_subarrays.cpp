/*
You are given an array a of N integers. For each index i, you are required to determine the number of contiguous subarrays that fulfills the following conditions:

    The value at index i must be the maximum element in the contiguous subarrays, and
    These contiguous subarrays must either start from or end with i.

Signature
int[] countSubarrays(int[] arr)
Input

    Array a is a non-empty list of unique integers that range between 1 to 1,000,000,000
    Size N is between 1 and 1,000,000

Output
An array where each index i contains an integer denoting the maximum number of contiguous subarrays of a[i]
Example:
a = [3, 4, 1, 6, 2]
output = [1, 3, 1, 5, 1]
Explanation:

    For index 0 - [3] is the only contiguous subarray that starts (or ends) with 3, and the maximum value in this subarray is 3.
    For index 1 - [4], [3, 4], [4, 1]
    For index 2 -[1]
    For index 3 - [6], [6, 2], [1, 6], [4, 1, 6], [3, 4, 1, 6]
    For index 4 - [2]

So, the answer for the above input is [1, 3, 1, 5, 1]
*/

vector < int > CountSubarrays(const vector < int > &arr)
{
 int n=int(arr.size());
 vector < int > res(n,1),LR(n,-1),RL(n,-1);
 stack < int > s;
 for(int i=0;i<n;i++)
 {
  while(!s.empty() && arr[s.top()]<arr[i]) LR[s.top()]=i,s.pop();
  s.push(i);
 }
 while(!s.empty()) s.pop();
 for(int i=n-1;i>=0;i--)
 {
  while(!s.empty() && arr[s.top()]<arr[i]) RL[s.top()]=i,s.pop();
  s.push(i);
 }
 for(int i=0;i<n;i++)
 {
  if (LR[i]==-1) res[i]+=n-1-i;
  else res[i]+=LR[i]-1-i;
  if (RL[i]==-1) res[i]+=i;
  else res[i]+=i-1-RL[i];
 }
 return res;
}
