#ifndef SIMPLE_INTERPOL_H
#define SIMPLE_INTERPOL_H

#include "Approx_func.h"
#include <vector>

using namespace std;


class Simple_interpol : public Approx_func {
public:
    Simple_interpol(const vector<pair<double, double>> &init);
    double get_value(double arg);
};

#endif // SIMPLE_INTERPOL_H
