template < typename T >
void print_heap(T pq)
{
 while(!pq.empty())
 {
  cout << pq.top() << " ";
  pq.pop();
 }
 cout << endl;
}

template < typename T >
void fill_heap(T &pq, const vector < int > &elements)
{
 for(unsigned i=0;i<elements.size();i++) pq.push(elements[i]);
}

void priority_queue_samples()
{
 vector < int > elements={8,3,9,1,7};

 priority_queue < int > max_heap_1;
 fill_heap(max_heap_1, elements);
 print_heap(max_heap_1); // 9 8 7 3 1

 priority_queue < int , vector < int > , less < int > > max_heap_2;
 fill_heap(max_heap_2, elements);
 print_heap(max_heap_2); // 9 8 7 3 1

 priority_queue < int , vector < int > , greater < int > > min_heap_1;
 fill_heap(min_heap_1, elements);
 print_heap(min_heap_1); // 1 3 7 8 9
}
