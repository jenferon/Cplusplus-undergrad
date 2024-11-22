// PHYS 30762 Programming in C++
// Assignment 2

//Program to open and read data file and compute the mean
//standard deviation and standard error of the data

//Jen Feron last updated: 18/02/2021

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<limits>
#include<string>
#include<array>

//Function to calculate mean 
double mean_function(double *array_entries, const int lenght){
    double sum = 0;
    for (int i{};i<lenght;i++){
        sum += array_entries[i];
    }
    return (1/(double) lenght)*sum;
}

//Function to calculate standard deviation
double stan_dev(double *my_array, double mean, const int lenght){
    double sum = 0;
    for (int i{}; i <lenght; i++){
      sum += pow(my_array[i] - mean,2);
    }
    return sqrt((1/(double) (lenght-1))*sum);
}

//Function to calcultae standard error
double standard_error(double std, const int lenght){
    return std/(sqrt((double) lenght));
}

//main code
int main()
{
// Ask user to enter filename
  std::cout<<"Enter data filename: ";
  char data_file[100];
  std::cin>>data_file;
  if(std::cin.fail()){
                std::cout<<"Invalid input, please enter another value"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> data_file;
            }
//read in data file
int course_code[79];
double grade[79];
std::string course_name[79];
int count;
std::ifstream my_file{data_file};
if(! my_file.good ()) {
  std::cout<<"Error: file could not be opened"<<std::endl;
  return(1);
}
int index{0};
while(!my_file.eof()){
    my_file >> grade[index] >> course_code[index];
    getline(my_file, course_name[index]);
    index++;
    
}
my_file.close();

double* grade_pointer = grade;
//call functions to calculate mean and standard deviation of course marks
double mean = mean_function(grade_pointer, index);
std::cout << "The average of the coursework marks is " << mean << std::endl;

double standard_deviation = stan_dev(grade_pointer, mean, index);
std::cout << "The standard deviation on the coursework marks is " << standard_deviation << std::endl;

double error = standard_error(standard_deviation, index);
std::cout << "The error on this measurement is " << error << std::endl;

//print values
std::cout << "Number of courses = " << index << std::endl;

return 0;
}
