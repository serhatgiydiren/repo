void stack_samples()
{
 vector < int > elements={8,3,9,1,7};

 stack < int > s;
 for(unsigned i=0;i<elements.size();i++) s.push(elements[i]);
 // 7 1 9 3 8
 while(!s.empty())
 {
  cout << s.top() << " ";
  s.pop();
 }
 cout << endl;
}
