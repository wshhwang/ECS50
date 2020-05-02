#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stack>
#include <bitset>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <istream>

using namespace std;

int main(int argc, char** argv){
    //get access data from   argc == 2
    // matA/0-test.txt       argv[1]
    // matB/0-test.txt       argv[2]
    (void) argc;
    int numberInput =0;
    int matrixSize = 0;
    vector <int> matrix1;
    vector <int> matrix2;

    for (int i=1; i<=2; i++){
        if (i==1){
            ifstream test_txt(argv[i]);
            test_txt >> numberInput;
            matrixSize = numberInput;
            while (test_txt >> numberInput){
                matrix1.push_back(numberInput);
            }

        }
        if (i==2){
            ifstream test_txt(argv[i]);
            test_txt >> numberInput;
            matrixSize = numberInput;
            while (test_txt >> numberInput){
                matrix2.push_back(numberInput);
            }
        }
    }

    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < matrixSize; column++){
            int result = 0;

            for(int count = 0; count < matrixSize; count++){
                    if ((count < column) || (count > row)) {continue;}
                    int matrix1value = ((matrixSize * row) + count - ((row) * (row + 1) / 2));
                    int matrix2value = ((matrixSize * count) + column - ((count) * (count + 1) / 2));
                    result += matrix1[matrix1value] * matrix2[matrix2value];
            }
            if (!(result==0)){
                cout << result<<" ";
            }
        }
    }
}