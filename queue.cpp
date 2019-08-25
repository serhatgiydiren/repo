void queue_samples()
{
 vector < int > elements={8,3,9,1,7};

 queue < int > q;
 for(unsigned i=0;i<elements.size();i++) q.push(elements[i]);
 // 8
 cout << q.front() << endl;
 // 8
 cout << q.back() << endl;
 // 8 3 9 1 7
 while(!q.empty())
 {
  cout << q.front() << " ";
  q.pop();
 }
 cout << endl;
}
