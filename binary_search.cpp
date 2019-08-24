int binary_search(const vector < int > &arr, const int &key)
{
 int lo=0,hi=arr.size()-1;
 while(lo<=hi)
 {
  int mid=lo+(hi-lo)/2;
  if (key<arr[mid]) hi=mid-1;
  else if (key>arr[mid]) lo=mid+1;
  else return mid;
 }
 return -1;
}
