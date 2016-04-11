#include "Simple_interpol.h"

Simple_interpol::Simple_interpol(const vector<pair<double, double>> &init) : Approx_func(init) {}

double Simple_interpol::get_value(double arg) {
    pair<bool, double> check_result = check_borders(arg);
    if (!check_result.first) return check_result.second;
    unsigned int segment = find_segment(arg);
    const pair<double, double> &prev_point = args_and_vals.at(segment - 1);
    const pair<double, double> &cur_point = args_and_vals.at(segment);
    return (arg - prev_point.first) <= (cur_point.first - arg) ? prev_point.second : cur_point.second;
}
