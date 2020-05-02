#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stack>
#include <bitset>
#include <algorithm>

using namespace std;
union U{
    float input;
    int i;};


int main()
{
    U u;


    //float input;
    cout<< "Please enter a float: ";
    cin>> u.input;
    //bitset<32> b1(input);
    //input.set();
    //cout<<"string mybitset" << b1<<"\n";

    //31 sign, 30-23 exponent, 22-0 mantissa

    unsigned int float_int = *((unsigned int*)&u.input);
    //unsigned int sign;
    //unsigned int exponent;
    //unsigned int mantis;
    if (float_int == 0) {
        cout<< "0E0"<<endl;
        return 0;
    }

    char plusOrNeg = '+';
    if ((float_int) & (1<<31)){
        plusOrNeg = '-';
        cout<< plusOrNeg<<"1.";
    }
    //else cout<< plusOrNeg; //dont need for +
    else cout<<"1.";


    string mantissa(31,' ');
    char mant[22];
    int count = 0;



         while (count <23){
            if (float_int & (1<<(count))) {
               mant[count] = '1';
                ++count;
               }
            else
            {mant[count] = '0';
             ++count;}





             }
         //mant[count] = '\0';
         mantissa = mant;
         reverse(mantissa.begin(), mantissa.end()); // #include <algorithm>


    int exponent = ((float_int>>23) & 0xff);
    //int exponent = ((float_int>>23) & 0x7f800000);
    if (exponent != 0)
    {exponent = exponent - 127;}

    //cout<<bitset<8>(input);
    //skip checking negative sign

    cout<< mantissa <<"E"<<exponent<<endl;

    return 0;
}