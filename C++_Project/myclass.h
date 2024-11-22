//Project:Data Storage system - header
//Jen Feron
#ifndef MY_CLASS_H // Will only be true the once!
#define MY_CLASS_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <vector>
#include <deque>
#include <utility>
#include <memory>
#include <algorithm>
#include <tuple>

class function{
    //abstract base class for function classes
    protected:
    virtual ~function(){}
    virtual double apply_func(double x)=0;
    virtual void set_constant(const double constant_in) {}
};
class function_power: public function{
    //dervived class showing power relation
    protected:
    double power {0};
    double constant {0};
    public:
    function_power() = default;
    function_power(double n, double A): power{n}, constant{A} {};
    ~function_power() {}
    void set_power(const double power_in){power=power_in;};
    void set_constant(const double constant_in){constant=constant_in;};
    double apply_func(double x){return pow(constant*x,power);}
    friend std::istream& operator>>(std::istream& is, function_power& f);
    double percentage_error(double err){return power*err;}
};
class function_sum: public function{
    //derived class showing sum relation
    protected:
    public:
    double constant{0};
    function_sum() = default;
    function_sum(double A): constant{A} {};
    ~function_sum() {}
    void set_constant(const int constant_in){constant=constant_in;};
    double apply_func(double x){return x+constant;}
    friend std::istream& operator>>(std::istream& is, function_sum& f);
    double percentage_error_1(double err, double measurement);
};

class measurement_base{
    //Abstract base class for measurements
    protected:
    std::string units{"units"};
    std::string name{"y"};
    measurement_base() = default;
    measurement_base(std::string units_in, std::string name_in): units{units_in}, name{name_in} {}
    virtual ~measurement_base(){}
    virtual std::string return_name() {return "ghost";}
    virtual double return_measurement() {return 0.0;}
    virtual double return_uncertainty() {return 0.0;}
    virtual std::string return_units() {return units;}
    virtual void info()=0;
};
class indep_measurement: public measurement_base{
    //dervived class for independent variable
    protected:
    double measurement{0};
    double measurement_error{0};
    double systematic_error{0};
    public:
    indep_measurement() = default;
    indep_measurement(std::string name_in, double meas, double meas_err, double sys_err, std::string units_in): measurement_base{units_in, name_in}, measurement{meas}, measurement_error{meas_err}, systematic_error{sys_err} {};
    ~indep_measurement() {}
    void info();
    void set_measurement(const double measurement_in){measurement=measurement_in;};
    void set_error(const double error_in){measurement_error=error_in;};
    void set_sys_error(const double sys_error_in){systematic_error=sys_error_in;};
    void set_name(const std::string name_in){name=name_in;};
    double total_error(){return sqrt(pow(measurement_error,2)+pow(systematic_error,2));}
    double percentage_error(){return total_error()/measurement;}
    std::string return_name() {return name;}
    double return_measurement() {return measurement;}
    double return_uncertainty() {return measurement_error;}
    double return_sys_err() {return systematic_error;}
    std::string return_units() {return units;}
    friend std::istream& operator>>(std::istream& is, indep_measurement& y);
};
class dep_measurement: public measurement_base{
    //dervived class for dependent measurement
    public:
    dep_measurement() = default;
    dep_measurement(std::string name_in, std::string units_in): measurement_base{units_in, name_in} {};
    ~dep_measurement() {}
};
class dep_measure_actual: public dep_measurement{
    //derrived class for the measured value of the dependent variable
    protected:
    double measurement{0};
    double uncertainty{0};
    public:
    dep_measure_actual() = default;
    dep_measure_actual(std::string y, std::string units_in, double measure, double uncert): measurement{measure}, uncertainty{uncert}, dep_measurement{y, units_in} {};
    void info();
    ~dep_measure_actual() {}
    std::string return_name() {return name;}
    double return_measurement() {return measurement;}
    double return_uncertainty() {return uncertainty;}
    std::string return_units() {return units;}
    friend std::istream& operator>>(std::istream& is, dep_measure_actual& x);
};
//namespace defined to allow for multiple classes with the same name
//derived class for the predicted values of the dependent variable
namespace pow_ns{
class dep_measure_predicted: public dep_measurement{
    private:
    class std::unique_ptr<indep_measurement> &variable;
    class std::unique_ptr<function_power> &func1;
    public:
    dep_measure_predicted(std::string y, std::string units_in, std::unique_ptr<indep_measurement> &x, std::unique_ptr<function_power> &func1_in): func1{func1_in}, dep_measurement{y, units_in},  variable{x} {};
    ~dep_measure_predicted() {}
    void info();
    double measure_power(){return func1->apply_func(variable->return_measurement());}
    double uncert_power(){return func1->percentage_error(variable -> return_uncertainty());}
    std::string return_name() {return name;}
    double return_measurement() {return measure_power();}
    double return_uncertainty() {return uncert_power();}
    virtual std::string return_units() {return units;}
};
}
namespace sum_ns{
class dep_measure_predicted: public dep_measurement{
    private:
    class std::unique_ptr<indep_measurement> &variable;
    class std::unique_ptr<function_sum> &func2;
    public:
    dep_measure_predicted(std::string y, std::string units_in, std::unique_ptr<indep_measurement> &x,std::unique_ptr<function_sum> &func2_in): func2{func2_in}, dep_measurement{y, units_in}, variable{x} {};
    ~dep_measure_predicted() {}
    void info();
    double measure_sum(){return func2->apply_func(variable->return_measurement());}
    double uncert_sum(){return func2->percentage_error_1(variable->return_uncertainty(),variable->return_measurement());}
    std::string return_name() {return name;}
    double return_measurement() {return measure_sum();}
    double return_uncertainty() {return uncert_sum();}
    std::string return_units() {return units;}
};
}

class experiment{
    //experiment class to store deque containers of the other measurement classes in one place
    private:
    std::deque <class dep_measure_actual>  dep_measurements;
    std::deque <class indep_measurement> indep_measurements;
    std::deque <class sum_ns::dep_measure_predicted> sum_predict;
    std::deque <class pow_ns::dep_measure_predicted> power_predict;
    std::string power_or_sum;
    public:
    static int experimentcount; //static data variable to allow for the number of experiments to be counted
    experiment(std::deque <class dep_measure_actual>  dep_measurements_in, std::deque <class indep_measurement> indep_measurements_in, std::deque <class sum_ns::dep_measure_predicted> sum_predict_in, std::deque <class pow_ns::dep_measure_predicted> power_predict_in, std::string pos): dep_measurements{dep_measurements_in}, indep_measurements{indep_measurements_in}, sum_predict{sum_predict_in}, power_predict{power_predict_in}, power_or_sum{pos} {experimentcount++;};
    void add_expt_start_pow(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<pow_ns::dep_measure_predicted> const &z);
    void add_expt_start_sum(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<sum_ns::dep_measure_predicted> const &z);
    void add_expt_end_pow(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<pow_ns::dep_measure_predicted> const &z);
    void add_expt_end_sum(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<sum_ns::dep_measure_predicted> const &z);
    ~experiment() {}
    void print_info();
    std::vector<std::pair<double,double>> give_measurements_iv();
    std::vector<std::pair<double,double>> give_measurements_dv();
    std::vector<std::tuple<double,double,double,double>> give_measurements_all();
    friend void write_to_file(experiment& e);
};
#endif