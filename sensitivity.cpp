/* function for doing sensitivity analysis */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *sensitivity(double *prices, int numscen, int numsec, double *solution, int trials = 100){
    int *stressed_result, i, j, k, *score;
    double *stressed_data, portfolio_val, random;

    srand(time(0));

    score = (int *)calloc(trials, sizeof(int));
    stressed_data = (double *)calloc((1+numsec), sizeof(double));
    //stressed_result = (int *)calloc(trials*numscen, sizeof(int));
    for (i = 0; i < trials; i++){
        score[i] = 0;
        
        //for every scenario perturb the prices of securities except cash
        for (j = 1; j <= numscen; j++){
            portfolio_val = 0;
            
            for (k = 0; k <= numsec; k++){

                random = ((double)rand()/RAND_MAX)*0.1 - 0.05;
                // Stressed prices remain unchanged for cash
                if (k == 0){
                    stressed_data[k] = prices[j*(1+numsec) + k];
                }
                else{
                    stressed_data[k] = prices[j*(1+numsec) + k]*(1 + random);
                
                }
                portfolio_val = portfolio_val + stressed_data[k]*solution[k];
                //portfolio_val = portfolio_val + prices[j*(1+numsec) + k]*solution[k];
            }
            //printf("portfolio value for perturbed scenario %d: %f\n", j, portfolio_val);
            if (portfolio_val < 0) score[i] = score[i] + 1;
            
        }
        //printf("score for trial %d: %d\n", i, score[i]);
           
    }
    
    free(stressed_data);
    return score;
}
