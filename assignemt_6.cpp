//code for assignment 6; using inheritance
//Jen Feron
#include<iostream>
#include<cmath>

class shapes{
    public:
    virtual void info()=0;
    virtual ~shapes(){std::cout<<"Base class destructor called"<<std::endl;};
};
class two_d: public shapes{
    public:
    virtual double area()=0;
    virtual ~two_d(){std::cout<<"2D destructor called"<<std::endl;}
};
class three_d: public shapes{
    public:
    virtual double volume()=0;
    virtual ~three_d(){std::cout<<"3D destructor called"<<std::endl;}
};
class rectangle: public two_d{
    protected:
    double lenght{0};
    double width{0};
    int dimensions{2};
    std::string name{"Rectangle"};
    public:
    rectangle(double l, double w, std::string name): lenght{l}, width{w}, name{name}, dimensions{2} {};
    ~rectangle() {std::cout<<name<<" destructor called"<<std::endl;}
    void info(){std::cout<<name<<": lenght= "<<lenght<<"m"<<" width= "<<width<<"m"<<" area = "<<area()<<"m^2"<<std::endl;}
    double area(){return lenght*width;}
};
class square: public rectangle{
    public:
    square(double l): rectangle(l,l,"Square") {};
    ~square() {std::cout<<"Square destructor called"<<std::endl;}
};
class ellipse: public two_d{
    protected:
    double major_axis{0};
    double minor_axis{0};
    int dimensions {2};
    std::string name{"Ellipse"};
    public:
    ellipse(double a, double b, std::string name): major_axis{a}, minor_axis{b}, name{name}, dimensions{2} {};
    ~ellipse() {std::cout<<name<<" destructor called"<<std::endl;}
    void info(){std::cout<<name<<": semi-major axis= "<<major_axis<<"m"<<" semi_minor axis= "<<minor_axis<<"m"<<" area = "<<area()<<"m^2"<<std::endl;}
    double area(){return M_PI*major_axis*minor_axis;}
};
class circle:public ellipse{
    public:
    circle(double r): ellipse(r,r,"Circle") {};
    ~circle() {std::cout<<"Circle destructor called"<<std::endl;}
};
class cuboid: public three_d{
    protected:
    double lenght{0};
    double width{0};
    double height{0};
    int dimensions {3};
    std::string name{"Cuboid"};
    public:
    cuboid(double l,double w, double h, std::string name): lenght{l}, width{w}, height{h}, name{name}, dimensions{3} {};
    ~cuboid() {std::cout<<name<<" destructor called"<<std::endl;}
    void info(){std::cout<<name<<": lenght= "<<lenght<<"m"<<" width= "<<width<<"m"<<" height= "<<height<<"m"<<" volume= "<<volume()<<"m^3"<<std::endl;}
    double volume(){return lenght*width*height;}
};
class cube: public cuboid{
    public:
    cube(double l): cuboid{l,l,l,"Cube"} {};
    ~cube() {std::cout<<"Cube destructor called"<<std::endl;}
};
class ellipsoid: public three_d{
    protected:
    double a{0};
    double b{0};
    double c{0};
    int dimensions{3};
    std::string name{"Ellipsoid"};
    public:
    ellipsoid(double A, double B, double C, std::string name): a{A}, b{B}, c{C}, name{name}, dimensions{3} {};
    ~ellipsoid() {std::cout<<name<<" destructor called"<<std::endl;}
    void info(){std::cout<<name<<": a= "<<a<<"m"<<" b= "<<b<<"m"<<" c= "<<c<<"m"<<" volume= "<<volume()<<"m^3"<<std::endl;}
    double volume(){return ((double) 4.0/3.0)*M_PI*a*b*c;}
};
class sphere: public ellipsoid{
    public:
    sphere(double r): ellipsoid(r,r,r,"Sphere") {};
    ~sphere() {std::cout<<"Sphere destructor called"<<std::endl;}
};
class prism: public three_d{
    private:
    double depth;
    class two_d *base;
    public:
    prism(double d, two_d *base_shape): depth{d}, base{base_shape} {};
    void info(){
        std::cout<<"Prism: depth= "<<depth<<"m"<<" volume= "<<volume()<<"m^3"<<std::endl;
        std::cout<<"The base of the prism is: "<<std::endl;
        base->info();
    }
    double volume(){return depth*(base->area());}
};
int main(){
    //use pointers to print info
    std::cout.precision(3);
    //in 2D
    two_d *two_d_pointer[4];
    two_d_pointer[0]=new rectangle(2,3,"Rectangle");
    two_d_pointer[0]->info();
    two_d_pointer[1]= new square(4);
    two_d_pointer[1]->info();
    two_d_pointer[2]= new ellipse(2,3,"Ellipse");
    two_d_pointer[2]->info();
    two_d_pointer[3]= new circle(3);
    two_d_pointer[3]->info();
    //in 3D
    three_d *three_d_pointer[5];
    three_d_pointer[0]= new cuboid(2,3,5,"Cuboid");
    three_d_pointer[0]->info();
    three_d_pointer[1]= new cube(3);
    three_d_pointer[1]->info();
    three_d_pointer[2]= new ellipsoid(2,1,3,"Ellipsoid");
    three_d_pointer[2]->info();
    three_d_pointer[3]= new sphere(4);
    three_d_pointer[3]->info();
    three_d_pointer[4] = new prism(4, two_d_pointer[2]);
    three_d_pointer[4]->info();
    //delete pointers
    for(int i{0};i<3;i++){
        delete three_d_pointer[i];
        //three_d_pointer[i] =0;
        delete two_d_pointer[i];
        two_d_pointer[i]=0;
    }
    return 0;
}
