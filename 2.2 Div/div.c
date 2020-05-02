#include<stdio.h>
#include<stdlib.h>

int main (int argc , char **argv)
{
    unsigned long dividend = atoll(argv[1]);
    unsigned int divisor = atoi(argv[2]);
    unsigned int remainder = 0;
    unsigned int quotient= 0;
    unsigned int item = 0;
    //printf("%u\n", dividend);
    int i=31;
    for(; i >= 0 ; i--){
        remainder <<= 1;
        //printf("%d 1st remainder\n", remainder);
        //unsigned int y = dividend >>i;
        item = dividend >>i;
        //printf("%d\n", dividend);
        item = item &1;
        remainder = remainder | item;
        //printf("%d 2nd remainder\n", remainder);
        //unsigned int z = y & 1;
        //remainder |= ((dividend >> i)& 1);
        if( remainder >= divisor)
        {
            //remainder -= divisor;
            remainder = remainder - divisor;
            //printf("%d final remainder\n", remainder);
            unsigned int x = 1 << i;
            //printf("%d\n", i);
            quotient = quotient | x;

            //unsigned int count = (1 << i);
            //quotient |= count;
        }
    }
    printf("%lu / %d = %d R %d\n", dividend , divisor, quotient, remainder);
}