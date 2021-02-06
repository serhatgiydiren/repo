// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>
#include "ortools/linear_solver/linear_solver.h"

using namespace std;

namespace operations_research {

struct loc
{
 double x;
 double y;
};
 
struct warehouse
{
 double cost;
 int served;
 int cap_cur;
 loc lc;
};
 
struct customer
{
 int demand;
 int w_id;
 loc lc;
};

double dist(const loc &lc1, const loc &lc2)
{
 return sqrt(pow(lc1.x-lc2.x,2)+pow(lc1.y-lc2.y,2));
}

void simple_mip_program() {
 //MPSolver solver("warehouse_location", MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);
 MPSolver solver("warehouse_location", MPSolver::GLOP_LINEAR_PROGRAMMING);

 cout << fixed << setprecision(6);
 cerr << fixed << setprecision(6);

 int n,m;

 cin >> n >> m;

 vector < warehouse > w(n);
 vector < customer > c(m);

 const double infinity = solver.infinity();

 vector < const MPVariable* > var_x(n);
 vector < vector < const MPVariable* > > var_y(n, vector < const MPVariable* > (m));
 //vector < vector < MPConstraint* > > c0(n, vector < MPConstraint* > (m));
 vector < MPConstraint* > c1(m);
 vector < MPConstraint* > c2(n);

 for(int i=0;i<n;i++)
 {
  cin >> w[i].cost >> w[i].cap_cur >> w[i].lc.x >> w[i].lc.y;
  var_x[i] = solver.MakeIntVar(0.0, 1.0, "");
 }
 for(int i=0;i<m;i++) cin >> c[i].demand >> c[i].lc.x >> c[i].lc.y;
 for(int i=0;i<n;i++)
 {
  c2[i] = solver.MakeRowConstraint(0.0, w[i].cap_cur, "");
  for(int j=0;j<m;j++)
  {
   var_y[i][j] = solver.MakeIntVar(0.0, 1.0, "");
   //c0[i][j] = solver.MakeRowConstraint(-infinity, 0.0, "");
   //c0[i][j]->SetCoefficient(var_y[i][j], 1);
   //c0[i][j]->SetCoefficient(var_x[i], -1);
   c2[i]->SetCoefficient(var_y[i][j], c[j].demand);
  }
 }
 for(int j=0;j<m;j++)
 {
  c1[j] = solver.MakeRowConstraint(1.0, 1.0, "");
  for(int i=0;i<n;i++)
  {
   c1[j]->SetCoefficient(var_y[i][j], 1);
  }
 }

 LOG(INFO) << "Number of variables = " << solver.NumVariables();
 LOG(INFO) << "Number of constraints = " << solver.NumConstraints();

 MPObjective* const objective = solver.MutableObjective();
 for(int i=0;i<n;i++) objective->SetCoefficient(var_x[i], w[i].cost);
 for(int i=0;i<n;i++) for(int j=0;j<m;j++) objective->SetCoefficient(var_y[i][j], dist(w[i].lc,c[j].lc));
 objective->SetMinimization();

 const MPSolver::ResultStatus result_status = solver.Solve();
 cout << objective->Value() << " ";
 if (result_status == MPSolver::OPTIMAL) cout << 1 << endl;
 else cout << 0 << endl;
 for(int j=0;j<m;j++)
 {
  for(int i=0;i<n;i++)
  {
   if (var_y[i][j]->solution_value()==1)
   {
    cout << i << " ";
    break;
   }
  }
 }
 cerr << endl;
 /*LOG(INFO) << "Solution:";
 LOG(INFO) << "Objective value = " << objective->Value();
 LOG(INFO) << "x = " << var_x[0]->solution_value();
 LOG(INFO) << "y = " << var_x[1]->solution_value();
 LOG(INFO) << "\nAdvanced usage:";
 LOG(INFO) << "Problem solved in " << solver.wall_time() << " milliseconds";
 LOG(INFO) << "Problem solved in " << solver.iterations() << " iterations";
 LOG(INFO) << "Problem solved in " << solver.nodes() << " branch-and-bound nodes";*/
}
}

int main() {
 operations_research::simple_mip_program();
 return EXIT_SUCCESS;
}
