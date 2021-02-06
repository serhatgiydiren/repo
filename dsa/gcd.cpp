#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
 return (b == 0) ? a : gcd(b, a%b);
}

int main() {
 cout << gcd(39, 6) << endl; // 3
 cout << gcd(378907298722, 8238598) << endl; // 2

 return 0;
}
