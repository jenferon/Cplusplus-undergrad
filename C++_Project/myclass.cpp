//Project:Data Storage system - class functions definitions
//use this to store longer functions in classes for readablitlty of code
//Jen Feron
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
#include "myclass.h"

//define functions for function power class
std::istream& operator>>(std::istream& is, function_power& f){
    std::cout<<"Input for power function:"<<std::endl;
    std::cout<<"Determine the relationship between the dependent and independent variables"<<std::endl;
    std::cout<<"Please enter in the form: constant power: ";
    is >> f.constant >> f.power;
    return is;
}
//define functions for function sum class
std::istream& operator>>(std::istream& is, function_sum& f){
    std::cout<<"Input for sum function:"<<std::endl;
    std::cout<<"Determine the relationship between the dependent and independent variables"<<std::endl;
    std::cout<<"Please enter the constant to be added (can be positive or negative): ";
    is>>f.constant;
    return is;
}
double function_sum::percentage_error_1(double err, double measurement){
    double error =err/(apply_func(measurement));
    return error;
}
//define functions for independent measurement class
void indep_measurement::info(){
    std::cout<<"("<<measurement<<" +/- "<<measurement_error<<" +/- "<<systematic_error<<")"<<units<<std::endl;
}
std::istream& operator>>(std::istream& is, indep_measurement& y){
    std::cout<<"Input for independent measurement:"<<std::endl;
    std::cout<<"Enter in the form: name measurement error systematic error units"<<std::endl;
    is>> y.name >> y.measurement >> y.measurement_error >> y.systematic_error >> y.units;
    return is;
}
//define functions for dependent measurement actual class
std::istream& operator>>(std::istream& is, dep_measure_actual& x){
    std::cout<<"Input for dependent measurement:"<<std::endl;
    std::cout<<"Enter in the form: name measurement error units"<<std::endl;
    is>> x.name >> x.measurement >> x.uncertainty >> x.units;
    return is;
}
void dep_measure_actual::info(){
    std::cout<<"("<<measurement<<" +/- "<<uncertainty<<")"<<units<<std::endl;
}
//define functions for pow_ns dep_measure_predicted
void pow_ns::dep_measure_predicted::info(){
    std::cout<<name<<measure_power()<<"+/-"<<uncert_power()<<std::endl;
}
//define functions for sum_ns dep_measure_predicted
void sum_ns::dep_measure_predicted::info(){
    std::cout<<name<<measure_sum()<<"+/-"<<uncert_sum()<<std::endl;
}
//define functions for experiment class
void experiment::add_expt_start_pow(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<pow_ns::dep_measure_predicted> const &z){
    dep_measurements.push_front(*x);
    indep_measurements.push_front(*y);
    power_predict.push_front(*z);
}
void experiment::add_expt_start_sum(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<sum_ns::dep_measure_predicted> const &z){
    dep_measurements.push_front(*x);
    indep_measurements.push_front(*y);
    sum_predict.push_front(*z);
}
void experiment::add_expt_end_pow(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<pow_ns::dep_measure_predicted> const &z){
    dep_measurements.push_back(*x);
    indep_measurements.push_back(*y);
    power_predict.push_back(*z);
}
void experiment::add_expt_end_sum(std::unique_ptr<dep_measure_actual> const &x, std::unique_ptr<indep_measurement> const &y, std::unique_ptr<sum_ns::dep_measure_predicted> const &z){
    dep_measurements.push_back(*x);
    indep_measurements.push_back(*y);
    sum_predict.push_back(*z);
}
void experiment::print_info(){
    //prints out all measurements in order of the independent variable
    std::vector<std::tuple<double,double,double,double>> vec1 = give_measurements_all();
    std::cout.precision(3);
    int size = dep_measurements.size();
    std::cout<<"Independent variable: "<<indep_measurements[0].return_name()<<"      "<<"Dependent Variable: "<<dep_measurements[0].return_name()<<std::endl;
    std::cout<<"Date "<<std::endl;
    time_t now = time(0);
    // convert now to string form
    char* dt = ctime(&now);
    std::cout<<dt<<std::endl;
    std::cout<<"Measurement "<<"Error "<<"Systematic Error "<<" Measurement "<<"Error"<<std::endl;
     for(int i =0; i<size; i++ ){
        std::cout<<"("<<std::get<0>(vec1[i])<<"+/-"<<std::get<1>(vec1[i])<<"+/-"<<indep_measurements[i].return_sys_err()<<")"<<indep_measurements[i].return_units();
        std::cout<<"("<<std::get<2>(vec1[i])<<"+/-"<<std::get<3>(vec1[i])<<")"<<dep_measurements[i].return_units()<<std::endl;  
    }
}
std::vector<std::pair<double,double>> experiment::give_measurements_iv(){
    //function to give back a pair of the independent variable and it's uncertainty
    std::vector<std::pair<double,double>> vec1;
    for(int i=0; i<indep_measurements.size(); i++){
        vec1.push_back(std::make_pair(indep_measurements[i].return_measurement(),indep_measurements[i].return_uncertainty()));
    }
    return vec1;
}
std::vector<std::pair<double,double>> experiment::give_measurements_dv(){
    std::vector<std::pair<double,double>> vec1;
    for(int i=0; i<dep_measurements.size(); i++){
        vec1.push_back(std::make_pair(dep_measurements[i].return_measurement(),dep_measurements[i].return_uncertainty()));
    }
    return vec1;
}
std::vector<std::tuple<double,double,double,double>> experiment::give_measurements_all(){
    //function to return a vectors of tuples of independent measurement, dependedent measurements with their associated errors
    //which is sorted in order of independent variables
    std::vector<std::tuple<double,double,double,double>> vec1;
    for(int i=0; i<dep_measurements.size(); i++){
        vec1.push_back(std::make_tuple(indep_measurements[i].return_measurement(),indep_measurements[i].return_uncertainty(),dep_measurements[i].return_measurement(),dep_measurements[i].return_uncertainty()));
    }
    std::sort(vec1.begin(), vec1.end());
    return vec1;
}
void write_to_file(experiment& e){
    //writes data to file in order of the independent variables
    std::string name{ "experiment_" + std::to_string(e.experimentcount) + ".txt"};
    std::ofstream MyFile(name);
    MyFile <<"Data from experiment "<< e.experimentcount<<std::endl;
    std::cout.precision(3);
    int size = e.dep_measurements.size();
    std::vector<std::tuple<double,double,double,double>> vec1 = e.give_measurements_all();
    MyFile <<"Independent variable:"<<e.indep_measurements[0].return_name()<<"      "<<"Dependent Variable:"<<e.dep_measurements[0].return_name()<<std::endl;
    MyFile<<"Date "<<std::endl;
    time_t now = time(0);
    // convert now to string form
    char* dt = ctime(&now);
    MyFile<<dt<<std::endl;
    MyFile<<"Measurement "<<"Error "<<"Systematic Error "<<" Measurement "<<"Error"<<std::endl;
    for(int i =0; i<size; i++ ){
        MyFile<<"("<<std::get<0>(vec1[i])<<"+/-"<<std::get<1>(vec1[i])<<"+/-"<<e.indep_measurements[i].return_sys_err()<<")"<<e.indep_measurements[i].return_units();
        MyFile<<"("<<std::get<2>(vec1[i])<<"+/-"<<std::get<3>(vec1[i])<<")"<<e.dep_measurements[i].return_units();
        MyFile<<std::endl;}
    MyFile.close();
}
   