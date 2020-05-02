#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void swap(int** a, int** b){
    int* temp = *a;
    *a = *b;
    *b = temp;
}
 */
/*
int editDist(char* word1, char* word2){

  int word1_len = strlen(word1);
  int word2_len = strlen(word2);
  int* oldDist = (int*)malloc((word2_len + 1) * sizeof(int));
  int* curDist = (int*)malloc((word2_len + 1) * sizeof(int));

  int i,j,dist;

  //intialize distances to length of the substrings
  for(i = 0; i < word2_len + 1; i++){
    oldDist[i] = i;
    curDist[i] = i;
  }

  for(i = 1; i < word1_len + 1; i++){
    curDist[0] = i;
    for(j = 1; j < word2_len + 1; j++){
      if(word1[i-1] == word2[j-1]){
        curDist[j] = oldDist[j - 1];
      }//the characters in the words are the same
      else{
        curDist[j] = min(min(oldDist[j], //deletion
                          curDist[j-1]), //insertion
                          oldDist[j-1]) + 1; //subtitution
      }
    }//for each character in the second word
    swap(&oldDist, &curDist);
  }//for each character in the first word

  dist = oldDist[word2_len];//using oldDist instead of curDist because of the last swap
  free(oldDist);
  free(curDist);
  return dist;

}
*/
//int main(int argc, char** argv){

//int editDist(char* word1, char* word2);
//int min(int a, int b);
//void swap(int** a, int** b);
/*
int min(int a, int b){
    if (a<b){
        return a;
    }
    else{
        return b;
    }
}
 */

int main(){
        char* word1 = "Slow Slow Tango Close";
        char* word2 = "Quick Quick Slow";

        int word1_len = strlen(word1);
        int word2_len = strlen(word2);
        int* oldDist = (int*)malloc((word2_len + 1) * sizeof(int));
        int* curDist = (int*)malloc((word2_len + 1) * sizeof(int));

        int i;
        int j;
        int dist;

        //intialize distances to length of the substrings
        for(i = 0; i < word2_len + 1; i++){
            oldDist[i] = i;
            curDist[i] = i;
        }

        for(i = 1; i < word1_len + 1; i++){
            curDist[0] = i;
            for(j = 1; j < word2_len + 1; j++){
                if(word1[i-1] == word2[j-1]){
                    curDist[j] = oldDist[j - 1];
                }//the characters in the words are the same
                else{
                    /*
                    int f = min (oldDist[j],curDist[j-1]);
                    int g= min (f, oldDist[j-1]);
                    curDist[j]= g+1;
                     */

                    int a= oldDist[j];
                    int b= curDist[j-1];
                    int c= oldDist[j-1];

                    if (a<b){
                        if (a<c)
                        {curDist[j]= a+1;}
                        else
                        {curDist[j]= c+1;}
                    }
                    else{
                        if (b<c)
                        {curDist[j]= b+1;}
                        else{
                            curDist[j]= c+1;
                        }

                    }

                    //curDist[j] = min(min(oldDist[j],curDist[j-1]),oldDist[j-1]) + 1;
                }
            }//for each character in the second word

            int* temp = oldDist;

            oldDist = curDist;
            curDist = temp;


        }//for each character in the first word
        printf("%d word2_len\n", word2_len);
        dist = oldDist[word2_len];//using oldDist instead of curDist because of the last swap
        //free(oldDist);
        //free(curDist);


        printf("The distance between %s and %s is %d.\n", word1, word2, dist);

        // return 0;
    }

