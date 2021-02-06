/*
We have N different apps with different user growth rates. At a given time t, measured in days, the number of users using an app is g^t (for simplicity we'll allow fractional users), where g is the growth rate for that app. These apps will all be launched at the same time and no user ever uses more than one of the apps.
After how many full days will we have 1 billion total users across the N apps?
Signature
int getBillionUsersDay(float[] growthRates)
Input
1.0 < growthRate < 2.0 for all growth rates
1 <= N <= 1,000
Output
Return the number of full days it will take before we have a total of 1 billion users across all N apps.
Example 1
growthRates = [1.5]
output = 52
Example 2
growthRates = [1.1, 1.2, 1.3]
output = 79
Example 3
growthRates = [1.01, 1.02]
output = 1047
*/

const double EPS=1e-9;
const double one_billion=1e9;

bool check(const int &p, const vector < float > &growthRates)
{
 double c=0;
 for(auto e:growthRates) c+=pow(e,p);
 return(c-one_billion>EPS);
}

int getBillionUsersDay(const vector < float > &growthRates)
{
 int lo=1,hi=int(1e9);
 while(lo<hi)
 {
  int mid=(lo+hi)>>1;
  if (check(mid,growthRates)) hi=mid;
  else lo=mid+1;
 }
 return lo;
}
