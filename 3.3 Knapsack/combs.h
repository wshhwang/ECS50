#ifndef COMBS_H
#define COMBS_H
  /*int max(int a, int b);
  int min(int a, int b);

  int num_combs(int n, int k);
  int** get_combs(int* items, int k, int len);
   */

#endif
 void rec_combos(int k, int num_cols,int len, int* row,int* temp,int* items,int** mat){
    if(k == 0){
        for(int i = 0; i < num_cols; ++i){
            mat[*row][i] = temp[i];
        }
        (*row)++;
        return;
    }else{
        for(int i = 0; i < len; i++){
            temp[num_cols - k] = items[i];
            rec_combos(k - 1, num_cols, len - i - 1,row,temp,items + i + 1,mat);
        }
    }
 }

 int** get_combs(int* items, int k, int len){
    int cmbs = num_combs(len, k);
    int** mat = (int**)malloc(cmbs * sizeof(int*));
    int* temp = (int*)malloc(k *sizeof(int));
    int row = 0;

    for(int i = 0; i < cmbs; ++i){
        mat[i] = (int*)malloc(k * sizeof(int));
    }
    rec_combos(k,k,len,&row,temp,items,mat);
    return mat;
 }