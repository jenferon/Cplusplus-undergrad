//Project:Data Storage system - main file
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

// define static variable of experiment class
int experiment::experimentcount{};
//functions used for data anaylsis using templates
//Function to calculate mean
template <class c_type> c_type mean_function(std::vector<c_type> array_entries){
    c_type sum = 0;
    for (int i{};i<array_entries.size();i++){
        sum += array_entries[i];}
return (1/(c_type) array_entries.size())*sum;}
//Function to calculate standard deviation
template <class c_type> c_type stan_dev(std::vector<c_type> array_entries, c_type mean){
    c_type sum = 0;
    for (int i{}; i <array_entries.size(); i++){
        sum += pow(array_entries[i] - mean,2);}
    return sqrt((1/(double) (array_entries.size()-1))*sum);}
//Function to calcultae standard error
template <class c_type> c_type standard_error(std::vector<c_type> array_entries, c_type std){
    return std/(sqrt((c_type) array_entries.size()));}
//find range of vector which also demonstrates use of a lambda function
template <class c_type> c_type find_range(std::vector<c_type> vec){
    c_type min_value = *min_element(vec.begin(),vec.end());
    c_type max_value = *max_element(vec.begin(),vec.end());
    auto range = [](c_type x, c_type y){return x - y;};
    return range(max_value,min_value);
}
double red_chi_squared(std::vector<double> y, std::vector<double> fx, std::vector<double> sigma){
    double chi_square = 0;
    int size = y.size();
    try{
        for(int i =1; i<size; i++ ){
            chi_square = chi_square + pow((y[i] - fx[i]),2)/pow(sigma[i],2);
    }
    }
    catch(int errorFlag){
        //error statement to catch wrong inputs
        std::cerr<<"Calculation error"<<std::endl;
        return 1;
    }
    return chi_square/size;
}
int main(){
//create booleon to allow for multiple experiments to be inputted
bool add_exp = true;
//create a container to store multiple experiments
std::vector<experiment> exp_vec;
while(add_exp == true){
//input data from file
//File lines must be in the order of independent measurement, independent measurement error, dependent measurement, dependent measurement error
std::cout<<"Enter data filename: ";//files for sum and power relations are given in the correct format
char data_file[100];
try{
std::cin>>data_file;
}
catch(int error_flag){
    if (std::cin.fail()){
        //error statement to catch wrong inputs
        std::cerr<<"File could not be found"<<std::endl;
        return 1; 
    }
}
//read in data file
std::cout<<"How many lines does the data file have?"<<std::endl; //both files given have 16 lines
int lines;
std::cin>>lines;
std::cout<<"What is the absolute systematic error of the independent variable?"<<std::endl;
double sys_err;
std::cin>>sys_err;
std::vector<double> indep_measure_err(lines);
std::vector<double> indep_measure(lines);
std::vector<double> dep_measure(lines);
std::vector<double> dep_measure_err(lines);
std::ifstream my_file{data_file};
if(! my_file.good ()) {
    //error statement to catch wrong inputs
    std::cerr<<"Error: file could not be opened"<<std::endl;
    return(1);
}
int index{0};
while(!my_file.eof()){
    my_file >> indep_measure[index]>>indep_measure_err[index]>>dep_measure[index]>>dep_measure_err[index];
    index++;  
}
my_file.close();
std::cout<<"is the relationship a power dependence or a sum? (Enter p for power dependence and s for sum)"<<std::endl;
char answer;
std::cin>>answer;
if(answer != 'p' || answer != 's'){
    //error statement to catch wrong inputs
    std::cerr<<"Answer not valid"<<std::endl;
    return(1);
}
if(answer == 'p'){
    //intialise experiment class with empty deque containers
    std::deque <class dep_measure_actual> dep_measurements_in;
    std::deque <class indep_measurement> indep_measurements_in;
    std::deque <class sum_ns::dep_measure_predicted> sum_predict_in;
    std::deque <class pow_ns::dep_measure_predicted> power_predict_in;
    std::string pow = "p";
    experiment exp1(dep_measurements_in,indep_measurements_in,sum_predict_in,power_predict_in, pow);
    //input into class showing overidden istream opperator
    function_power f;
    std::cin>> f;
    std::unique_ptr<function_power> f_ptr(new function_power(f));
    std::cout<<"Enter the name of the independent variable:"<<std::endl;
    std::string name_id;
    std::cin>>name_id;
    std::cout<<"Enter the name of the dependent variable:"<<std::endl;
    std::string name_d;
    std::cin>>name_d;
    std::cout<<"Enter the units of the dependent variable:"<<std::endl;
    std::string units_d;
    std::cin>> units_d;
    std::cout<<"Enter the units of the independent variable:"<<std::endl;
    std::string units_id;
    std::cin>> units_id;
    for(int i=0; i<lines; i++ ){
        //for lines in data file add data to classes
        indep_measurement y(name_id, indep_measure[i], indep_measure_err[i],sys_err, units_id);
        std::unique_ptr<indep_measurement> y_ptr(new indep_measurement(name_id, indep_measure[i], indep_measure_err[i],sys_err, units_id));
        std::unique_ptr<dep_measure_actual> x_1_ptr(new dep_measure_actual(name_d, units_d, dep_measure[i], dep_measure_err[i]));
        std::unique_ptr<pow_ns::dep_measure_predicted> x_2_ptr(new pow_ns::dep_measure_predicted(name_d, units_d, y_ptr, f_ptr));
        exp1.add_expt_end_pow(x_1_ptr,y_ptr,x_2_ptr);
    }
    //demonstrate user input to write data to experiment class
    bool add_measurement(true); //use booleon to allow for multiple measurements to be added
    while (add_measurement == true){
        std::cout<<"Would you like to enter another measurement (enter y for yes and n for no)?"<<std::endl;
        std::string answer;
        std::cin>>answer;
        if (answer == "y"){
            //allow user to decide if the new measurements are to be added at the start or end of the container
            std::cout<<"Would you like to add the measurement at the end or start (enter e for end and s for start)?"<<std::endl;
            std::string answer2;
            std::cin>>answer2;
            if(answer2 == "e"){
                //measurements added at end of container while demonstrating use of istream overload
                indep_measurement y;
                std::cin>>y;
                indep_measure.push_back(y.return_measurement());
                std::unique_ptr<indep_measurement>y1_ptr(new indep_measurement(y));
                dep_measure_actual x;
                std::cin>>x;
                dep_measure.push_back(x.return_measurement());
                std::unique_ptr<dep_measure_actual>x1_ptr1(new dep_measure_actual(x));
                std::unique_ptr<pow_ns::dep_measure_predicted> x_2_ptr(new pow_ns::dep_measure_predicted(name_d, units_d, y1_ptr, f_ptr));
                exp1.add_expt_end_pow(x1_ptr1,y1_ptr,x_2_ptr);
                continue;
            }
            if(answer2 == "s"){
                //measurements added at start of container while demonstrating use of istream overload
                indep_measurement y;
                std::cin>>y;
                indep_measure.push_back(y.return_measurement());
                std::unique_ptr<indep_measurement>y1_ptr(new indep_measurement(y));
                dep_measure_actual x;
                std::cin>>x;
                dep_measure.push_back(x.return_measurement());
                std::unique_ptr<dep_measure_actual>x1_ptr1(new dep_measure_actual(x));
                std::unique_ptr<pow_ns::dep_measure_predicted> x_2_ptr(new pow_ns::dep_measure_predicted(name_d, units_d, y1_ptr, f_ptr));
                exp1.add_expt_start_pow(x1_ptr1,y1_ptr,x_2_ptr);
                continue;
            }
            else{
                //error statement to catch wrong inputs
                std::cerr<<"Answer not valid"<<std::endl;
                return(1);
        }
        }
        if(answer == "n"){
            //no more measurements to be added
            exp1.print_info(); //print experimental information to screen
            std::vector<double> fx; //vector to store predicted dependent measurement
            for(int i = 0; i<indep_measure.size();i++){
                fx.push_back(f.apply_func(indep_measure[i]));
            }
            double chisquared = red_chi_squared(dep_measure,fx,dep_measure_err);//calculate reduced chi squared
            //print information showing use of template functions
            std::cout<<"The reduced chi squared value for this experiment is:";
            std::cout<< chisquared<<std::endl;
            std::cout<<"The range of the independent variables is: "<<find_range<double>(indep_measure)<<std::endl;
            double mean = mean_function<double>(indep_measure); 
            std::cout<<"The mean of the indpendent variables is:"<<mean<<std::endl;
            double s_dev = stan_dev<double>(indep_measure,mean);
            std::cout<<"This has a standard deviation of: "<<s_dev<<std::endl;
            double std_err = standard_error<double>(indep_measure, s_dev);
            std::cout<<"And a standard error of: "<<std_err<<std::endl;
            write_to_file(exp1); //write experimental data to file
            add_measurement = false; //ensure no more measurements are added
            exp_vec.push_back(exp1); // add experiment to container of experiments
        }
        else{
            //error statement to catch wrong inputs
            std::cerr<<"Answer not valid"<<std::endl;
            return(1);
        }
    }
}
if(answer == 's'){
    std::cout<<"Sum relation"<<std::endl;
    //intialise experiment class with empty deque containers
    std::deque <class dep_measure_actual> dep_measurements_in;
    std::deque <class indep_measurement> indep_measurements_in;
    std::deque <class sum_ns::dep_measure_predicted> sum_predict_in;
    std::deque <class pow_ns::dep_measure_predicted> power_predict_in;
    std::string sum = "s";
    experiment exp1(dep_measurements_in,indep_measurements_in,sum_predict_in,power_predict_in, sum);
    //input into class using overridden istream containers
    function_sum f2;
    std::cin>> f2;
    std::unique_ptr<function_sum> f2_ptr(new function_sum(f2));
    std::cout<<"Enter the name of the independent variable:"<<std::endl;
    std::string name_id;
    std::cin>>name_id;
    std::cout<<"Enter the name of the dependent variable:"<<std::endl;
    std::string name_d;
    std::cin>>name_d;
    std::cout<<"Enter the units of the dependent variable:"<<std::endl;
    std::string units_d;
    std::cin>> units_d;
    std::cout<<"Enter the units of the independent variable:"<<std::endl;
    std::string units_id;
    std::cin>> units_id;
    for(int i=0; i<lines; i++ ){
        //for lines in data file add data to classes
        std::unique_ptr<indep_measurement> y_ptr(new indep_measurement(name_id, indep_measure[i], indep_measure_err[i],sys_err, units_id));
        std::unique_ptr<dep_measure_actual> x_1_ptr(new dep_measure_actual(name_d, units_d, dep_measure[i], dep_measure_err[i]));
        std::unique_ptr<sum_ns::dep_measure_predicted> x_2_ptr(new sum_ns::dep_measure_predicted(name_d, units_d, y_ptr, f2_ptr));
        exp1.add_expt_end_sum(x_1_ptr,y_ptr,x_2_ptr);
    }
    //demonstrate user input to write data to experiment class
    bool add_measurement = true; //use booleon to allow for multiple measurements to be added
    while (add_measurement == true){
        std::cout<<"Would you like to enter another measurement (enter y for yes and n for no)?"<<std::endl;
        std::string answer;
        std::cin>>answer;
        if (answer == "y"){
            //allow for addidition of measurement at start and end of containert
            std::cout<<"Would you like to add the measurement at the end or start (enter e for end and s for start)?"<<std::endl;
            std::string answer2;
            std::cin>>answer2;
            if(answer2 == "e"){
                //measurements added at end of container while demonstrating use of istream overload
                indep_measurement y;
                std::cin>>y; 
                indep_measure.push_back(y.return_measurement());
                std::unique_ptr<indep_measurement>y1_ptr(new indep_measurement(y));
                dep_measure_actual x;
                std::cin>>x;
                dep_measure.push_back(x.return_measurement());
                std::unique_ptr<dep_measure_actual>x1_ptr1(new dep_measure_actual(x));
                std::unique_ptr<sum_ns::dep_measure_predicted> x_2_ptr(new sum_ns::dep_measure_predicted(name_d, units_d, y1_ptr, f2_ptr));
                exp1.add_expt_end_sum(x1_ptr1,y1_ptr,x_2_ptr);
                continue;
            }
            if(answer2 == "s"){
                //measurements added at start of container while demonstrating use of istream overload
                indep_measurement y;
                std::cin>>y;
                indep_measure.push_back(y.return_measurement());
                std::unique_ptr<indep_measurement>y1_ptr(new indep_measurement(y));
                dep_measure_actual x;
                std::cin>>x;
                dep_measure.push_back(x.return_measurement());
                std::unique_ptr<dep_measure_actual>x1_ptr1(new dep_measure_actual(x));
                std::unique_ptr<sum_ns::dep_measure_predicted> x_2_ptr(new sum_ns::dep_measure_predicted(name_d, units_d, y1_ptr, f2_ptr));
                exp1.add_expt_start_sum(x1_ptr1,y1_ptr,x_2_ptr);
                continue;
            }
            else{
                //error statement to catch wrong inputs
                std::cerr<<"Answer not valid"<<std::endl;
                return(1);
        }
        }
        if(answer == "n"){
            //no more measurements to be added
            exp1.print_info(); //print experimental information to screen
            std::vector<double> fx; //vector to store predicted dependent measurement
            std::vector<std::pair<double,double>> iv = exp1.give_measurements_iv(); //pair function
            for(int i = 0; i<indep_measure.size();i++){
                fx.push_back(f2.apply_func(iv[i].first));
            }
            double chisquared = red_chi_squared(dep_measure,fx,dep_measure_err);//calculate reduced chi squared
            //print information showing use of template functions
            std::cout<<"The reduced chi squared value for this experiment is:";
            std::cout<< chisquared<<std::endl;
            std::cout<<"The range of the independent variables is: "<<find_range<double>(indep_measure)<<std::endl;
            double mean = mean_function<double>(indep_measure);
            std::cout<<"The mean of the indpendent variables is:"<<mean<<std::endl;
            double s_dev = stan_dev<double>(indep_measure,mean);
            std::cout<<"This has a standard deviation of: "<<s_dev<<std::endl;
            double std_err = standard_error<double>(indep_measure, s_dev);
            std::cout<<"And a standard error of: "<<std_err<<std::endl;
            write_to_file(exp1); //write experimental data to file 
            add_measurement = false; //ensure no more measurements are added
            exp_vec.push_back(exp1); // add experiment to container of experiments
        }
        else{
            //error statement to catch wrong inputs
            std::cerr<<"Answer not valid"<<std::endl;
            return(1);
        }
    }
}
//another experiment?
std::cout<<"Would you like to enter another experiment (enter y for yes and n for no)?"<<std::endl;
std::string answer2;
std::cin>>answer2;
if (answer2 == "y"){
    continue;
    }
if(answer2 == "n"){
    add_exp = false;
}
else{
    //error statement to catch wrong inputs
    std::cerr<<"Answer not valid"<<std::endl;
    return(1);
}
}
return 0;
}
//add more to the main function to show all the functions created ie add somewhere that shpws the pair thing 
