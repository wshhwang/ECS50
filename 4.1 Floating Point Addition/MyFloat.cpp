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
	//this function is complete. No need to modify it.
	strm << f.packFloat();
	return strm;
}
////////////////////////////////////////////////////////

bool MyFloat::operator==(const float rhs) const{
		MyFloat temp(rhs);
		if(sign== temp.sign)
			{
			if(exponent == temp.exponent)
				{
				if(mantissa == temp.mantissa)
					{
					return true;
					}
				}
			}
		return false;			
		//return false; //this is just a stub so your code will compile
}
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
MyFloat MyFloat::operator-(const MyFloat& rhs) const{
		MyFloat temp(rhs);
		if(temp.sign == 1)
			{
		    temp.sign = 0;
			}
		else	
			{
		    temp.sign = 1;	
			}
		return *this + temp;  
		//return *this; //you don't have to return *this. it's just here right now so it will compile  
	}
/////////////////////////////////////////////////////////////////////

MyFloat MyFloat::operator+(const MyFloat& rhs) const{
    unsigned int exp_diff;
    bool borrow = false;
    MyFloat final;
    MyFloat large(rhs);
    MyFloat small(*this);

    if (!(rhs.exponent >= this->exponent))
		{ 
		  large = (*this);
          small = rhs;
	    }

    exp_diff = large.exponent - small.exponent;
	unsigned int exp_diff_change;
	exp_diff_change = exp_diff - 1;	

	final.exponent = large.exponent;
    large.mantissa |= 1 << 23; 
    small.mantissa |= 1 << 23; 

    small.mantissa = small.mantissa >> exp_diff;
    
    if(small.mantissa & (1<<(exp_diff_change)))
    	{
    	    borrow = true;
    	}
///////// addition ///////////////////////////


    if(large.sign)
		{     
        if (large.sign == small.sign)     
			{
			final.sign = 1;	            
			final.mantissa = large.mantissa + small.mantissa;
			}
        else
			{    
			final.sign = 1;            
			final.mantissa = large.mantissa - small.mantissa;
            if(borrow==true)
                {
				final.mantissa= final.mantissa -1;
			 	}
            
	        }
    	}

    else
		{
        if (large.sign == small.sign)     
            {
			final.sign = 0; // " + " 
			final.mantissa = large.mantissa + small.mantissa;
			}
        else
			{                
			final.sign = 0;  // " + "
            final.mantissa = large.mantissa - small.mantissa;
            if(borrow==true)
            	  {
					final.mantissa= final.mantissa -1;          	   
     		      }
		    }
	    }	

/////////////////////////////
    if(final.mantissa == 0){
        final.sign = 0;
        final.exponent = 0;

    }
//////////////////////////
    if (final.mantissa &(1<<24))
		{
		//final.sign= 0;
        final.mantissa = final.mantissa >> 1;
        final.exponent = final.exponent+ 1;
	    }
	else
		{
		//final.sign= 0;
		while ((final.mantissa &(1<<23))==false )
			{
			final.mantissa = final.mantissa << 1;
	        final.exponent = final.exponent-1;
			}
	    }

//////////////////////////////////////
		final.mantissa &= 0x7FFFFF;/// errorr**ask TA
     		return final;
		//return *this; //you don't have to return *this. it's just here right now so it will compile
}

////////////////////////////////////////////////////////////////

float MyFloat::packFloat() const{
	//this function must be written in inline assembly
  //returns the floating point number represented by this
   float f = 0;
    __asm__(
		//mantissa
		"movl %[mantissa], %[f];"   
		//"orl %[mantissa], %[f];"        

                // sign
		//"movl %[sign], %[f];"        
		"shll $31, %[sign];"
                "orl %[sign], %[f];"        

                //exponent
                //"movl %[exponent], %[f];"    
		"shll $23, %[exponent];"
                "orl %[exponent], %[f];"    
			
		//output
                :[f]"=a"(f)        
	
     	       //input
		:[sign]"b" (sign),[exponent] "c" (exponent), [mantissa]"d" (mantissa)
		// clobber
                :"cc"                                                  
            ); // end asm
  return f;
}
//end pack

void MyFloat::unpackFloat(float f) {
	//this function must be written in inline assembly
	//extracts the fields of f into sign, exponent, and mantissa

    __asm__(
			//mantissa
			"movl %[f], %[mantissa];"
			"shll $9, %[mantissa];"
			"shrl $9, %[mantissa];"
 
			//sign
			"movl %[f], %[sign];"
			"shrl $31,%[sign];"

			//exponent
			"movl %[f], %[exponent];"
			"shll $1, %[exponent];"
			"shrl $24, %[exponent];"      
			      
		
			//output
			// floet =a
			// sign =b
			// exponent =c
			// mantissa =d
			
		        :[sign]"=b"(sign),[exponent]"=c"(exponent),[mantissa]"=d"(mantissa) 
		      	:[f]"a"(f)//input
		    	:"cc"// clobber
		    );
}
//end unpack
//
















