#include "Approx_func.h"



using namespace std;

Approx_func::Approx_func(const vector<pair<double, double>> &init_data)  : args_and_vals(init_data) {}

double Approx_func::operator() (double arg) {
    return get_value(arg);
}

pair<bool, double> Approx_func::check_borders(double arg) {
    if (arg <= args_and_vals.at(0).first) {
        return pair<bool, double>(false, args_and_vals.at(0).second);
    }
    if (arg >= args_and_vals.at(args_and_vals.size()-1).first) {
        return pair<bool,double>(false, args_and_vals.at(args_and_vals.size()-1).second);
    }
    return pair<bool,double>(true, 0);
}

unsigned int Approx_func::find_segment(double arg) {
    unsigned int i = 1;
    unsigned int args_size = args_and_vals.size();
    while (i < args_size) {
        if (arg >= args_and_vals.at(i).first) {
            ++i;
        } else {
            break;
        }
    }
    return i;
}

