template < typename T >
void print_containter(T c)
{
 for(auto it=c.begin();it!=c.end();it++) cout << it->first << " " << it->second << " - ";
 cout << endl;
}

void map_samples()
{
 const string s="SEARCHEXAMPLE";

 map < char , int > m;
 for(unsigned i=0;i<s.size();i++) m[s[i]]=i;
 print_containter(m); // A 8 - C 4 - E 12 - H 5 - L 11 - M 9 - P 10 - R 3 - S 0 - X 7 - 
 cout << m.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (m.find('E')!=m.end()) << endl; // 1
 cout << m.erase('E') << endl; // 1 (the number of elements erased)
 cout << (m.find('E')!=m.end()) << endl; // 0
 print_containter(m); // A 8 - C 4 - E 12 - H 5 - L 11 - M 9 - P 10 - R 3 - X 7 - 

 unordered_map < char , int > um;
 for(unsigned i=0;i<s.size();i++) um[s[i]]=i;
 print_containter(um); // M 9 - X 7 - C 4 - H 5 - S 0 - P 10 - E 12 - L 11 - A 8 - R 3 - 
 cout << um.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (um.find('E')!=um.end()) << endl; // 1
 cout << um.erase('E') << endl; // 1 (the number of elements erased)
 cout << (um.find('E')!=um.end()) << endl; // 0
 print_containter(um); // M 9 - X 7 - C 4 - H 5 - P 10 - E 12 - L 11 - A 8 - R 3 - 

 multimap < char , int > mm;
 for(unsigned i=0;i<s.size();i++) mm.insert(make_pair(s[i],i));
 print_containter(mm); // A 2 - A 8 - C 4 - E 1 - E 6 - E 12 - H 5 - L 11 - M 9 - P 10 - R 3 - S 0 - X 7 - 
 cout << mm.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (mm.find('E')!=mm.end()) << endl; // 1
 cout << mm.erase('E') << endl; // 3 (the number of elements erased)
 cout << (mm.find('E')!=mm.end()) << endl; // 0
 print_containter(mm); // A 2 - A 8 - C 4 - H 5 - L 11 - M 9 - P 10 - R 3 - S 0 - X 7 - 

 unordered_multimap < char , int > umm;
 for(unsigned i=0;i<s.size();i++) umm.insert(make_pair(s[i],i));
 print_containter(umm); // L 11 - P 10 - R 3 - E 12 - E 6 - E 1 - S 0 - H 5 - C 4 - A 8 - A 2 - X 7 - M 9 - 
 cout << umm.erase('Q') << endl; // 0 (the number of elements erased)
 cout << (umm.find('E')!=umm.end()) << endl; // 1
 cout << umm.erase('E') << endl; // 3 (the number of elements erased)
 cout << (umm.find('E')!=umm.end()) << endl; // 0
 print_containter(umm); // L 11 - P 10 - R 3 - S 0 - H 5 - C 4 - A 8 - A 2 - X 7 - M 9 - 
}
