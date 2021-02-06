#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;

const int MDL = 1e9 + 7; // 10^9+7 (prime)

ll modExp(ll a, ll b, ll m = MDL)
{
ll res = 1;

 a %= m;
 // b >>= 1 -> b /= 2
 for ( ; b ; b >>= 1)
 {
  // b & 1 -> b % 2 == 1
  if (b & 1) res = (res * a) % m;
  a = (a * a) % m;
 }
 return res;
}

int main() {
 cout << MDL << endl; // 1000000007
 cout << modExp(8238598, 378907298722) << endl; // 303758382
 cout << modExp(8238598, 378907298722, 1e9 + 3) << endl; // 741807352
 cout << modExp(8238598, 378907298722, 1e9 + 7) << endl; // 303758382

 return 0;
}
