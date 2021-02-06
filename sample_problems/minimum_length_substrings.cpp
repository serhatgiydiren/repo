/*
You are given two strings s and t. You can select any substring of string s and rearrange the characters of the selected substring. Determine the minimum length of the substring of s such that string t is a substring of the selected substring.
Signature
int minLengthSubstring(String s, String t)
Input
s and t are non-empty strings that contain less than 1,000,000 characters each
Output
Return the minimum length of the substring of s. If it is not possible, return -1
Example
s = "dcbefebce"
t = "fd"'
output = 5
Explanation:
Substring "dcbef" can be rearranged to "cfdeb", "cefdb", and so on. String t is a substring of "cfdeb". Thus, the minimum length required is 5.
*/

map < char , int > hash_string(const string &s)
{
 map < char , int > res;
 for(auto e:s) res[e]++;
 return res;
}

bool check(const map < char , int > &m1, const map < char , int > &m2)
{
 for(auto e:m1)
 {
  auto it=m2.find(e.first);
  if (it==m2.end()) return false;
  if (it->second<e.second) return false;
 }
 return true;
}

int minLengthSubstring_optimal(const string &s, const string &t)
{
 int res=INT_MAX;
 if (s.size()>=t.size())
 {
  auto hash_t=hash_string(t);
  int left=0;
  map < char , int > hash_s;
  for(int i=0;i<int(s.size());i++)
  {
   hash_s[s[i]]++;
   while(check(hash_t,hash_s))
   {
    res=min(res,i-left+1);
    hash_s[s[left++]]--;
   }
  }
 }
 if (res==INT_MAX) return -1;
 return res;
}

int minLengthSubstring_brute_force(const string &s, const string &t)
{
 int n=int(s.size());
 auto hash_t=hash_string(t);
 for(int i=int(t.size());i<=n;i++) for(int j=0;j<n+1-i;j++) if (check(hash_t,hash_string(s.substr(j,i)))) return i;
 return -1;
}
