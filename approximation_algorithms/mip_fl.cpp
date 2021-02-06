#include <bits/stdc++.h>

using namespace std;

const double INF = numeric_limits<double>::infinity();

struct Facility
{
 double cost;
 int capacity;
 int available;
 unordered_set < int > customers;
 double x;
 double y;
};

struct Customer
{
 int demand;
 int facility;
 double x;
 double y;
};

int n_facility, n_customer;

vector < Facility > facilities;
vector < Customer > customers;
vector < vector < double > > distance_matrix;
vector < vector < double > > feature;
vector < vector < int > > penalty;

void read_data()
{
 cin >> n_facility >> n_customer;
 customers.resize(n_customer);
 facilities.resize(n_facility);
 for(auto & facility : facilities)
 {
  cin >> facility.cost >> facility.capacity >> facility.x >> facility.y;
  facility.available=facility.capacity;
 }
 for(auto & customer : customers)
 {
  cin >> customer.demand >> customer.x >> customer.y;
  customer.facility=-1;
 }
}

// Initialize distance matrix, distance_matrix[i][j] is the distance between the i-th customer and the j-th facility.
void init_distance_matrix()
{
 distance_matrix.resize(n_customer, vector < double > (n_facility));
 for(int i=0;i<n_customer;i++) for(int j=0;j<n_facility;j++) distance_matrix[i][j]=sqrt(pow(customers[i].x-facilities[j].x,2)+pow(customers[i].y-facilities[j].y,2));
}

// Initialize features, feature[i][j] is the feature for the edge that connects the i-th customer and the j-th facility.
// feature[i][j] equals to the setup cost of the j-th facility, which means it is independent from i.
void init_feature()
{
 feature.resize(n_customer, vector < double > (n_facility));
 for(int i=0;i<n_customer;i++) for(int j=0;j<n_facility;j++) feature[i][j]=facilities[j].cost;
}

// Calculate augmented cost for a certain set of assignment.
double get_augmented_cost(const double &lambda)
{
 double augmented_cost=0.0;
 for(int facility=0;facility<n_facility;facility++)
 {
  for(auto customer : facilities[facility].customers) augmented_cost+=distance_matrix[customer][facility]+lambda*penalty[customer][facility];
  augmented_cost+=!facilities[facility].customers.empty()*facilities[facility].cost;
 }
 return augmented_cost;
}

// Initialize the weight of penalty.
double init_lambda(const double &cost, const double &alpha)
{
 return alpha*cost/n_customer;
}

// Initialize assignment by greedy algorithm.
void init_assignment()
{
 for(int customer=0;customer<int(customers.size());customer++)
 {
  double min_distance=INF;
  int min_facility=-1;
  for(int facility=0;facility<n_facility;facility++)
  {
   if (min_distance>distance_matrix[customer][facility] && customers[customer].demand<=facilities[facility].available)
   {
    min_distance=distance_matrix[customer][facility];
    min_facility=facility;
   }
  }
  facilities[min_facility].customers.insert(customer);
  facilities[min_facility].available-=customers[customer].demand;
  customers[customer].facility=min_facility;
 }
}

// Calculate cost for a certain set of assignment.
double get_cost()
{
 double cost=0.0;
 for(int facility=0;facility<n_facility;facility++)
 {
  for(auto customer : facilities[facility].customers) cost+=distance_matrix[customer][facility];
  cost+=!facilities[facility].customers.empty()*facilities[facility].cost;
 }
 return cost;
}

