#include <bits/stdc++.h>
#include "ortools/algorithms/knapsack_solver.h"

using namespace std;

namespace operations_research {
void RunKnapsackExample() {
 KnapsackSolver solver(KnapsackSolver::KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER, "KnapsackExample");
 vector< int64 > capacities(1);
 int item_count;
 cin >> item_count >> capacities[0];
 cerr << item_count << " " << capacities[0] << endl;
 vector < int64 > values(item_count);
 vector < vector < int64 > > weights(1, vector < int64 > (item_count));
 for(int i=0;i<item_count;i++) cin >> values[i] >> weights[0][i];
 solver.Init(values, weights, capacities);
 int64 computed_value= solver.Solve();
 cout << computed_value << " " << 1 << endl;
 for (int i=0;i<item_count;i++) cout << solver.BestSolutionContains(i) << " ";
 cout << endl;
 LOG(INFO) << "Total value: " << computed_value;
}
}

int main(int argc, char **argv) {
 operations_research::RunKnapsackExample();
 return EXIT_SUCCESS;
}
