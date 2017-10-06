#include <stdio.h>
#include <stdlib.h>

int CreateHistCsv(int *score_array, int trials, int numscen, const char *filename){
    FILE *hist_csv = NULL;
    int retcode = 0, *hist_arr;
    hist_arr = (int *)calloc(numscen, sizeof(int));
    hist_csv = fopen(filename, "w");
    fprintf(hist_csv, "Score-Bin, Frequency\n");
    for (int i = 0; i < numscen; i++){
        hist_arr[i] = 0;
        for (int j = 0; j < trials; j++){
            if (score_array[j] == i) hist_arr[i]++;  
        }
        fprintf(hist_csv, "%d, %d\n", i, hist_arr[i]);
    }
    fclose(hist_csv);
    return retcode;

}