#include <stdio.h>


int main() {
    int number = 89;
    char letter = 'b';
    double real_number = 35.27;
    char str[]= "hi class";
    // string in C is an array of characters that ends with the null character
    char str2[] = {'h','i', '\0'};



    printf("number is %d\n", number);
    printf("letter is %c and real_number is %lf \n", letter, real_number);
    printf("Hello, World! \n");
    printf("This is a string %s \n and so is %s \n", str, str2);
    printf("number as a character is %c \n", number);

    return 0;


}



