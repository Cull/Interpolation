#include "Approx_func_fabr.h"

const shared_ptr<Approx_func> Approx_func_fabr::create_approx_func(const vector<pair<double, double>> &args_and_vls, Methods method){
    if (method == Step) return shared_ptr<Approx_func>(new Simple_interpol(args_and_vls));
    if (method == Linear) return shared_ptr<Approx_func>(new Linear_interpol(args_and_vls));
    if (method == Quadratic) return shared_ptr<Approx_func>(new Quadratic_interpol(args_and_vls));
    cout << "unsupported method was inputed - applying default(step) method " << endl;
    return shared_ptr<Approx_func>(new Simple_interpol(args_and_vls));
}
