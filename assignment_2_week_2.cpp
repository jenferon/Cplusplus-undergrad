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
#include<vector>
#include<sstream>
#include <bits/stdc++.h>

//Function to calculate mean 
double mean_function(std::vector<double> array_entries){
    double sum = 0;
    for (int i{};i<array_entries.size();i++){
        sum += array_entries[i];
    }
    return (1/(double) array_entries.size())*sum;
}

//Function to calculate standard deviation
double stan_dev(std::vector<double> array_entries, double mean){
    double sum = 0;
    for (int i{}; i <array_entries.size(); i++){
      sum += pow(array_entries[i] - mean,2);
    }
    return sqrt((1/(double) (array_entries.size()-1))*sum);
}

//Function to calcultae standard error
double standard_error(std::vector<double> array_entries, double std){
    return std/(sqrt((double) array_entries.size()));
}

//function to sort strings alphabetically
bool mycomp(std::string a, std::string b){
	return a.substr(11,30)<b.substr(11,30);
}

std::vector<std::string> alphabatically_sort(std::vector<std::string> a){
	int n=a.size();
	sort(a.begin(),a.end(),mycomp);
	return a;
}
//main code
int main(){
// Ask user to enter filename
  std::cout<<"Enter data filename: ";
  char data_file[100];
  std::cin>>data_file;
  while(std::cin.fail()){
                std::cout<<"Invalid input, please enter another value"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> data_file;
            }
//read in data file
std::vector<double> course_code(79);
std::vector<double> grade(79);
std::vector<std::string> course_name(79);
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

//call functions to calculate mean and standard deviation of course marks
double mean = mean_function(grade);
double standard_deviation = stan_dev(grade, mean);
double error = standard_error(grade, standard_deviation);

//print values
std::cout << "Number of courses = " << grade.size() << std::endl;
std::cout << "The average of the coursework marks is " << mean << std::endl;
std::cout << "The error on this measurement is " << error << std::endl;
std::cout << "The standard deviation on the coursework marks is " << standard_deviation << std::endl;

//print course list using an iterator
std::cout<<"Full course list:"<<std::endl;
int index_1{0};
std::vector<std::string> course_code_and_name;
for (std::vector<std::string>::iterator it_1 = course_name.begin(); it_1 != course_name.end(); ++it_1, index_1++){
  std::stringstream ss;
  ss << "PHYS";
  ss << course_code[index_1];
  ss << *it_1;
  std::cout << ss.str() << std::endl;
  course_code_and_name.push_back(ss.str());
}
std::cout <<"Do you want to sort the courses alphabetically? (enter y for yes or n for n)"<<std::endl;
std::string answer;
std::cin >> answer;
while(answer != "y" && answer != "n"){
  std::cout<<"User input is invalid"<<std::endl;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin >> answer;
}
if(answer == "y"){//sort names alphabetically
  std::vector<std::string> alphabetically_sorted = alphabatically_sort(course_code_and_name);
  for (std::vector<std::string>::iterator j = alphabetically_sorted.begin(); j != alphabetically_sorted.end(); ++j){
  
    std::cout << *j << std::endl;
  }
}
std::vector<double> grades_first_year;
std::vector<std::string> courses_first_year;
std::vector<double> grades_second_year;
std::vector<std::string> courses_second_year;
std::vector<double> grades_third_year;
std::vector<std::string> courses_third_year;
std::vector<double> grades_fourth_year;
std::vector<std::string> courses_fourth_year;

for(int index_2{0}; index_2 < course_code_and_name.size(); index_2++){
  char first_digit = (course_code_and_name[index_2]).at(4);
  if(first_digit == '1'){
    grades_first_year.push_back(grade[index_2]);
    courses_first_year.push_back(course_code_and_name[index_2]);
  }
  if(first_digit == '2'){
    grades_second_year.push_back(grade[index_2]);
    courses_second_year.push_back(course_code_and_name[index_2]);
  }
  if(first_digit == '3'){
    grades_third_year.push_back(grade[index_2]);
    courses_third_year.push_back(course_code_and_name[index_2]);
  }
  if(first_digit == '4'){
    grades_fourth_year.push_back(grade[index_2]);
    courses_fourth_year.push_back(course_code_and_name[index_2]);
  }
}
//enter course year and print the courses, mean and standard deviations for that year
bool repeat{true};
while(repeat == true){
  std::string year_of_interest;
  std::cout<<"Enter the year you would like to look at (please enter 1, 2, 3 or 4 for the corrosponding years):"<<std::endl;
  std::cin >> year_of_interest;
  while(year_of_interest != "1" && year_of_interest != "2" && year_of_interest != "3" && year_of_interest != "4"){
    std::cout<<"User input is invalid"<<std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> year_of_interest;
  
  }
  if(year_of_interest == "1"){
    std::cout<<"The first year courses are: "<<std::endl;
    for(std::vector<std::string>::iterator it_3 = courses_first_year.begin(); it_3 != courses_first_year.end(); ++it_3){
      std::cout<< *it_3 << std::endl;
    }
    double mean_first_year = mean_function(grades_first_year);
    double standard_deviation_first_year = stan_dev(grades_first_year, mean_first_year);
    double error_first_year = standard_error(grades_first_year, standard_deviation_first_year);
    std::cout<<"The mean of the first year grades is: "<< mean_first_year;
    std::cout<<" with an error of " << error_first_year<< std::endl;
    std::cout<<"The standard deviation is: " << standard_deviation_first_year << std::endl;
  }
  if(year_of_interest == "2"){
    std::cout<<"The second year courses are: "<<std::endl;
    for(std::vector<std::string>::iterator it_4 = courses_second_year.begin(); it_4 != courses_second_year.end(); ++it_4){
      std::cout<< *it_4 << std::endl;
  }
    double mean_second_year = mean_function(grades_second_year);
    double standard_deviation_second_year = stan_dev(grades_second_year, mean_second_year);
    double error_second_year = standard_error(grades_second_year, standard_deviation_second_year);
    std::cout<<"The mean of the second year grades is: "<< mean_second_year;
    std::cout<<" with an error of " << error_second_year<< std::endl;
    std::cout<<"The standard deviation is: " << standard_deviation_second_year << std::endl;
}
  if(year_of_interest == "3"){
    std::cout<<"The third year courses are: "<<std::endl;
    for(std::vector<std::string>::iterator it_5 = courses_third_year.begin(); it_5 != courses_third_year.end(); ++it_5){
      std::cout<< *it_5 << std::endl;
  }
    double mean_third_year = mean_function(grades_third_year);
    double standard_deviation_third_year = stan_dev(grades_third_year, mean_third_year);
    double error_third_year = standard_error(grades_third_year, standard_deviation_third_year);
    std::cout<<"The mean of the third year grades is: "<< mean_third_year;
    std::cout<<" with an error of " << error_third_year<< std::endl;
    std::cout<<"The standard deviation is: " << standard_deviation_third_year << std::endl;
}
  if(year_of_interest == "4"){
    std::cout<<"The fourth year courses are: "<<std::endl;
    for(std::vector<std::string>::iterator it_6 = courses_fourth_year.begin(); it_6 != courses_fourth_year.end(); ++it_6){
      std::cout<< *it_6 << std::endl;
  }
    double mean_fourth_year = mean_function(grades_fourth_year);
    double standard_deviation_fourth_year = stan_dev(grades_fourth_year, mean_fourth_year);
    double error_fourth_year = standard_error(grades_fourth_year, standard_deviation_fourth_year);
    std::cout<<"The mean of the fourth year grades is: "<< mean_fourth_year;
    std::cout<<" with an error of " << error_fourth_year<< std::endl;
    std::cout<<"The standard deviation is: " << standard_deviation_fourth_year << std::endl;
  }
  std::cout<<"Do you want the data for another year? Please input y for yes and n for no"<<std::endl;
  char answer;
  std::cin>>answer;
  while(answer != 'y' && answer != 'n'){
    std::cout<<"User input is invalid"<<std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> answer;
    }
    if(answer == 'y'){
      repeat = true;
      std::cout<<"You chose to repeat"<<std::endl;
      }
    if(answer== 'n'){
      repeat = false;
      std::cout<<"You chose not to repeat"<<std::endl;
    }
}
return 0;
}