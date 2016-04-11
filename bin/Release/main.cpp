#include <iostream>
#include <fstream>
#include <vector>
#include <memory>


using namespace std;

struct Data {
    Data(const vector<pair<double, double>> &init_data) : data(init_data) {}
    const vector<pair<double, double>> data;
};

class Approx_func {
public:
    Approx_func(const vector<pair<double, double>> &init_data)  : args_and_vals(init_data) {}
    virtual double get_value(double) = 0;
    virtual double operator() (double arg) = 0;
protected:
    const vector<pair<double, double>> &args_and_vals;
    /*if arg <= x_1 return false and value f(x_1)
      if arg >= x_n return false and value f(x_n)
      else  return true*/
    pair<bool, double> check_borders(double arg) {
        if (arg <= args_and_vals.at(0).first) {
            return pair<bool, double>(false, args_and_vals.at(0).second);
        }

        if (arg >= args_and_vals.at(args_and_vals.size()-1).first) {
            return pair<bool,double>(false, args_and_vals.at(args_and_vals.size()-1).second);
        }

        return pair<bool,double>(true, 0);
    }

    /* seek i :  x_(i-1) <= arg <= x_i */
    unsigned int find_segment(double arg) {
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
};

class Simple_interpol : public Approx_func {
public:
    Simple_interpol(const vector<pair<double, double>> &init) : Approx_func(init) {}
    double get_value(double arg) {
        pair<bool, double> check_result = check_borders(arg);
        if (!check_result.first) return check_result.second;
        unsigned int segment = find_segment(arg);
        const pair<double, double> &prev_point = args_and_vals.at(segment - 1);
        const pair<double, double> &cur_point = args_and_vals.at(segment);
        return (arg - prev_point.first) <= (cur_point.first - arg) ? prev_point.second : cur_point.second;
    }
    double operator() (double arg) {
        return get_value(arg);
    }
};

class Linear_interpol : public Approx_func {
public:
    Linear_interpol (const vector<pair<double, double>> & init) : Approx_func(init) {}
    double get_value(double arg) {
        pair<bool, double> check_result = check_borders(arg);
        if (!check_result.first) return check_result.second;
        unsigned int segment = find_segment(arg);
        const pair<double, double> &prev_point = args_and_vals.at(segment - 1);
        const pair<double, double> &cur_point = args_and_vals.at(segment);
        double linear_coef = (cur_point.second - prev_point.second) / (cur_point.first - prev_point.first);
        return prev_point.second + linear_coef * (arg - prev_point.first);
    }
    double operator()(double arg) {
        return get_value(arg);
    }
};

class Quadratic_interpol : public Approx_func {
public:
    Quadratic_interpol (const vector<pair<double, double>> &init) : Approx_func(init) {}
    double get_value(double arg) {
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
    double operator() (double arg) {
        return get_value(arg);
    }
private:
    typedef const pair<double, double> cpdd;
    double calc_value(cpdd &prev_point, cpdd &cur_point, cpdd &next_point, double arg) {
        double prev_coef = (arg - cur_point.first) * (arg - next_point.first);
        prev_coef /= (prev_point.first - cur_point.first) * (prev_point.first - next_point.first);
        double cur_coef = (arg - prev_point.first) * (arg - next_point.first);
        prev_coef /= (cur_point.first - prev_point.first) * (cur_point.first - next_point.first);
        double next_coef = (arg - prev_point.first) * (arg - cur_point.first);
        prev_coef /= (next_point.first - prev_point.first) * (next_point.first - cur_point.first);
        return prev_coef * prev_point.second + cur_coef * cur_point.second + next_coef * next_point.second;
    }
};

class Approx_func_fabr {
public:
    enum Methods {Step, Linear, Quadratic};
    const shared_ptr<Approx_func> create_approx_func(const vector<pair<double, double>> &args_and_vls, Methods method){
        if (method == Step) return shared_ptr<Approx_func>(new Simple_interpol(args_and_vls));
        if (method == Linear) return shared_ptr<Approx_func>(new Linear_interpol(args_and_vls));
        if (method == Quadratic) return shared_ptr<Approx_func>(new Quadratic_interpol(args_and_vls));
        cout << "unsupported method was inputed - aplying default(step) method " << endl;
        return shared_ptr<Approx_func>(new Simple_interpol(args_and_vls));
    }
};

class Parser {
public:
    vector<pair<double, double>> parse_function(const string& init_file) {
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
    vector<double> parse_reqst_vals(const string& reqst_arg_file) {
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
};

class Controller {
    typedef const shared_ptr<Approx_func> cshptrAppF;
public:
    void run() {
        Data data = init_data();
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
private:
    Parser pars;
    Approx_func_fabr fabr;
    vector<pair<double, double>> init_data() {
        cout << "Enter initial function values filename (*.txt):" << endl;
        string values_file;
        cin >> values_file;
        return pars.parse_function(values_file);
    }
    cshptrAppF select_approx_func(const Data &d) {
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
    vector<double> get_reqst_args() {
        cout << "Enter argument values file name (*.txt):" << endl;
        string args_file;
        cin >> args_file;
        return pars.parse_reqst_vals(args_file);
    }
    vector<double> calc_func_values(const vector<double> &args, cshptrAppF &func) {
        unsigned int size = args.size();
        vector<double> result_values;
        for(int i = 0; i < size; ++i) {
            result_values.push_back((*func).get_value(args.at(i)));
        }
        return result_values;
    }
    void write_result(string out_file, const vector<double> &args, const vector<double> &values){
        ofstream os(out_file);
        unsigned int size = args.size();
        os << size << endl;
        for(unsigned int i = 0; i < size; ++ i) {
            os << args.at(i) << " " <<  values.at(i) << endl;
        }
    }
};

int main(int argc, char* argv[])
{
    Controller c;
    c.run();
    return 0;
}
