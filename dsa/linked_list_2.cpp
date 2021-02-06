#define __USE_MINGW_ANSI_STDIO 0

#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
int data;
Node* next;

Node(const int &val)
{
 data=val;
 next=NULL;
}
};

class LinkedList
{
Node* first;

public: 
LinkedList()
{
 first=NULL;
}

Node* head()
{
 return first;
}

void insert(const int &val)
{
 Node* temp=new Node(val);
 if (first==NULL) first=temp;
 else
 {
  Node *runner=first;
  while(runner->next) runner=runner->next;
  runner->next=temp;
 }
}

void make_unique_1()
{
 set < int > items;
 Node *temp=first,*prev=NULL;
 while(temp)
 {
  if (items.find(temp->data)==items.end())
  {
   items.insert(temp->data);
  }
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
 set < int > items;
 Node *temp=first,*runner;
 while(temp)
 {
  runner=temp;
  while(runner->next)
  {
   if (runner->next->data==temp->data) runner->next=runner->next->next;
   else runner=runner->next;
  }
  temp=temp->next;
 }
}

void kToTheLast(int k)
{
 int c=0;
 Node *temp=first;            
 while(temp)
 {
  c++;
  temp=temp->next;
 }
 cerr << c << " elements..." << endl;
 temp=first;
 while(c>k)
 {
  c--;
  temp=temp->next;
 }
 if (c==k) cerr << k << " to the last:" << temp->data << endl;
 else cerr << k << " to the last:" << " NOT EXISTS" << endl;
}

void deleteMiddleNode()
{
 int c=0;
 Node *temp=first;
 while(temp)
 {
  c++;
  temp=temp->next;
 }
 cerr << c << " elements..." << endl;
 int n=(c+1)/2;
 temp=first;
 c=0;
 while(temp)
 {
  if (++c>=n-1) { temp->next=temp->next->next; break; }
  temp=temp->next;
 }
}

void make_partition(const int &val)
{
 Node *temp=first,*prev=NULL,*lt_left=NULL,*lt_right=NULL,*gt_left=NULL,*gt_right=NULL;
 while(temp)
 {
  if (temp->data<val)
  {
   if (lt_left==NULL) lt_left=lt_right=temp;
   else
   {
    lt_right->next=temp;
    lt_right=lt_right->next;
   }
  }
  else
  {
   if (gt_left==NULL) gt_left=gt_right=temp;
   else
   {
    gt_right->next=temp;
    gt_right=gt_right->next;
   }
  }
  prev=temp;
  temp=temp->next;
  prev->next=NULL;
 }
 temp=lt_left;
 cerr << "lt : ";
 while(temp)
 {
  cerr << temp->data << "->";
  temp=temp->next;
 }
 cerr << endl;
 temp=gt_left;
 cerr << "gt : ";
 while(temp)
 {
  cerr << temp->data << "->";
  temp=temp->next;
 }
 cerr << endl;
 if (lt_left==NULL) first=gt_left;
 else
 {
  first=lt_left;
  lt_right->next=gt_left;
 }
}

void reverse_LL()
{
Node *res=NULL,*runner=first,*temp;

 while(runner)
 {
  temp=runner;
  runner=runner->next;
  temp->next=res;
  res=temp;  
 }
 first=res;
}

bool is_palindrome()
{
 int c=0;
 Node *temp=first;
 while(temp)
 {
  c++;
  temp=temp->next;
 }
 cerr << c << " elements..." << endl;
 stack < int > checker;
 int n=c/2;
 temp=first;
 int d=0;
 while(temp)
 {
  d++;
  if (d<=n) checker.push(temp->data);
  else if (d+n>c)
  {
   int top_element=checker.top();
   checker.pop();
   if (top_element!=temp->data) return false;
  }
  temp=temp->next;
 }
 return true;
}

void print()
{
 Node* temp=first;
 cerr << "Head->";
 while(temp)
 {
  cerr << temp->data << "->";
  temp=temp->next;
 }
 cerr << endl;
}
};  

LinkedList add_LL(LinkedList L1, LinkedList L2)
{
LinkedList sum;
int carry=0,c;

 Node *t1=L1.head();
 Node *t2=L2.head();
 
 while(t1 || t2)
 {
  c=carry;
  if (t1) c+=t1->data;
  if (t2) c+=t2->data;
  cerr << c << endl;
  sum.insert(c%10);
  carry=c/10;
  if (t1) t1=t1->next;
  if (t2) t2=t2->next;
 }
 if (carry) sum.insert(carry);
 return sum; 
}

void solve()
{
int n,q;

 cin >> n;
 cerr << n << endl;
 LinkedList LL1,LL2,LL3;
 for(int i=0;i<n;i++)
 {
  cin >> q;
  cerr << q << " ";
  LL1.insert(q);
  LL2.insert(q);
  LL3.insert(q);
 }
 cerr << endl;

 LL1.print();
 LL1.make_unique_1();
 LL1.print();
 LL1.insert(999);
 LL1.print();
 LL1.insert(999);
 LL1.print();
 LL1.make_unique_1();
 LL1.print();

 LL2.print();
 LL2.make_unique_2();
 LL2.print();
 LL2.insert(999);
 LL2.print();
 for(int i=1;i<=12;i++) LL2.kToTheLast(i);
 LL2.print();
 for(int i=1;i<=10;i++)
 {
  LL2.deleteMiddleNode();
  LL2.print();
 }

 LL3.print();
 LL3.make_partition(5);
 LL3.print();
 LL3.make_partition(5000);
 LL3.print();
 LL3.make_partition(0);
 LL3.print();

 LinkedList LL7,LL8;
 LL7.insert(1); 
 LL7.insert(1); 
 LL7.insert(1); 
 LL7.insert(1); 
 LL7.insert(1); 
 LL7.insert(1); 
 LL7.insert(1); 
 LL8.insert(9); 
 LL8.insert(8); 
 LL8.insert(8); 
 LL8.insert(8); 
 LL8.insert(8); 
 LL8.insert(8); 
 LL8.insert(8); 
 LinkedList LL9=add_LL(LL7,LL8);
 LL9.print();

 LinkedList LL4,LL5;
 LL4.insert(8); 
 LL4.insert(6); 
 LL4.insert(3); 
 LL5.insert(1); 
 LL5.insert(2); 
 LL5.insert(3); 
 LL5.insert(4);
 /* 368 + 4321 = 4689 */
 LinkedList LL6=add_LL(LL4,LL5);
 LL6.print();
 LL6.reverse_LL();
 LL6.print();

 LinkedList LL10;
 LL10.insert(3);
 LL10.insert(2);
 LL10.insert(2);
 LL10.insert(3);
 LL10.print();
 cerr << LL10.is_palindrome() << endl;

 LinkedList LL11;
 LL11.insert(3);
 LL11.print();
 cerr << LL11.is_palindrome() << endl;

 LinkedList LL12;
 LL12.insert(1);
 LL12.insert(1);
 LL12.print();
 cerr << LL12.is_palindrome() << endl;

 LinkedList LL13;
 LL13.insert(1);
 LL13.insert(2);
 LL13.print();
 cerr << LL13.is_palindrome() << endl;
}

void solve_test_cases()
{
int test_cases=1;

 cin >> test_cases;
 while(test_cases--) solve();
}

void fast_io()
{
 ios::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cout << fixed << setprecision(15);
}

int main()
{
 fast_io();
 solve_test_cases();
 return EXIT_SUCCESS;
}
