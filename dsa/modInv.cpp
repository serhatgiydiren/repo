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

// (a * b) % m = 1
// b = modular multiplicative inverse of a under modulo m
// a and m are coprime i.e. gcd(a, m) = 1
// m MUST BE prime
ll modInv(ll a, ll m = MDL)
{
 return modExp(a, m - 2, m);
}

// (a * b) % m = 1
// b = modular multiplicative inverse of a under modulo m
// a and m are coprime i.e. gcd(a, m) = 1
// m MUST NOT BE prime
ll modInv2(ll a, ll m = MDL)
{
 pair < ll , pair < ll , ll > > temp = extEuclid(a, m);
 return (temp.second.first % m + m) % m; // temp.second.first (x) may be negative
}

int main() {
 cout << modInv(8238598) << endl; // 871091301
 cout << modInv2(8238598) << endl; // 871091301
 cout << modInv(8238598, 1e9 + 3) << endl; // 130737082 -> WRONG because 1e9+3 (1000000003) is not prime, divisible by 23
 cout << modInv2(8238598, 1e9 + 3) << endl; // 553627330
 cout << modInv(8238598, 1e9 + 7) << endl; // 871091301
 cout << modInv2(8238598, 1e9 + 7) << endl; // 871091301
 cout << modInv(8,6) << endl; // 4 -> WRONG because 6 is not prime
 cout << modInv2(8,6) << endl; // 1

 return 0;
}
