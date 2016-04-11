#ifndef APPROX_FUNC_H
#define APPROX_FUNC_H

#include <vector>

using namespace std;

struct Data {
    Data(const vector<pair<double, double>> &init_data) : data(init_data) {}
    const vector<pair<double, double>> data;
};

class Approx_func {
public:
    Approx_func(const vector<pair<double, double>> &init_data);
    virtual double get_value(double) = 0;
    double operator() (double arg);
protected:
    const vector<pair<double, double>> &args_and_vals;
    /*if arg <= x_1 return false and value f(x_1)
      if arg >= x_n return false and value f(x_n)
      else  return true*/
    pair<bool, double> check_borders(double arg);

    /* seek i :  x_(i-1) <= arg <= x_i */
    unsigned int find_segment(double arg);
};
#endif // APPROX_FUNC_H
