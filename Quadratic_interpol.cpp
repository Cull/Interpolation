#include "Quadratic_interpol.h"

Quadratic_interpol::Quadratic_interpol(const vector<pair<double, double>> &init) : Approx_func(init) {}

double Quadratic_interpol::get_value(double arg) {
    pair<bool, double> check_result = check_borders(arg);
    if (!check_result.first) return check_result.second;
    unsigned int segment = find_segment(arg);
    const pair<double, double> &prev_point = args_and_vals.at(segment - 1);
    const pair<double, double> &cur_point = args_and_vals.at(segment);
    unsigned int points_count = args_and_vals.size();
    if (points_count > 2) {
        if (segment < points_count - 1) {
            const pair<double, double> &next_point = args_and_vals.at(segment + 1);
            return calc_value(prev_point,cur_point,next_point, arg);
        } else {
            const pair<double, double> &before_prev_point = args_and_vals.at(segment - 2);
            return calc_value(before_prev_point,prev_point,cur_point, arg);
        }
    }
    double linear_coef = (cur_point.second - prev_point.second) / (cur_point.first - prev_point.first);
    return prev_point.second + linear_coef * (arg - prev_point.first);
}

double Quadratic_interpol::calc_value(cpdd &prev_point, cpdd &cur_point, cpdd &next_point, double arg) {
    double prev_coef = (arg - cur_point.first) * (arg - next_point.first);
    prev_coef /= (prev_point.first - cur_point.first) * (prev_point.first - next_point.first);
    double cur_coef = (arg - prev_point.first) * (arg - next_point.first);
    prev_coef /= (cur_point.first - prev_point.first) * (cur_point.first - next_point.first);
    double next_coef = (arg - prev_point.first) * (arg - cur_point.first);
    prev_coef /= (next_point.first - prev_point.first) * (next_point.first - cur_point.first);
    return prev_coef * prev_point.second + cur_coef * cur_point.second + next_coef * next_point.second;
}
