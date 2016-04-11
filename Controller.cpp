#include "Controller.h"

void Controller::run() {
    Data data = get_init_data();
    cshptrAppF func = select_approx_func(data);
    vector<double> reqst_args = get_reqst_args();
    vector<double> result_values = calc_func_values(reqst_args, func);
    write_result("result.txt", reqst_args, result_values);
    bool flag = true;
    string result_file_name = "result.txt";
    while (flag) {
        cout << "Result is counted - check result.txt" << endl;
        cout << endl;
        cout << "If you want to change interpolation method enter 1, enter 0 to exit" << endl;
        cout << "warning: previous result(result.txt) will be overwrited," << endl;
        cout << "check them or save them in other file." << endl;
        cin >> flag;
        if (flag) {
            cshptrAppF new_func = select_approx_func(data);
            result_values = calc_func_values(reqst_args, new_func);
            write_result("result.txt", reqst_args, result_values);
        }
    }
    char t;
    cin >>t;
}

vector<pair<double, double>> Controller::get_init_data() {
    cout << "Enter initial function values filename (*.txt):" << endl;
    string values_file;
    cin >> values_file;
    return pars.parse_function(values_file);
}

Controller::cshptrAppF Controller::select_approx_func(const Data &d) {
    cout << "Enter interpolation method name:" << endl;
    cout << "For step method enter - 1," << endl;
    cout << "For linear method enter - 2," << endl;
    cout << "For quadratic method enter - 3." << endl;
    int method_str;
    cin >> method_str;
    Approx_func_fabr::Methods method;
    if(method_str == 1) method = Approx_func_fabr::Step;
    if(method_str == 2) method = Approx_func_fabr::Linear;
    if(method_str == 3) method = Approx_func_fabr::Quadratic;
    return fabr.create_approx_func(d.data, method);
}

vector<double> Controller::get_reqst_args() {
    cout << "Enter argument values file name (*.txt):" << endl;
    string args_file;
    cin >> args_file;
    return pars.parse_reqst_vals(args_file);
}

vector<double> Controller::calc_func_values(const vector<double> &args, cshptrAppF &func) {
    unsigned int size = args.size();
    vector<double> result_values;
    for(int i = 0; i < size; ++i) {
        result_values.push_back((*func).get_value(args.at(i)));
    }
    return result_values;
}

void Controller::write_result(string out_file, const vector<double> &args, const vector<double> &values){
    ofstream os(out_file);
    unsigned int size = args.size();
    os << size << endl;
    for(unsigned int i = 0; i < size; ++ i) {
        os << args.at(i) << " " <<  values.at(i) << endl;
    }
}
