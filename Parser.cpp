#include "Parser.h"

vector<pair<double, double>> Parser::parse_function(const string& init_file) {
    ifstream is(init_file, ifstream::in);
    string file_name = init_file;
    while (!is.is_open()) {
        cout << "There is no file called: " << file_name << " please, enter correct file in folder with exe file" << endl;
        cin >> file_name;
        is.open(file_name, ifstream::in);
    }
    vector<pair<double, double>> result;
    unsigned int size;
    is >> size;
    double arg;
    double func_value;
    for(unsigned int i = 0; i < size; ++i) {
        is >> arg;
        is >> func_value;
        result.push_back(pair<double,double>(arg,func_value));
    }
    return result;
}

vector<double> Parser::parse_reqst_vals(const string& reqst_arg_file) {
    ifstream is(reqst_arg_file, ifstream::in);
    string file_name = reqst_arg_file;
    while (!is.is_open()) {
        cout << "There is no file called: " << file_name << " please, enter correct filename in folder with exe file" << endl;
        cin >> file_name;
        is.open(file_name, ifstream::in);
    }
    vector<double> result;
    unsigned int size;
    is >> size;
    double arg;
    for(unsigned int i = 0; i < size; ++i) {
        is >> arg;
        result.push_back(arg);
    }
    return result;
}
