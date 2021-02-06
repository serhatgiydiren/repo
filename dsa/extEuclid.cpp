#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// a * x + b * y = gcd(a, b)
// a & b -> coprime
// x = multiplicative modulo inverse of a under modulo b
// y = multiplicative modulo inverse of b under modulo a
pair < ll , pair < ll , ll > > extEuclid(ll a, ll b)
{
// (gcd, (x, y))
pair < ll , pair < ll , ll > > res;

 if (b == 0)
 {
  res.first = a;
  res.second.first = 1;
  res.second.second = 0;
 }
 else
 {
  res = extEuclid(b, a % b);
  long long temp = res.second.first;
  res.second.first = res.second.second;
  res.second.second = temp - (a / b) * res.second.second;
 }

 return res;
}

int main() {
ll a = 165;
ll b = 75;

 // 165 * 1 + 75 * (-2) = 15
 pair < ll , pair < ll , ll > > gcdxy = extEuclid(a, b);
 cout << "gcd = " << gcdxy.first << endl; // 15
 cout << "x = " << gcdxy.second.first << endl; // 1
 cout << "y = " << gcdxy.second.second << endl; // -2

 return 0;
}
