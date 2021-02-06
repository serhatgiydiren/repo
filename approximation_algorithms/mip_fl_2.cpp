#include <bits/stdc++.h>

using namespace std;

using DistanceMatrix = vector<vector<double>>;
using Feature = vector<vector<double>>;
using Penalty = vector<vector<int>>;

struct Facility
{
    double cost;
    int capacity;
    int available;                  // Available capacity. If capacity is 100, and 37 is occupied, then available is 100 - 37 = 63.
    unordered_set<int> customers;   // Customers that are served by this facility.
    double x;
    double y;

};

struct Customer
{
    int demand;
    int facility;                   // The assigned facility.
    double x;
    double y;
};


// Read input data.
auto read_data()
{
 int n_facility;
 int n_customer;   
 cin >> n_facility >> n_customer;
 auto facilities = vector<Facility>(n_facility);
 auto customers = vector<Customer>(n_customer);
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
 return make_tuple(facilities, customers);
}

// Initialize distance matrix, distance_matrix[i][j] is the distance between the i-th customer and the j-th facility.
auto init_distance_matrix(const vector<Customer> & customers, const vector<Facility> & facilities)
{
    auto square = [](auto x) { return x * x; };
    auto distance = [square](auto & a, auto & b) { return sqrt(square(a.x - b.x) + square(a.y - b.y)); };

    auto distance_matrix = DistanceMatrix(customers.size(), vector<double>(facilities.size()));
    for(auto i = 0; i < customers.size(); ++i)
    {
        for(auto j = 0; j < facilities.size(); ++j)
        {
            distance_matrix[i][j] = distance(customers[i], facilities[j]);
        }
    }

    return distance_matrix;
}

// Initialize features, feature[i][j] is the feature for the edge that connects the i-th customer and the j-th facility.
// feature[i][j] equals to the setup cost of the j-th facility, which means it is independent from i.
auto init_feature(const vector<Customer> & customers, const vector<Facility> & facilities)
{
    auto feature = Feature(customers.size(), vector<double>(facilities.size()));
    for(auto i = 0; i < customers.size(); ++i)
    {
        for(auto j = 0; j < facilities.size(); ++j)
        {
            feature[i][j] = facilities[j].cost;
        }
    }

    return feature;
}

// Calculate augmented cost for a certain set of assignment.
auto get_augmented_cost(const vector<Facility> & facilities, 
                        const DistanceMatrix & distance_matrix, const Penalty & penalty, double lambda)
{
    auto augmented_cost = 0.0;
    for(auto i = 0; i < facilities.size(); ++i)
    {
        auto facility = i;
        for(auto customer : facilities[facility].customers)
        {
            augmented_cost += distance_matrix[customer][facility] + lambda * penalty[customer][facility];
        }
        augmented_cost += !facilities[facility].customers.empty() * facilities[facility].cost;
    }

    return augmented_cost;
}

// Initialize the weight of penalty.
auto init_lambda(const vector<Customer> & customers, double cost, double alpha)
{
    return alpha * cost / customers.size();
}

// Initialize assignment by greedy algorithm.
auto init_assignment(vector<Customer> & customers, vector<Facility> & facilities, const DistanceMatrix & distance_matrix)
{
    for(auto i = 0; i < customers.size(); ++i)
    {
        auto customer = i;

        auto min_distance = numeric_limits<double>::infinity();
        auto min_facility = -1;
        for(auto j = 0; j < facilities.size(); ++j)
        {
            auto facility = j;
            if(min_distance > distance_matrix[customer][facility] && customers[customer].demand <= facilities[facility].available)
            {
                min_distance = distance_matrix[customer][facility];
                min_facility = facility;
            }
        }
        facilities[min_facility].customers.insert(customer);
        facilities[min_facility].available -= customers[customer].demand;

        customers[customer].facility = min_facility;
    }
}

// Calculate cost for a certain set of assignment.
auto get_cost(const vector<Facility> & facilities, const DistanceMatrix & distance_matrix)
{
    auto cost = 0.0;
    for(auto i = 0; i < facilities.size(); ++i)
    {
        auto facility = i;
        for(auto customer : facilities[facility].customers)
        {
            cost += distance_matrix[customer][facility];
        }
        cost += !facilities[facility].customers.empty() * facilities[facility].cost;
    }

    return cost;
}

// Sample random integer from [0, n - 1].
auto random_sample(int n)
{
	static default_random_engine generator(time(nullptr));
	uniform_int_distribution<int> distribution(0, n - 1);
	auto random_index = distribution(generator);

	return random_index;
}

