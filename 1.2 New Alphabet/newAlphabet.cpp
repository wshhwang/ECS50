#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stack>

using namespace std;

int main(int argc, char ** argv)
//https://stackoverflow.com/questions/3024197/what-does-int-argc-char-argv-mean/3024202
//acrc argument count
//argv argument vector
{
    char output;

    cout << "You entered the word: ";
    for (int i = 1; i < argc; ++i){
        unsigned int input = atoi(argv[i]);

        int add = 0;
        while( !(input & (1<<add))){
            add++;}

        int position = add;

        if ((input & (1<<26))){
            output = 'A' + position;
            cout<< output;
        }
        else if(!(input & (1<<26)))
        {   output = 'a' + position;
            cout<< output;
        }

    }
    return 0;
}
