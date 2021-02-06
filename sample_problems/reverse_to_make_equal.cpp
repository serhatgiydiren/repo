/*
Given two arrays A and B of length N, determine if there is a way to make A equal to B by reversing any subarrays from array B any number of times.
Signature
bool areTheyEqual(int[] arr_a, int[] arr_b)
Input
All integers in array are in the range [0, 1,000,000,000].
Output
Return true if B can be made equal to A, return false otherwise.
Example
A = [1, 2, 3, 4]
B = [1, 4, 3, 2]
output = true
After reversing the subarray of B from indices 1 to 3, array B will equal array A.
*/

bool areTheyEqual(const vector < int > &array_a, const vector < int > &array_b)
{
 unordered_map < int , int > m;
 for(int e:array_a) m[e]++;
 for(int e:array_b) m[e]--;
 for(auto e:m) if (e.second!=0) return false;
 return true;
}
