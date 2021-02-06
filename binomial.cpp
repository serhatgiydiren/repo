 vector < vll > x(MAXN,vll(MAXN,0));
 FOR(i,0,MAXN)
 {
  x[i][0]=x[i][i]=1;
  FOR(j,1,i) x[i][j]=(x[i-1][j-1]+x[i-1][j])%MDL;
 }
