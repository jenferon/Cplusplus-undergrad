//Assignment_1
//Jenifer Feron, Last updated:12/02/2021
//Code to calculate the energy changes between energy levels of
//the Bohr atom model
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include <limits>
//create function to calculate the energy of the Bohr model in eV
double energy_calculation(double n_1, double n_2,double z){
    return 13.6*(pow(z,2)*(pow(1/n_2,2)-pow(1/n_1,2)));
}
//create function to return correct error message if input is invalid
int main()
{   bool repeat{true};
    while (repeat == true){
        //Ask user to input the intial and final energy levels and atomic number, 
        //ensuring integers are inputted
        std::cout << "Enter the inital energy level (as an integer)"<<std::endl;
        double intial_energy_level ;
        std::cin >> intial_energy_level;
        while(std::cin.fail() || intial_energy_level < 0 || intial_energy_level != floor(intial_energy_level)){
            if(std::cin.fail()){
                std::cout<<"Invalid input, please enter another value"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> intial_energy_level;
            }
            if(intial_energy_level != floor(intial_energy_level)){
                std::cout<<"Input must be an integer"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> intial_energy_level; 
            }
            if(intial_energy_level < 0){
                std::cout<<"The energy level must be a positive integer"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> intial_energy_level;
        }
        }
        std::cout << "Enter the final energy level (as an integer)"<<std::endl;
        double final_energy_level;
        std::cin >> final_energy_level;
        while(std::cin.fail() || final_energy_level < 0 || final_energy_level != floor(final_energy_level) || final_energy_level>intial_energy_level){
            if(std::cin.fail()){
                std::cout<<"Invalid input, please enter another value"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> final_energy_level;
            }
            if(final_energy_level<0){
                std::cout<<"Energy levels must be greater than zero"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> final_energy_level; 
            }
            if(final_energy_level>intial_energy_level){
                std::cout<<"The final energy level must be smaller than the intial energy level"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> final_energy_level;
            }  
            if(final_energy_level != floor(final_energy_level)){
                std::cout<<"Input must be an integer"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> final_energy_level; 
            }  
        }
        std::cout<< "Enter the atomic number (as an integer)"<<std::endl;
        double atomic_number;
        std::cin>>atomic_number;
        while(std::cin.fail() || atomic_number<0 || atomic_number != floor(atomic_number)){
            if(std::cin.fail()){
                std::cout<<"Invalid input, please enter another value"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> atomic_number;
            }if(atomic_number<0){
                std::cout<<"The energy level must be a positive integer"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> atomic_number;
            }
            if(atomic_number != floor(atomic_number)){
                std::cout<<"Input must be an integer"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> atomic_number; 
            }
        }
        //calculate the energy difference and output in either Joules and eV
        double energy;
        energy = energy_calculation(intial_energy_level,final_energy_level,atomic_number); //calculate enegry in eV
        const double ev_to_joules{1.602*(pow(10,-19))}; //define conversion factor from eV to Joules
        char energy_in_ev;
        std::cout<<"Please enter e to get the energy in eV, or J for Joules"<<std::endl;
        std::cin>> energy_in_ev;
        while(energy_in_ev != 'e' && energy_in_ev != 'J'){
                        std::cout<<"User input is invalid"<<std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin >> energy_in_ev;
        }
        if (energy_in_ev == 'e'){
            std::cout<<"The energy of the transition is ";
            std::cout << std::setprecision(3);
            std::cout << energy;
            std::cout << " eV" << std::endl; 
            std::cout<<"Do you want to do another calculation? Please input y for yes and n for no"<<std::endl;
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
                std::cout<<"You chose to repeat the calculation"<<std::endl;
                }
            if(answer== 'n'){
                repeat = false;
                std::cout<<"You chose not to repeat the calculation"<<std::endl;
            }
        }
        if(energy_in_ev == 'J'){
            std::cout<<"The energy of the transition is ";
            std::cout << std::setprecision(3);
            std::cout << energy*ev_to_joules;
            std::cout << " J" << std::endl; 
            std::cout<<"Do you want to do another calculation? Please input y for yes and n for no"<<std::endl;
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
                std::cout<<"You chose to repeat the calculation"<<std::endl;
                }
            if(answer== 'n'){
                repeat = false;
                std::cout<<"You chose not to repeat the calculation"<<std::endl;
                }             
        }
    }
    return 0;
}