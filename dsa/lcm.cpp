#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
 return (b == 0) ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
 return a * (b / gcd(a, b));
}

int main() {
 cout << lcm(2, 3) << endl; // 6
 cout << lcm(300, 500) << endl; // 1500

 return 0;
}
