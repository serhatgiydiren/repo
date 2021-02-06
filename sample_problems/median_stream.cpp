/*
You're given a list of n integers arr[0..(n-1)]. You must compute a list output[0..(n-1)] such that, for each index i (between 0 and n-1, inclusive), output[i] is equal to the median of the elements arr[0..i] (rounded down to the nearest integer).
The median of a list of integers is defined as follows. If the integers were to be sorted, then:

    If there are an odd number of integers, then the median is equal to the middle integer in the sorted order.
    Otherwise, if there are an even number of integers, then the median is equal to the average of the two middle-most integers in the sorted order.

Signature
int[] findMedian(int[] arr)
Input
n is in the range [1, 1,000,000].
Each value arr[i] is in the range [1, 1,000,000].
Output
Return a list of n integers output[0..(n-1)], as described above.
Example 1
n = 4
arr = [5, 15, 1, 3]
output = [5, 10, 5, 4]
The median of [5] is 5, the median of [5, 15] is (5 + 15) / 2 = 10, the median of [5, 15, 1] is 5, and the median of [5, 10, 1, 3] is (3 + 5) / 2 = 4.
Example 2
n = 2
arr = [1, 2]
output = [1, 1]
The median of [1] is 1, the median of [1, 2] is (1 + 2) / 2 = 1.5 (which should be rounded down to 1).
*/

vector < int > findMedian(const vector < int > &arr)
{
 int n=int(arr.size()),a,b;
 vector < int > res(n);
 priority_queue < int , vector < int > , less < int > > p_desc;
 priority_queue < int , vector < int > , greater < int > > p_asc;

 for(int i=0;i<n;i++)
 {
  if (i%2) p_asc.push(arr[i]);
  else p_desc.push(arr[i]);
  if (i && (a=p_asc.top())<(b=p_desc.top()))
  {
   p_asc.pop();
   p_desc.pop();
   p_asc.push(b);
   p_desc.push(a);
  }
  if (i%2) res[i]=(p_asc.top()+p_desc.top())>>1;
  else res[i]=p_desc.top();
 }
 return res;
}
