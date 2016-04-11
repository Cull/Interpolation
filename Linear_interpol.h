#ifndef LINEAR_INTERPOL_H
#define LINEAR_INTERPOL_H

#include "Approx_func.h"
#include <vector>

class Linear_interpol : public Approx_func{
public:
    Linear_interpol(const vector<pair<double, double>> &init);
    double get_value(double arg);
};

#endif // LINEAR_INTERPOL_H
