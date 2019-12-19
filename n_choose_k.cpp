#define MDL 1000000007
#define N 100005

vector < long long > dp(N,-1),fact(N,1);

void init()
{
 for(int i=2;i<N;i++) fact[i]=(fact[i-1]*i)%MDL;
}

long long powmod(long long a, long long b)
{
 long long res=1;
 a%=MDL;
 for(;b;b>>=1)
 {
  if (b&1) res=res*a%MDL;
  a=a*a%MDL;
 }
 return res;
}

long long modinv(long long a)
{
 return powmod(a, MDL-2);
}

long long nCk(long long n, long long k)
{
 long long numerator=1,denominator=1;
 for(int i=0;i<k;i++) numerator=(numerator*(n-i))%MDL;
 for(int i=1;i<=k;i++) denominator=(denominator*i)%MDL;
 return (numerator*modinv(denominator))%MDL;
}

long long nCk2(int n, int k)
{
 return(((fact[n]*modinv(fact[k]))%MDL)*modinv(fact[n-k]))%MDL;
}
