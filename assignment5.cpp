//Assignment 5 - C++ class for matricies
//Jen Feron
#include<iostream>
#include<math.h>

class matrix{
private:
    int rows{0};
    int columns{0};
    double *array{nullptr};
public:
    matrix() = default; //{std::cout<<"Default constructor called"<<std::endl;} //default constructor
    //paramatised constructor
    matrix(int n, int m){
        int size = (m-1)+((n-1)*m)+1;
        if(size<1){
            throw("Error: trying to delare an array with size <1");
        }
        rows = n;
        columns = m;
        array = new double[size];
        for(int i=0; i<rows; i++){ 
            for(int j=0;j<columns;j++){
                int x = (j+(i*columns));
                array[x]= 0;
    }
    }
    }
    void set_row(const int row_in){rows=row_in;};
    void set_column(const int column_in){columns=column_in;};
    void set_size(int row_in, int column_in){
        int size = (column_in-1)+((row_in-1)*column_in)+1;
        array = new double[size];
        for(int i=0; i<rows; i++){ 
            for(int j=0;j<columns;j++){
                int x = (j+(i*columns));
                array[x]= 0;
    }
    }
    }
    matrix(matrix&); //copy
    matrix(matrix&&); //move
    ~matrix(){delete array;} //destructor
    int row_number() {return rows;};
    int column_number() {return columns;};
    int get_size() {return (columns-1)+((rows-1)*columns)+1;};
    matrix& operator=(matrix&); //copy assignment
    matrix& operator=(matrix&&); //move assignment
    double & operator[](size_t i); //overload []
    friend std::ostream& operator<<(std::ostream& os,const matrix& m1);
    friend std::istream& operator>>(std::istream& is, matrix& m1);
    double determinant();
    double determinant_2x2();
    //matrix addition
    matrix operator+(matrix &m1){
        matrix m2(rows,columns);
        if(m1.row_number()==rows && m1.column_number()==columns){
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    int x = (j+(i*columns));
                    m2[x]=array[x]+m1[x]; 
                }
            }
        }
        else{
            throw("Error: Matrices must be of the same dimensions");
        }
        return m2;
    }
    matrix operator-(matrix &m1){
        matrix m2(rows,columns);
        if(m1.row_number()==rows && m1.column_number()==columns){
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    int x =j+(i*columns);
                   m2[x]=array[x]-m1[x]; 
                }
            }
        }
        else{
            throw("Error: Matrices must be of the same dimensions");
        }
        return m2;
    }
    matrix operator*(matrix &m1){
        matrix m2(rows,m1.columns);
        int x =0;
        double *sum;
        sum = new double [columns*m1.row_number()];
        if(m1.row_number()==columns){
            for(int i=0;i<rows;i++){
                for(int j=0;j<columns;j++){
                    for(int k=0;k<columns;k++){
                        int y = k+(i*columns);
                        int z = j+(k*m1.column_number());
                        sum[x] = sum[x] + array[y]*m1[z]; 
                    }
                m2[x] = sum[x];
                x++;
                }
            }
        }
        else{
            throw("Error: For AB the number of columns of A must equal the number of rows of B");
        }
        return m2;
    }
    matrix remove_row_and_column(int n, int m){
        matrix m2(rows-1,columns-1);
        int y =0;
        for(int i=0; i<rows; i++){
            if(i == (n-1)){
            continue;
            }   
            else{
            for(int j=0; j<columns; j++){
                if(j == (m-1)){
                continue;
                }
                else{
                int x = j+(i*columns);
                m2[y]= array[x];
                y++;
                }
            }
            }
        }
        return m2;
    }
};
double matrix::determinant_2x2(){
    if(rows == columns){
        if(rows ==1){
            return array[0];
        }
        if(rows == 2){
            return (array[0]*array[3]-array[2]*array[1]);
        }
    }
    else{
        throw("Error: Matrix must be square");
        }
    return 0;
}
double matrix::determinant(){
    if(rows == columns){
        double x =0;
        if(columns>3){
            for(int j=0;j<columns;j++){
            int element=j+(0*columns);
            matrix small_array = remove_row_and_column(1,j+1);
            double small_det = small_array.determinant();
            x=x+pow(-1,j+2)*array[element]*small_det;
            }
        }
        for(int j=0;j<columns;j++){
            int element=j+(0*columns);
            matrix small_array = remove_row_and_column(1,j+1);
            double small_det = small_array.determinant_2x2();
            x=x+pow(-1,j+2)*array[element]*small_det;
            }
            return x;
    }
    else{
        throw("Error: Matrix must be square");
    }
    return 0;
}
//overload [] function
double & matrix::operator[](size_t size){
    if(size<0 || size>=get_size()){
        throw("Error: trying to access array elements out of bounds");
    }
    return array[size];
}
//copy constructor
matrix::matrix(matrix &arr){
array=nullptr;
rows =arr.rows;
columns=arr.columns;
if(arr.get_size()>0){
    array=new double[arr.get_size()];
    for(int i=0;i<arr.get_size();i++){ 
        array[i]=arr[i];
        }
}
}
//copy assignment
matrix & matrix::operator=(matrix &arr){
    if(&arr == this){
        return *this;
    }
    delete[] array;
    array=nullptr;
    rows =arr.rows;
    columns=arr.columns;
    if(arr.get_size()>0){
        array=new double[arr.get_size()];
        for(int i=0;i<arr.get_size();i++){
            array[i] = arr[i];
        }
    }
    return *this;
}
//move constructor
matrix::matrix(matrix &&arr){
std::cout<<"move constructor\n";
int size = arr.get_size();
array=arr.array;

arr.array=nullptr;
}
//move assignment
matrix & matrix::operator=(matrix&& arr){
    std::cout<<"move assignment\n";
    std::swap(rows,arr.rows);
    std::swap(columns,arr.columns);
    std::swap(array,arr.array);
    return *this;
}
//friend functions to overload << and >>
std::ostream& operator<<(std::ostream& os,const matrix& m1){
    for(int i=0;i<m1.rows;i++){
        for(int j=0;j<m1.columns;j++){
            int x = (j+(i*m1.columns));
            os<<m1.array[x] << " ";
        }
        os<< std::endl;
    }
    return os;
}
std::istream& operator>>(std::istream& is, matrix& m1){
    int rows_in{0};
    int columns_in{0};
    std::cout<<"input the number of rows"<<std::endl;
    std::cin>> rows_in;
    m1.set_row(rows_in);
    std::cout<<"input number of columns"<<std::endl;
    std::cin>>columns_in;
    m1.set_column(columns_in);
    m1.set_size(rows_in,columns_in);
    std::cout<<"You must enter an array of size "<<m1.get_size()<<std::endl;
    for(int i=0;i<m1.rows;i++){
        for(int j=0;j<m1.columns;j++){
            std::cout<<"Enter matrix element "<<"A("<<i+1<<","<<j+1<<")"<<std::endl;
            double element;
            is>>element;
            int x = (j+(i*m1.columns));
            m1[x] = element;
        }
    }
    return is;
}
int main(){
double array_1[9] = {0,1,4,1,3,0,2,0,1};
double array_2[9] = {1,2,0,2,0,1,1,3,2};
matrix a(3,3);
for(int i = 0; i<a.get_size();i++){
    a[i]=array_1[i];
}
matrix b(3,3);
for(int i = 0; i<a.get_size();i++){
    b[i]=array_2[i];
}
//print out matrix multiplication, addidition and subtraction
std::cout<<"Matrix A is:"<<std::endl;
std::cout<<a<<std::endl;
std::cout<<"Matrix B is:"<<std::endl;
std::cout<<b<<std::endl;
std::cout<<"B+A="<<std::endl;
std::cout<<b+a<<std::endl;
std::cout<<"B-A="<<std::endl;
std::cout<<b-a<<std::endl;
std::cout<<"B*A="<<std::endl;
std::cout<<b*a;
matrix c=a.remove_row_and_column(1,2);
std::cout<<"Matrix A with the first row and second column removed is: "<<std::endl;
std::cout<<c<<std::endl;
double detA = a.determinant();
std::cout<<"The determinant of matrix A is: "<<detA<<std::endl;
//show use of redefined >> function
std::cout << "Enter a matrix: "<<std::endl;
matrix new_matrix{};
std::cin >> new_matrix;
std::cout << "You entered: " << std::endl;
std::cout<<new_matrix<<std::endl;
//show copy and assignment operators work
matrix d;
d=a; 
std::cout<<"Matrix D has been created using a deep copy assignment of Matrix A"<<std::endl;
matrix e(a);
std::cout<<"Matrix E has been created using a deep copy constructor of Matrix A"<<std::endl;
a[2]=-2.5;
std::cout<<"Matrix A's 2nd element has been changed from 4 to -2.5"<<std::endl;
std::cout<<"A[2]= "<<a[2]<<std::endl;
std::cout<<"D[2]= "<<d[2]<<std::endl;
std::cout<<"E[2]= "<<e[2]<<std::endl;
matrix f;
f= std::move(b);
std::cout<<"Matrix F has been created using a move assignment operator from Matrix B"<<std::endl;
std::cout<<"F[3]= "<<f[3]<<std::endl;
std::cout<<"Matrix B is now a default Matrix"<<std::endl;
//determinant with a 4x4 and 5x5 matrix
double array_3[25] = {1,2,1,1,1,1,1,3,2,3,0,2,0,1,2,0,0,2,1,2,0,1,2,0,1};
double array_4[16] = {1,2,0,1,2,0,0,1,1,2,1,0,1,2,0,0};
double array_5[36] = {2,1,0,1,2,1,2,3,1,2,0,0,2,0,1,0,1,2,0,2,1,2,3,4,0,1,2,3,0,1,1,2,3,0,1,2};
matrix h(4,4);
for(int i = 0; i<h.get_size();i++){
    h[i]=array_4[i];
}
matrix g(5,5);
for(int i = 0; i<g.get_size();i++){
    g[i]=array_3[i];
}
matrix six_by_six(6,6);
for(int i = 0; i<six_by_six.get_size();i++){
    six_by_six[i]=array_5[i];
}
double detG = g.determinant();
std::cout<<"Matrix G is:"<<std::endl;
std::cout<<g<<std::endl;
std::cout<<"The determinant of matrix G is: "<<detG<<std::endl;
double detH = h.determinant();
std::cout<<"Matrix H is:"<<std::endl;
std::cout<<h<<std::endl;
std::cout<<"The determinant of matrix H is: "<<detH<<std::endl;
double detI = six_by_six.determinant();
std::cout<<"Matrix I is:"<<std::endl;
std::cout<<six_by_six<<std::endl;
std::cout<<"The determinant of matrix I is: "<<detI<<std::endl;
return 0;
}