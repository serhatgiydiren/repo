#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;

#define MAXN 10000005

vb prime(MAXN,true);

bool isPrime(ll n)
{
//sieve() must be called before any use
 if (n<MAXN) return prime[n];
 if (n<2) return false;
 if (n>2 && n%2==0) return false;
 for (ll i=3;i*i<=n;i+=2) if (n%i==0) return false;
 return true;
}

void sieve()
{
 for (int p=2;p*p<MAXN;p++) if (prime[p]) for (int i=p*2;i<MAXN;i+=p) prime[i]=false;
}

vector < ll > divisors(ll n)
{
vector < ll > res;

 for (ll i = 1 ; i * i <= n ; i++)
 {
  if (n % i == 0)
  {
   res.push_back(i);
   ll j = n / i;
   if (i != j) res.push_back(j);
  }
 }
 return res;
}

// USE FOR BIG NUMBERS , complexity = O(sqrt(n))
// returns factor list
vector < ll > factorize(ll n)
{
vector < ll > res;

 for (ll i = 2 ; i * i <= n ; i++)
 {
  while (n % i == 0)
  {
   res.push_back(i);
   n /= i;
  }
 }
 
 if (n != 1) res.push_back(n);

 return res;
}

// USE FOR SMALL NUMBERS , complexity = O(log(n))
// returns factor list
vector < int > factorize2(int n)
{
vector < int > res, minPrime(n + 1);

 for (int i = 2 ; i * i <= n ; i++) if (minPrime[i] == 0) for (int j = i * i ; j <= n ; j += i) if (minPrime[j] == 0) minPrime[j] = i;
 for (int i = 2 ; i <= n ; i++) if (minPrime[i] == 0) minPrime[i] = i;

 while (n != 1)
 {
  res.push_back(minPrime[n]);
  n /= minPrime[n];
 }

 return res;
}

// USE FOR BIG NUMBERS , complexity = O(sqrt(n))
// returns ( factor , exponentiation ) list
vector < pair < ll , int > > factorize3(ll n)
{
vector < pair < ll , int > > res;

 for (ll i = 2 ; i * i <= n ; i++)
 {
  int count = 0;
  while (n % i == 0)
  {
   count++;
   if (count == 1) res.push_back(make_pair(i, 1));
   else res[res.size()-1].second++;
   n /= i;
  }
 }
 
 if (n != 1) res.push_back(make_pair(n, 1));

 return res;
}

// slow divCount
ll divCount(ll n)
{
ll res = 0;

 for (ll i = 1 ; i * i <= n; i++)
 {
  if (n % i == 0)
  {
   if (i * i == n) res++;
   else res += 2;
  }
 }
 return res;
}

// fast divCount
ll divCount2(ll n)
{
ll res = 1;

 vector < pair < ll , int > > factList3 = factorize3(n);
 for (unsigned i = 0 ; i < factList3.size(); i++) res *= (factList3[i].second + 1);
 return res;
}

void processNum(ll num)
{
vector < ll > divList, factList;
vector < int > factList2;
vector < pair < ll , int > > factList3;

 if (num > INT_MAX) cout << "divCount skipped..." << endl;
 else cout << "Divisor (slow) count = " << divCount(num) << endl;

 cout << "Divisor (fast) count = " << divCount2(num) << endl;

 if (num > INT_MAX) cout << "divisors skipped..." << endl;
 else
 {
  divList = divisors(num);
  cout << "Divisors : ";
  for (unsigned i = 0 ; i < divList.size(); i++) cout << divList[i] << " ";
  cout << endl;
 }

 factList = factorize(num);
 cout << "Factors : ";
 for (unsigned i = 0 ; i < factList.size(); i++) cout << factList[i] << " ";
 cout << endl;

 if (num < 1e7)
 {
  factList2 = factorize2(num);
  cout << "Factors : ";
  for (unsigned i = 0 ; i < factList2.size(); i++) cout << factList2[i] << " ";
  cout << endl;
 }
 else cout << "factorize2 skipped..." << endl;

 factList3 = factorize3(num);
 cout << "Factors & Exponentiations : ";
 for (unsigned i = 0 ; i < factList3.size(); i++) cout << factList3[i].first << "^" << factList3[i].second << " ";
 cout << endl;
}

vector < bool > sieve(ll n)
{
vector < bool > res(n + 1, true);

 res[0] = res[1] = false;
 for (ll i = 2 ; i * i <= n ; i++) if (res[i]) for (ll j = i * i ; j <= n ; j += i) res[j] = false;
 return res;
}