// Select a customer, move it to a new facility.
// Select the move with the maximum gain in augmented cost.
auto select_customer_to_move(const double &lambda)
{
 double max_augmented_gain=-INF;
 vector < int > max_customer;
 vector < int > max_facility;
 for(int customer=0;customer<n_customer;customer++)
 {
  for(int facility_new=0;facility_new<n_facility;facility_new++)
  {
   int facility_old=customers[customer].facility;
   if (facility_new==facility_old) continue;
   if (facilities[facility_new].available<customers[customer].demand) continue;

   // If there is only one customer in the old facility, then remove this customer will cause the facility to shutdown.
   double augmented_cost_old=distance_matrix[customer][facility_old]+lambda*penalty[customer][facility_old]+(facilities[facility_old].customers.size()==1)*facilities[facility_old].cost;

   // If there is no customer in the new facility, then move this customer to the new facility will cause it to setup.
   double augmented_cost_new=distance_matrix[customer][facility_new]+lambda*penalty[customer][facility_new]+(facilities[facility_new].customers.size()==0)*facilities[facility_new].cost;

   double augmented_gain=augmented_cost_old-augmented_cost_new;

   if (max_augmented_gain<augmented_gain)
   {
    max_augmented_gain=augmented_gain;
    max_customer.clear();
    max_customer.push_back(customer);
    max_facility.clear();
    max_facility.push_back(facility_new);
   }
   else if(max_augmented_gain==augmented_gain)
   {
    max_customer.push_back(customer);
    max_facility.push_back(facility_new);
   }
  }
 }

 if (max_augmented_gain>0.0)
 {
  int index=rand()%max_customer.size();
  int customer_selected=max_customer[index];
  int facility_old=customers[customer_selected].facility;
  int facility_new=max_facility[index];
  return make_tuple(max_augmented_gain, customer_selected, facility_old, facility_new);
 }
 else return make_tuple(0.0, -1, -1, -1);
}

// Penalize features with the maximum utility.
auto add_penalty(double &augmented_cost, const double &lambda)
{
 double max_util=-INF;
 vector < int > max_util_customer;
 for(int customer=0;customer<n_customer;customer++)
 {
  int facility=customers[customer].facility;
  double util=feature[customer][facility]/(1+penalty[customer][facility]);
  if (max_util<util)
  {
   max_util=util;
   max_util_customer.clear();
   max_util_customer.push_back(customer);
  }
  else if (max_util==util) max_util_customer.push_back(customer);
 }

 // Add penalty and update augmented cost.
 for(auto customer : max_util_customer)
 {
  int facility=customers[customer].facility;
  penalty[customer][facility]+=1;
  augmented_cost+=lambda;
 }
}

void save_result(const vector < Customer > &customers, const double &cost)
{
 cout << cost << " " << 0 << endl;
 for(auto & customer : customers) cout << customer.facility << " ";
 cout << endl;
}

void guided_ls()
{
 double alpha=0.05;
 init_distance_matrix();
 init_assignment();
 init_feature();
 double cost=get_cost();
 double lambda=0.0;
 penalty.resize(n_customer, vector < int > (n_facility));
 double augmented_cost=get_augmented_cost(lambda);
 auto best_customers=customers;
 auto best_cost=cost;
 long long step_limit=1e6;
 for(long long step=0;step<step_limit;step++)
 {
  cerr << step + 1 << " " << step_limit << " " << cost << " " << augmented_cost << " " << best_cost << endl;
  auto [augmented_cost_gain_by_customer_move, customer, facility_old, facility_new]=select_customer_to_move(lambda);
  if (customer==-1)
  {
   if (!lambda) lambda=init_lambda(cost, alpha);
   add_penalty(augmented_cost, lambda);
  }
  else
  {
   double cost_old=distance_matrix[customer][facility_old]+(int(facilities[facility_old].customers.size())==1)*facilities[facility_old].cost;
   double cost_new=distance_matrix[customer][facility_new]+(int(facilities[facility_new].customers.size())==0)*facilities[facility_new].cost;
   double cost_gain=cost_old-cost_new;
   double augmented_cost_gain=augmented_cost_gain_by_customer_move;
   cost-=cost_gain;
   augmented_cost-=augmented_cost_gain;
   facilities[facility_old].customers.erase(customer);
   facilities[facility_old].available+=customers[customer].demand;
   facilities[facility_new].customers.insert(customer);
   facilities[facility_new].available-=customers[customer].demand;
   customers[customer].facility=facility_new;
  }
  if (best_cost>cost)
  {
   best_cost=cost;
   best_customers=customers;
  }
 }
 save_result(best_customers, best_cost);
}

void init()
{
 srand(time(NULL));
 cout << fixed << setprecision(6);
 cerr << fixed << setprecision(6);
}

int main()
{
 init();
 read_data();
 guided_ls();
 return EXIT_SUCCESS;
}
