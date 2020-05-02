#include "MyFloat.h"

MyFloat::MyFloat(){
  sign = 0;
  exponent = 0;
  mantissa = 0;
}

MyFloat::MyFloat(float f){
  unpackFloat(f);
}

MyFloat::MyFloat(const MyFloat & rhs){
	sign = rhs.sign;
	exponent = rhs.exponent;
	mantissa = rhs.mantissa;
}

ostream& operator<<(std::ostream &strm, const MyFloat &f){
	strm << f.packFloat();
	return strm;

}

bool MyFloat::operator==(const float rhs) const{
    MyFloat temp(rhs);
    
    if(this->sign == temp.sign && this->exponent == temp.exponent && this->mantissa == temp.mantissa)
        return true;
    
    return false;
}


MyFloat MyFloat::operator+(const MyFloat& rhs) const{
    unsigned int diff;
    bool need_borrow = false;
    MyFloat sum;
    MyFloat f1, f2; // to modify sign, exponent, and mantissa

    // assign the larger number to f1 and the smaller one to f2
    if (rhs.exponent >= this->exponent){
        f1 = rhs;
        f2 = (*this);
    }
    else {
        f1 = (*this);
        f2 = rhs;
    }
    
    // calculate the difference between two exponents
    diff = f1.exponent - f2.exponent;
    sum.exponent = f1.exponent;
    
    // restore the leading 1
    f1.mantissa = f1.mantissa | (1 << 23);
    f2.mantissa = f2.mantissa | (1 << 23);
    
    // shift the radix of the smaller number to make exponents equal
    if(f2.mantissa & (1<<(diff-1))){
        // if the MSB shifted out is a 1, the subtraction need to borrow
        need_borrow = true;
    }
    f2.mantissa >>= (diff);
    
    // addition
    if(f1.sign){        // f1 is negative
        sum.sign = 1;
        if (f1.sign == f2.sign)     //f1, f2 are negative
            sum.mantissa = f1.mantissa + f2.mantissa;
        else{    // addition will not change sign
            sum.mantissa = f1.mantissa - f2.mantissa;
            if(need_borrow)
                sum.mantissa--;
            sum.sign = 1;
        }
    }
    else{
        sum.sign = 0;
        if (f1.sign == f2.sign)     //f1, f2 are positive
            sum.mantissa = f1.mantissa + f2.mantissa;
        else{    // addition will not change sign
            sum.mantissa = f1.mantissa - f2.mantissa;
            if(need_borrow)
                sum.mantissa--;
            sum.sign = 0;
        }
    }

    if(sum.mantissa == 0){
        // the sum is zero
        sum.exponent = 0;
        sum.sign = 0;
    }else if (sum.mantissa & (1 << 24)){
        // the leading 1's addition carries on
        sum.mantissa >>= 1;
        sum.exponent += 1;
    }else{
        // keeps adjusting the radix point and exponent until there's a 1 on the left
        while (!(sum.mantissa & (1 << 23))){
            sum.mantissa <<= 1;
            sum.exponent -= 1;
        }
    }
    // removing the leading 1
    sum.mantissa &= 0x7FFFFF;
    return sum;
}

MyFloat MyFloat::operator-(const MyFloat& rhs) const{
    MyFloat temp(rhs);
    if(temp.sign == 1)  // switch the sign
        temp.sign = 0;
    else
        temp.sign = 1;
    
    return operator+(temp);    // by equation: a - b = a + (-b)
}

void MyFloat::unpackFloat(float f)
{
    __asm__(
                "movl %[f], %[sign];"
                "shrl $31, %[sign];"      // eax will be sign
                "movl %[f], %[exponent];"
                "shll $1, %[exponent];"
                "shrl $24, %[exponent];"      // ebx will be exponent
                "movl %[f], %[mantissa];"
                "shll $9, %[mantissa];"
                "shrl $9, %[mantissa];"       // ecx will be mantissa
                :[sign]"=g" (sign), [exponent]"=g" (exponent), [mantissa]"=g" (mantissa)   // output
                :[f] "r" (f)                                                               // input
                :"cc"                                                                      // clobber
            );
}//unpackFloat

float MyFloat::packFloat() const{
  //returns the floating point number represented by this
  float f = 0;
    __asm__(
                "orl %[mantissa], %[f];"        // add mantissa
                "shll $23, %[exponent];"
                "orl %[exponent], %[f];"        // add exponent
                "shll $31, %[sign];"
                "orl %[sign], %[f];"        // add sign
                :[f]"+r"(f)                                                                 // output
                :[sign]"g" (sign), [exponent]"g" (exponent), [mantissa]"g" (mantissa)       // input
                :"cc"                                                                       // clobber
            );
  return f;
}//packFloat