const int MDL=1e9+7;

long long mod_exp(long long a, long long b, const long long &m=MDL)
{
 long long res=1;
 a%=m;
 for(;b;b>>=1)
 {
  if (b&1) res=(res*a)%m;
  a=(a*a)%m;
 }
 return res;
}

long long mod_inv(const long long &a, const long long &m=MDL)
{
 return mod_exp(a,m-2,m);
}
