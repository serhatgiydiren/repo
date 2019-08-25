template < typename T >
void print_containter(T c)
{
 for(auto it=c.begin();it!=c.end();it++) cout << *it << " ";
 cout << endl;
}

void set_samples()
{
 const string str="SEARCHEXAMPLE";

 set < char > s;
 for(unsigned i=0;i<str.size();i++) s.insert(str[i]);
 print_containter(s); // A C E H L M P R S X 
 cout << s.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (s.find('E')!=s.end()) << endl; // 1
 cout << s.erase('E') << endl; // 1 (the number of elements erased)
 cout << (s.find('E')!=s.end()) << endl; // 0
 print_containter(s); // A C H L M P R S X 

 unordered_set < char > us;
 for(unsigned i=0;i<str.size();i++) us.insert(str[i]);
 print_containter(us); // M X C H S P E L A R 
 cout << us.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (us.find('E')!=us.end()) << endl; // 1
 cout << us.erase('E') << endl; // 1 (the number of elements erased)
 cout << (us.find('E')!=us.end()) << endl; // 0
 print_containter(us); // M X C H S P L A R 

 multiset < char > ms;
 for(unsigned i=0;i<str.size();i++) ms.insert(str[i]);
 print_containter(ms); // A A C E E E H L M P R S X 
 cout << ms.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (ms.find('E')!=ms.end()) << endl; // 1
 cout << ms.erase('E') << endl; // 1 (the number of elements erased)
 cout << (ms.find('E')!=ms.end()) << endl; // 0
 print_containter(ms); // A A C H L M P R S X 

 unordered_multiset < char > ums;
 for(unsigned i=0;i<str.size();i++) ums.insert(str[i]);
 print_containter(ums); // L P R E E E S H C A A X M 
 cout << ums.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (ums.find('E')!=ums.end()) << endl; // 1
 cout << ums.erase('E') << endl; // 1 (the number of elements erased)
 cout << (ums.find('E')!=ums.end()) << endl; // 0
 print_containter(ums); // L P R S H C A A X M 
}
