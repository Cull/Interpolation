#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <memory>
#include <vector>
#include "Approx_func.h"
#include "Approx_func_fabr.h"
#include "Parser.h"

using namespace std;

class Controller {
    typedef const shared_ptr<Approx_func> cshptrAppF;
public:
    /*main cycle*/
    void run();
private:
    Parser pars;
    Approx_func_fabr fabr;
    /*get func initialization values*/
    vector<pair<double, double>> get_init_data();
    /*choose approx metod*/
    cshptrAppF select_approx_func(const Data &d);
    /*get args values to calc func approximation*/
    vector<double> get_reqst_args();
    vector<double> calc_func_values(const vector<double> &args, cshptrAppF &func);
    void write_result(string out_file, const vector<double> &args, const vector<double> &values);
};

#endif // CONTROLLER_H
