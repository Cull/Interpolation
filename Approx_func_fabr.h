#ifndef APPROX_FUNC_FABR_H
#define APPROX_FUNC_FABR_H

#include <vector>
#include <memory>
#include <iostream>
#include "Approx_func.h"
#include "Simple_interpol.h"
#include "Linear_interpol.h"
#include "Quadratic_interpol.h"



class Approx_func_fabr {
public:
    enum Methods {Step, Linear, Quadratic};
    const shared_ptr<Approx_func> create_approx_func(const vector<pair<double, double>> &args_and_vls, Methods method);
};

#endif // APPROX_FUNC_FABR_H
