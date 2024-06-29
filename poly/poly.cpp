//4001406135
#include <iostream>
#include <string>  
#include <math.h>
#include <sstream>
using namespace std;
class polynomial{
    public:
        int coefficient = 0, exponent = 0;  
};
class polynomial_result{
    private:
        polynomial* polynomial1;
        polynomial* polynomial2;
        int a_size = 0, b_size = 0;
    public:
        polynomial* result;
        polynomial_result(){
            polynomial1 = new polynomial[a_size];
            polynomial2 = new polynomial[b_size];  
            result = new polynomial[b_size * a_size] ;
        }
        //=========================================================================================================================
        string polynomial_make(string num_1, string num_2, string Operators){
            string final = "";
            size(num_1, num_2);     //first we find size of each phrase
            fill_polynomial_array(num_1, polynomial1);      //then we make polynomial of each one of them
            fill_polynomial_array(num_2, polynomial2);      //then we make polynomial of each one of them
            //now we do what user wants by enter value of Operator
            if (Operators == "sum"){
                polynomials_sum();
            }else if(Operators == "multiple"){
                polynomials_multiple(f);
            }
            sort_result(f);     //now sort the result polynomial
            for(int i = 0 ; i < a_size*b_size ; i++){
                if(result[i].coefficient == 0 && result[i].exponent == 0)   continue;
                if (result[i].coefficient < 0 ){
                    final += " - ";
                    final += to_string(abs(result[i].coefficient));
                }else{
                    if(i != 0){
                        final += " + ";
                    }
                    final += to_string(abs(result[i].coefficient));
                }
                final += "x^";
                final += to_string(result[i].exponent);
            }
            return final;
        }
        //=========================================================================================================================
        void size(string num_1, string num_2){      // find size of each phrase so we can make a polynomial class array with same size
            for (int i = 0 ; num_1[i] != '\0' || num_2[i] != '\0'; i++){
                if ((num_1[i] == '+' || num_1[i] == '-') && i !=0)  
                    a_size++;
                if ((num_2[i] == '+' || num_2[i] == '-') && i !=0)  
                    b_size++;
            }
            a_size++;
            b_size++;
            polynomial_result();        //now call the constrictor function to make polynomials
            for (int i = 0 ; i < a_size*b_size ; i++){
                result[i].coefficient = 0;
                result[i].exponent = 0;
            }  
        }
        //=========================================================================================================================
        void fill_polynomial_array(string num, polynomial* s){
            string temp_coefficient = "", temp_exponent = "";
            int j = 0, h = 0, f = 0;        // h show place of coefficient, f show place of exponent, and j show where to add this two in array
            for (int i = 0 ; num[i] != '\0'; i++){      //when we find "x" if we go forward it is exponent, if we go backward it is coefficient for each part of string which have separated by an operators
                if(num[i] == 'x'){
                    for (h = f ; h < i ; h++){      // h is equal to start of a math phrase where coefficient is
                        temp_coefficient += num[h];     // it will start from h to where num[h] == "x"
                    }
                    f = i+2 ;       // f show where exponent start, because x is show by x^2 and i show x so f must be i+2 to show first char of exponent
                    while(true){
                        if (num[f] == '+' || num[f] == '-' || num[f] == '\0'){      // when num[f] reach an operator or end of string it will stop
                            h = f+1 ;       // h change because one of several math phrase are finish for example 1x^2 is a part of 1x^2 + 3x^4 after one loop h show next part which is 3x^4 in our example
                            break;
                        }
                        temp_exponent += num[f];
                        f++ ;
                    }
                    // now we have coefficient and exponent so we add them to given array of function
                    s[j].exponent = stoi(temp_exponent);
                    s[j].coefficient = stoi(temp_coefficient);
                    j++;
                    temp_exponent = "";
                    temp_coefficient = "";
                }
            }
        }
        //=========================================================================================================================
        int f = 0;      //will be used in polynomial_multiple, and sort_result function
        void polynomials_multiple(int& f){      // multiple of a and b
            for(int i = 0 ; i < a_size ; i++){
                for(int j = 0 ; j < b_size ; j++){
                    bool flag = false;      // flag must reset every time so we put it in loop
                    if ( polynomial1[i].exponent == polynomial2[j].exponent ){//if exponents are same we only need to multiple coefficients
                        //check if a exponent is already exist it only add to it`s coefficient in result array
                        for (int g = 0 ; g <= f ; g++){
                            if (result[g].exponent == polynomial1[i].exponent){
                                result[g].coefficient += polynomial1[i].coefficient * polynomial2[j].coefficient;
                                flag = true;
                                break;
                            }
                        }
                        //check if a exponent isn`t exist it add both exponent and coefficient to result array
                        if (flag == false){     //if flag == true it mean that exponent was already exist and coefficient was add to it so we dont need to do this part again
                            result[f].exponent = polynomial1[i].exponent + polynomial2[j].exponent;
                            result[f].coefficient = polynomial1[i].coefficient * polynomial2[j].coefficient;
                            f++ ;
                        }
                    }else{      // if exponent are not the same, exponents must be sum with each other
                        //check if a exponent is already exist it only add to it`s coefficient in result array
                        for (int g = 0 ; g <= f ; g++){
                            if (result[g].exponent == (polynomial1[i].exponent + polynomial2[j].exponent)){
                                result[g].coefficient += polynomial1[i].coefficient * polynomial2[j].coefficient;
                                flag = true;
                                break;
                            }
                        }
                        //check if a exponent isn`t exist it add both exponent and coefficient to result array
                        if (flag == false){//if flag == true it mean that exponent was already exist and coefficient was add to it so we dont need to do this part again
                            result[f].exponent = polynomial1[i].exponent + polynomial2[j].exponent;
                            result[f].coefficient = polynomial1[i].coefficient * polynomial2[j].coefficient;
                            f++ ;
                        }
                    }        
                }
            }
        }
        //=========================================================================================================================
        void polynomials_sum(){
            int f = 0 ;
            for(int i = 0 ; i < a_size ; i++){
                bool flag = false;
                for(int j = 0 ; j < b_size ; j++){
                    if (polynomial1[i].exponent == polynomial2[j].exponent){        // if exponents be same sum of them is equal to sum of coefficient
                        result[f].exponent = polynomial1[i].exponent;
                        result[f].coefficient = polynomial1[i].coefficient + polynomial2[j].coefficient;
                        polynomial2[j].coefficient = 0 ;
                        polynomial2[j].exponent = 0 ;
                        flag = true ;
                        f++;
                        break;
                    }
                }
                if( flag == false ){        // if we dont find an equal exponents so we must add the polynomial to result
                    result[f].exponent = polynomial1[i].exponent;
                    result[f].coefficient = polynomial1[i].coefficient;
                    f++;
                }
            }
            for (int j = 0 ; j < b_size ; j++){
                if (polynomial2[j].exponent != 0 || polynomial2[j].coefficient != 0){
                    result[f].exponent = polynomial2[j].exponent;
                    result[f].coefficient = polynomial2[j].coefficient;
                    f++;
                }
            }   
        }
        //=========================================================================================================================
        void sort_result(int &f){       // because it is an array of polynomial exponent and coefficient value, we can`t use fast sort algorithm so we use bubble sort
            for (int i = 0 ; i < f ; i++){
                for (int j = 0 ; j < f ; j++){
                    if (result[i].exponent > result[j].exponent){
                        //swap values of coefficient and exponent of two part of array
                        int temp_exponent = result[j].exponent;
                        int temp_coefficient = result[j].coefficient;
                        result[j].exponent = result[i].exponent;
                        result[j].coefficient = result[i].coefficient;
                        result[i].exponent = temp_exponent;
                        result[i].coefficient = temp_coefficient;
                    }
                }
            }
        }
        //=========================================================================================================================
};
int main(){
    string a, b, c, d;
    cout<<"Please enter a math phrase like: 5x^10-2x^3\n";
    cout<<"Please enter a math phrase 1: ";
    cin>>a;
    cout<<"Please enter a math phrase 2: ";
    cin>>b;
    cout<<"what you want to do with this phrase\n"<<"1.sum\n"<<"2.multiple\nenter string not number: ";
    cin>>c;
    int f = 0 ;
    polynomial_result A;
    d = A.polynomial_make(a, b, c);
    cout<<"---------------------------------------------------------\n";
    cout<<"a: "<<a<<"\nb: "<<b<<'\n'<<c<<" of a, and b is: "<<d;
    return 0;
}