// Select a customer, move it to a new facility.
// Select the move with the maximum gain in augmented cost.
auto select_customer_to_move(const vector<Customer> & customers, const vector<Facility> & facilities,
                                    const DistanceMatrix & distance_matrix, const Penalty & penalty, double lambda)
{
    auto max_augmented_gain = -numeric_limits<double>::infinity();
    auto max_customer = vector<int>();
    auto max_facility = vector<int>();
    for(auto i = 0; i < customers.size(); ++i)
    {
        for(auto j = 0; j < facilities.size(); ++j)
        {
            auto customer = i;
            auto facility_new = j;
            auto facility_old = customers[customer].facility;

            if(facility_new == facility_old) continue;

            if(facilities[facility_new].available < customers[customer].demand) continue;

            // If there is only one customer in the old facility, then remove this customer will cause the facility to shutdown.
            auto augmented_cost_old = distance_matrix[customer][facility_old] + 
                                        lambda * penalty[customer][facility_old] + 
                                        (facilities[facility_old].customers.size() == 1) * facilities[facility_old].cost;   

            // If there is no customer in the new facility, then move this customer to the new facility will cause it to setup.
            auto augmented_cost_new = distance_matrix[customer][facility_new] + 
                                        lambda * penalty[customer][facility_new] + 
                                        (facilities[facility_new].customers.size() == 0) * facilities[facility_new].cost;

            auto augmented_gain = augmented_cost_old - augmented_cost_new;

            if(max_augmented_gain < augmented_gain)
            {
                max_augmented_gain = augmented_gain;
                max_customer.clear();
                max_customer.push_back(customer);
                max_facility.clear();
                max_facility.push_back(facility_new);
            }
            else if(max_augmented_gain == augmented_gain)
            {
                max_customer.push_back(customer);
                max_facility.push_back(facility_new);
            }
        }
    }

    if(max_augmented_gain > 0.0)
    {
        auto index = random_sample(max_customer.size());
        
        auto customer_selected = max_customer[index];
        auto facility_old = customers[customer_selected].facility;
        auto facility_new = max_facility[index];
        return make_tuple(max_augmented_gain, customer_selected, facility_old, facility_new);
    }
    else
    {
        return make_tuple(0.0, -1, -1, -1);
    }
}

// Penalize features with the maximum utility.
auto add_penalty(const vector<Customer> & customers, Penalty & penalty, const Feature & feature, double & augmented_cost, double lambda)
{
    auto max_util = -numeric_limits<double>::infinity();
    auto max_util_customer = vector<int>();

    for(auto i = 0; i < customers.size(); ++i)
    {
        auto customer = i;
        auto facility = customers[customer].facility;

        auto util = feature[customer][facility] / (1 + penalty[customer][facility]);

        if(max_util < util)
        {
            max_util = util;
            max_util_customer.clear();
            max_util_customer.push_back(customer);
        }
        else if(max_util == util)
        {
            max_util_customer.push_back(customer);
        }
    }

    // Add penalty and update augmented cost.
    for(auto customer : max_util_customer)
    {
        auto facility = customers[customer].facility;
        penalty[customer][facility] += 1;
        
        augmented_cost += lambda;
    }
}

// Save result to file
auto save_result(const vector<Customer> & customers, double cost)
{
    cout << cost << " " << 0 << endl;
    for(auto & customer : customers)
    {    
        cout << customer.facility << " ";
    }
    cout << endl;
}

// Perform the Guided Local Search.
auto search(vector<Customer> & customers, vector<Facility> & facilities)
{
 cout << fixed << setprecision(6);
 cerr << fixed << setprecision(6);
    auto alpha = 0.05;

    auto distance_matrix = init_distance_matrix(customers, facilities);

    init_assignment(customers, facilities, distance_matrix);

    auto feature = init_feature(customers, facilities);

    auto cost = get_cost(facilities, distance_matrix);

    auto lambda = 0.0;

    auto penalty = Penalty(customers.size(), vector<int>(facilities.size(), 0));

    auto augmented_cost = get_augmented_cost(facilities, distance_matrix, penalty, lambda);

    auto best_cost = cost;
    auto best_customers = customers;

    auto step_limit = 100000000;


    for(auto step = 0; step < step_limit; ++step)
    {
     cerr << step + 1 << " " << step_limit << " " << cost << " " << augmented_cost << " " << best_cost << endl;

        auto [augmented_cost_gain_by_customer_move, customer, facility_old, facility_new] = 
                select_customer_to_move(customers, facilities, distance_matrix, penalty, lambda);


        if(customer == -1)
        {
            if(!lambda) lambda = init_lambda(customers, cost, alpha);

            add_penalty(customers, penalty, feature, augmented_cost, lambda);
        }
        else
        {
            auto cost_old = distance_matrix[customer][facility_old] + 
                            (facilities[facility_old].customers.size() == 1) * facilities[facility_old].cost;

            auto cost_new = distance_matrix[customer][facility_new] + 
                            (facilities[facility_new].customers.size() == 0) * facilities[facility_new].cost;

            auto cost_gain = cost_old - cost_new;
            auto augmented_cost_gain = augmented_cost_gain_by_customer_move;

            cost -= cost_gain;
            augmented_cost -= augmented_cost_gain;

            facilities[facility_old].customers.erase(customer);
            facilities[facility_old].available += customers[customer].demand;

            facilities[facility_new].customers.insert(customer);
            facilities[facility_new].available -= customers[customer].demand;

            customers[customer].facility = facility_new;
        }

        if(best_cost > cost)
        {
            best_cost = cost;
            best_customers = customers;
        }
    }
            save_result(best_customers, best_cost);
}

int main(int argc, char * argv [])
{
    auto [facilities, customers] = read_data();
    
    search(customers, facilities);

    return 0;
}
