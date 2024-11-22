//Assignment 3 code
//Class for galaxy classification
#include<iostream>
#include<string>
#include<cmath>
#include<vector>

class galaxy{
private:
    std::string type {"E0"};
    double redshift {0.0};
    double total_mass {1e7};
    double stella_mass_fraction {0.0};
    std::vector<galaxy> satellites {};
public:
// Default constructor
    galaxy() = default;
//Parameterised constructor
    galaxy(std::string galaxy_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stella_mass_fraction):
        type{galaxy_type}, redshift{galaxy_redshift}, total_mass{galaxy_total_mass}, stella_mass_fraction{galaxy_stella_mass_fraction}
    {}
//Destructor
    ~galaxy(){std::cout<<"Destroying"<<type<<std::endl;};
//member functions
    double stella_mass() {return stella_mass_fraction*total_mass;};
    void change_type(std::string type_new);
    void print_data();
    void add_satellite(galaxy satellites_new);
};
//define print data function
void galaxy::print_data(){
    std::cout.precision(5);
    std::cout<<"Galaxy: [type,z,m(solar mass units),f*] = ["<<type<<","<<redshift<<","<<total_mass<<","<<stella_mass_fraction<< "]"<<std::endl;
    std::cout<<"The number of satelites in this galaxy is: "<< satellites.size()<<std::endl;
    if(satellites.size() != 0){
        std::vector<galaxy>::iterator i;
        std::cout<<"The properties of this galaxy's satellites are:"<<std::endl;
        for(auto i=satellites.begin(); i<satellites.end();++i){
            std::cout.precision(5);
            std::cout<<"Satellite: [type,z,m(solar mass units),f*] = ["<<type<<","<<redshift<<","<<total_mass<<","<<stella_mass_fraction<< "]"<<std::endl;
    }
    }
    return;
}
//define change type function
void galaxy::change_type(std::string type_new){
    type = type_new;
}
//satellite galaxy
void galaxy::add_satellite(galaxy satellites_new){
    satellites.push_back(satellites_new);    
}

int main()
{
    //create galaxys
    const double solar_mass = 1.98847*pow(10,30);
    std::vector<galaxy> galaxy_data;
    galaxy_data.push_back(galaxy("E0",4,1e9,0.05));
    galaxy_data.push_back(galaxy("E7",8,1e12,0.03));
    //define satellite vector
    galaxy satellites_1("S0",2,1e10,0.01);
    galaxy_data.at(0).add_satellite(satellites_1);
    galaxy satellites_2("SBa",3,1e11,0.012);
    galaxy_data.at(0).add_satellite(satellites_2);
    //print data using an iterator 
    std::vector<galaxy>::iterator galaxy_it;
    for(auto galaxy_it=galaxy_data.begin(); galaxy_it<galaxy_data.end();++galaxy_it){
        galaxy_it -> print_data();
        std::cout<<"Stella Mass (in solar mass units) = "<<galaxy_it->stella_mass()<<std::endl;   
    }
    galaxy_data.at(1).change_type("SBc");
    std::cout<<"Data for new galaxay type ";
    galaxy_data.at(1).print_data();
    return 0;
}