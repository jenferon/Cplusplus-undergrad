//Code of assignment 4
//Jen Feron, Last updated 9/03/2021
#include<iostream>
#include<cmath>
#include<math.h>

//define class
class complex_number{
private:
    double re{0};
    double im{0};
public:
// Default constructor
    complex_number() = default;
//Parameterised constructor
    complex_number(double x, double y): re{x}, im{y} {}
//Destructor
    ~complex_number(){}
//member functions
complex_number complex_conjugate() {return {re,im*-1};};
void set_re(const double re_in){re=re_in;};
void set_im(const double im_in){im=im_in;};
double get_real() const {return re;};
double get_imaginary() const {return im;};
double modulus(){return sqrt(pow(re,2)+pow(im,2));};
double argument(){return tan(im/re);};
//friend functions
friend std::ostream& operator<<(std::ostream& os,const complex_number& c1);
friend std::istream& operator>>(std::istream& is, complex_number& c1);
//define functions
complex_number operator+(const complex_number &c1){
    return {re+c1.get_real(),im+c1.get_imaginary()};
}
complex_number operator-(const complex_number &c1){
    return {re-c1.get_real(),im-c1.get_imaginary()};
}
complex_number operator*(const complex_number &c1){
    return {re*c1.get_real()-im*c1.get_imaginary(),im*c1.get_real()+re*c1.get_imaginary()};
}
complex_number operator/(complex_number &c1){
    complex_number c2 = c1.complex_conjugate();
    double x = 1/((c1.get_real()*c2.get_real())-(c1.get_imaginary()*c2.get_imaginary()));
    double real = x*(re*c2.get_real()-im*c2.get_imaginary());
    double imaginary =x*(re*c2.get_imaginary()+im*c2.get_real());
    return {real,imaginary};
}
};
//define friend functions
std::ostream& operator<<(std::ostream& os,const complex_number& c1){
    if(c1.get_imaginary()>=0){
        os << c1.get_real() << "+" << c1.get_imaginary() << "i";
    }
    if(c1.get_imaginary() < 0){
        os << c1.get_real() << "-" << c1.get_imaginary()*-1 << "i";
    }
    return os;
}
std::istream& operator>>(std::istream& is, complex_number& c1){
    double real_in = 0;
    double im_in =0;
    char sign;
    char i;
    is>>real_in>>sign>>im_in>>i;   
    c1.set_re(real_in);
    if(i == 'i'){
        if(sign == '-'){
            c1.set_im(im_in*-1);
        }
        if(sign == '+'){
            c1.set_im(im_in);
        }
    }
    else{
        std::cout<<"User input is not valid"<<std::endl;
        exit(0);
    }
    return is;
}
int main()
{  
std::cout.precision(3);
// Create two complex numbers
complex_number a{3,4};
complex_number b{1,-2};
// Get real and imaginary components, modulus and argument
std::cout << "The real component of a is: "<<a.get_real()<<std::endl;
std::cout<< "The imaginary component of a is: "<< a.get_imaginary()<<std::endl;
std::cout<<"The modulus of a is: "<<a.modulus()<<std::endl;
std::cout<<"The argument of a is: "<< a.argument()<<" radians"<<std::endl;
std::cout << "The real component of b is: "<<b.get_real()<<std::endl;
std::cout<< "The imaginary component of b is: "<< b.get_imaginary()<<std::endl;
std::cout<<"The modulus of b is: "<<b.modulus()<<std::endl;
std::cout<<"The argument of b is: "<< b.argument()<<" radians"<<std::endl;
// Get conjugates
//complex_number a_conjugate = a.complex_conjugate();
std::cout<<"The complex conjugate of a is: "<<a.complex_conjugate()<<std::endl;
std::cout<<"The complex conjugate of b is: "<<b.complex_conjugate()<<std::endl;
// Get sum, difference, product and quotient of a and b
complex_number a_plus_b = a+b;
std::cout<<"a + b = "<< a_plus_b <<std::endl;
complex_number a_minus_b = a-b;
std::cout<<"a - b = "<< a_minus_b<<std::endl;
complex_number a_times_b = a*b;
std::cout<<"a * b = "<<a_times_b<<std::endl;
complex_number a_divided_by_b = a/b;
std::cout<<"a / b = "<<a_divided_by_b<<std::endl;
//show use of redefined >> function
std::cout << "Enter a complex number: "<<std::endl;
complex_number c{};
std::cin >> c;
std::cout << "You entered: " << c << std::endl;
return 0;
}