// count of all numbers N where gcd(num, N) = 1 and 1 <= N <= num
ll eulerTotient(ll num)
{
ll res = num;

 vector < pair < ll , int > > factList3 = factorize3(num);
 for (unsigned i = 0 ; i < factList3.size(); i++) res = (res / factList3[i].first) * (factList3[i].first - 1);
 return res;
}

int main() {
 cout << isPrime(2) << endl; // 1
 cout << isPrime(3) << endl; // 1
 cout << isPrime(4) << endl; // 0
 cout << isPrime(5) << endl; // 1
 cout << isPrime(1e9+3) << endl; // 0 -> 1e9+3 = 1000000003 = 23 * 307 * 141623
 cout << isPrime(1e9+7) << endl; // 1 -> 1e9+7 = 1000000007 = 1 * 1000000007
 cout << isPrime(INT_MAX) << endl; // 1 -> INT_MAX = 2147483647 = 1 * 2147483647 
 cout << isPrime(LLONG_MAX) << endl; // 0 -> LLONG_MAX = 9223372036854775807 = 7 * 7 * 73 * 127 * 337 * 92737 * 649657 

 vector < bool > isPrimeList = sieve(INT_MAX); // generally 1e7 is enough
 cout << isPrimeList[2] << endl; // 1
 cout << isPrimeList[3] << endl; // 1
 cout << isPrimeList[4] << endl; // 0
 cout << isPrimeList[5] << endl; // 1
 cout << isPrimeList[1e9+3] << endl; // 0 -> 1e9+3 = 1000000003 = 23 * 307 * 141623
 cout << isPrimeList[1e9+7] << endl; // 1 -> 1e9+7 = 1000000007 = 1 * 1000000007
 cout << isPrimeList[INT_MAX] << endl; // 1 -> INT_MAX = 2147483647 = 1 * 2147483647 
 //cout << isPrimeList[LLONG_MAX] << endl; // ERROR -> not possible to calculate via sieve

 cout << eulerTotient(20) << endl; // 8
 cout << eulerTotient(49) << endl; // 42
 cout << eulerTotient(90) << endl; // 24
 cout << eulerTotient(2147483646) << endl; // 534600000

 processNum(200);
 // Divisor (slow) count = 12
 // Divisor (fast) count = 12
 // Divisors : 1 200 2 100 4 50 5 40 8 25 10 20 
 // Factors : 2 2 2 5 5 
 // Factors : 2 2 2 5 5 
 // Factors & Exponentiations : 2^3 5^2 

 processNum(289);
 // Divisor (slow) count = 3
 // Divisor (fast) count = 3
 // Divisors : 1 289 17 
 // Factors : 17 17 
 // Factors : 17 17 
 // Factors & Exponentiations : 17^2 

 processNum(8181);
 // Divisor (slow) count = 10
 // Divisor (fast) count = 10
 // Divisors : 1 8181 3 2727 9 909 27 303 81 101 
 // Factors : 3 3 3 3 101 
 // Factors : 3 3 3 3 101 
 // Factors & Exponentiations : 3^4 101^1 

 processNum(1e7-1);
 // Divisor (slow) count = 12
 // Divisor (fast) count = 12
 // Divisors : 1 9999999 3 3333333 9 1111111 239 41841 717 13947 2151 4649 
 // Factors : 3 3 239 4649 
 // Factors : 3 3 239 4649 
 // Factors & Exponentiations : 3^2 239^1 4649^1 

 processNum(1e9+3);
 // Divisor (slow) count = 8
 // Divisor (fast) count = 8
 // Divisors : 1 1000000003 23 43478261 307 3257329 7061 141623 
 // Factors : 23 307 141623 
 // factorize2 skipped...
 // Factors & Exponentiations : 23^1 307^1 141623^1 

 processNum(INT_MAX);
 // Divisor (slow) count = 2
 // Divisor (fast) count = 2
 // Divisors : 1 2147483647 
 // Factors : 2147483647 
 // factorize2 skipped...
 // Factors & Exponentiations : 2147483647^1 

 processNum(LLONG_MAX);
 // divCount skipped...
 // Divisor (fast) count = 96
 // divisors skipped...
 // Factors : 7 7 73 127 337 92737 649657 
 // factorize2 skipped...
 // Factors & Exponentiations : 7^2 73^1 127^1 337^1 92737^1 649657^1 

 processNum(1ll*2*3*5*7*11*13*17*19*23*29*31*37);
 // divCount skipped...
 // Divisor (fast) count = 4096
 // divisors skipped...
 // Factors : 2 3 5 7 11 13 17 19 23 29 31 37 
 // factorize2 skipped...
 // Factors & Exponentiations : 2^1 3^1 5^1 7^1 11^1 13^1 17^1 19^1 23^1 29^1 31^1 37^1 

 return 0;
}
