/*
Given a list of N triangles with integer side lengths, determine how many different triangles there are. Two triangles are considered to be the same if they can both be placed on the plane such that their vertices occupy exactly the same three points.
Signature
int countDistinctTriangles(int[][] triangles)
int countDistinctTriangles(Triangle[] triangles)
Input
In some languages triangles is an Nx3 array where triangles[i] is a length-3 array that contains the side lengths of the ith triangle. In other languages, triangles is a list of structs/objects that each represent a single triangle with side lengths a, b, and c.
It's guaranteed that all triplets of side lengths represent real triangles.
All side lengths are in the range [1, 1,000,000,000]
1 <= N <= 1,000,000
Output
Return the number of distinct triangles in the list.
Example 1
triangles = [[2, 2, 3], [3, 2, 2], [2, 5, 6]]
output = 2
The first two triangles are the same, so there are only 2 distinct triangles.
Example 2
triangles = [[8, 4, 6], [100, 101, 102], [84, 93, 173]]
output = 3
All of these triangles are distinct.
Example 3
triangles = [[5, 8, 9], [5, 9, 8], [9, 5, 8], [9, 8, 5], [8, 9, 5], [8, 5, 9]]
output = 1
All of these triangles are the same.
*/

struct sides
{
 long long a;
 long long b;
 long long c;
};

bool operator<(const sides &s1, const sides &s2)
{
 return (s1.a<s2.a || (s1.a==s2.a && (s1.b<s2.b || (s1.b==s2.b && s1.c<s2.c))));
}

void ut(sides &s)
{
  if (s.a>s.b) swap(s.a,s.b);
  if (s.a>s.c) swap(s.a,s.c);
  if (s.b>s.c) swap(s.b,s.c);
}

int countDistinctTriangles(vector < sides > &arr)
{
 set < sides > s;
 for(sides e:arr)
 {
   ut(e);
   s.insert(e);
 }
 return int(s.size());
}
