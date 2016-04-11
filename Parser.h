#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Parser {
public:
    /* parse init  values for func initialization*/
    vector<pair<double, double>> parse_function(const string& init_file);
    /* parse args values for approximation*/
    vector<double> parse_reqst_vals(const string& reqst_arg_file);
};

#endif // PARSER_H
