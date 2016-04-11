#ifndef QUADRATIC_INTERPOL_H
#define QUADRATIC_INTERPOL_H

#include "Approx_func.h"
#include <vector>


class Quadratic_interpol : public Approx_func {
    public:
    Quadratic_interpol (const vector<pair<double, double>> &init);
    double get_value(double arg);
private:
    typedef const pair<double, double> cpdd;
    double calc_value(cpdd &prev_point, cpdd &cur_point, cpdd &next_point, double arg);
};

#endif // QUADRATIC_INTERPOL_H
