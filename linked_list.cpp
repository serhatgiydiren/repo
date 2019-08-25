class node
{
public:
int data;
node* next;

node(const int &val)
{
 data=val;
 next=NULL;
}

node(const int &val, node *_next)
{
 data=val;
 next=_next;
}
};

class linked_list
{
node* first;

public: 
linked_list()
{
 first=NULL;
}

node* head()
{
 return first;
}

void insert(const int &val)
{
 node *temp=new node(val);
 if (first==NULL) first=temp;
 else
 {
  node *runner=first;
  while(runner->next) runner=runner->next;
  runner->next=temp;
 }
}

void make_unique_1()
{
 set < int > items;
 node *temp=first,*prev=NULL;
 while(temp)
 {
  if (items.find(temp->data)==items.end()) items.insert(temp->data);
  else
  {
   prev->next=temp->next;
   temp=prev;
  }
  prev=temp;
  temp=temp->next;
 }
}

void make_unique_2()
{
 node *main_runner=first,*sub_runner;
 while(main_runner)
 {
  sub_runner=main_runner;
  while(sub_runner->next)
  {
   if (main_runner->data==sub_runner->next->data) sub_runner->next=sub_runner->next->next;
   else sub_runner=sub_runner->next;
  }
  main_runner=main_runner->next;
 }
}

void print()
{
 cout << "Head -> ";
 node *runner=first;
 while(runner)
 {
  cout << runner->data << " -> ";
  runner=runner->next;
 }
 cout << endl;
}
};

void linked_list_samples()
{
 vector < int > elements={4,3,8,1,4,9,2,8,6,5,7,4,4,1,8};

 linked_list ll1;
 for(unsigned i=0;i<elements.size();i++) ll1.insert(elements[i]);
 ll1.print(); // Head -> 4 -> 3 -> 8 -> 1 -> 4 -> 9 -> 2 -> 8 -> 6 -> 5 -> 7 -> 4 -> 4 -> 1 -> 8 -> 
 ll1.make_unique_1();
 ll1.print(); // Head -> 4 -> 3 -> 8 -> 1 -> 9 -> 2 -> 6 -> 5 -> 7 -> 

 linked_list ll2;
 for(unsigned i=0;i<elements.size();i++) ll2.insert(elements[i]);
 ll2.print(); // Head -> 4 -> 3 -> 8 -> 1 -> 4 -> 9 -> 2 -> 8 -> 6 -> 5 -> 7 -> 4 -> 4 -> 1 -> 8 -> 
 ll2.make_unique_2();
 ll2.print(); // Head -> 4 -> 3 -> 8 -> 1 -> 9 -> 2 -> 6 -> 5 -> 7 -> 
}
