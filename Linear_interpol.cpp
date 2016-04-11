#include "Linear_interpol.h"

Linear_interpol::Linear_interpol(const vector<pair<double, double>> & init) : Approx_func(init) {}

double Linear_interpol::get_value(double arg) {
    pair<bool, double> check_result = check_borders(arg);
    if (!check_result.first) return check_result.second;
    unsigned int segment = find_segment(arg);
    const pair<double, double> &prev_point = args_and_vals.at(segment - 1);
    const pair<double, double> &cur_point = args_and_vals.at(segment);
    double linear_coef = (cur_point.second - prev_point.second) / (cur_point.first - prev_point.first);
    return prev_point.second + linear_coef * (arg - prev_point.first);
}
