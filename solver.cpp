/* this is a function that reads in a model from an lp file
 and solves it. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "gurobi_c++.h"
#include "gurobi_c.h"


 int solver(const char *lpfilename, double *solution, int *pstatus)
 {
    GRBenv     *env = NULL;
    GRBmodel *model = NULL;
    int error = 0;
    int j, k, solcount, numvars, numcons;
    double objn, vobj, xn;
    int optimstatus;
    double objval;
    char *varname;
    double x;
    FILE *log_file = NULL;
    //const char *logfilename = "mygurobi.log";

    // Create environment

    error = GRBloadenv(&env, "lpenv.log");
    if (error) goto QUIT;

    // Open log file for writing
    //log_file = fopen(logfilename, "w");
    if (!log_file){
        printf("Cannot open log file %s for writing\n", logfilename);
        exit(1);
    } 

    // Read model from the specified file
    error = GRBreadmodel(env, lpfilename, &model);
    if (error) goto QUIT;

    //fprintf(log_file, "Solving %s\n", lpfilename);

    // Solve the model
    error = GRBoptimize(model);
    if (error) goto QUIT;

    // Compute the number of variables and constraints in the model
    error = GRBgetintattr(model, "NumVars", &numvars);
    if (error) goto QUIT;
    error = GRBgetintattr(model, "NumConstrs", &numcons);
    if (error) goto QUIT;

    //fprintf(log_file, "variables = %d\n", numvars);
    //fprintf(log_file, "constraints = %d\n", numcons);

    // Capture solution information
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) goto QUIT;
  
    printf("\nOptimization complete\n");
    if (optimstatus == GRB_OPTIMAL) {
      error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
      if (error) goto QUIT;
      printf("Optimal objective: %.4e\n\n", objval);
      //fprintf(log_file, "Optimal objective = %.4e\n", objval);
    } else if (optimstatus == GRB_INF_OR_UNBD) {
      printf("Model is infeasible or unbounded\n\n");
      //fprintf(log_file, "->LP infeasible or unbounded\n");
      goto QUIT;
    } else if (optimstatus == GRB_INFEASIBLE) {
      printf("Model is infeasible\n\n");
      //fprintf(log_file, "->LP infeasible\n");
      goto QUIT;
    } else if (optimstatus == GRB_UNBOUNDED) {
      printf("Model is unbounded\n\n");
      //fprintf(log_file, "->LP unbounded\n");
      goto QUIT;
    } else {
      printf("Optimization was stopped with status = %d\n\n", optimstatus);
      goto QUIT;
    }

    /* Check if Type A arbitrage exists and return the portfolio vector */
    if (objval < -0.0001) {
      printf("type A arbitrage exists! \n");
      *pstatus = 0;

      for (j = 0; j < numvars; j++)
      {
        error = GRBgetstrattrelement(model, "Varname", j, &varname);
        if (error) goto QUIT;
        error = GRBgetdblattrelement(model, "X", j, &x);
        if (error) goto QUIT;
        printf("%s = %f\n", varname, x);
        //fprintf(log_file, "%s = %f\n", varname, x);
        solution[j] = x;
      }
    }

    else{
      *pstatus = 1;
      printf("No type A\n");
    }

    //fprintf(log_file, "bye.\n");

    QUIT:
    //fclose(log_file);

    if (error) {
        printf("ERROR %s \n", GRBgeterrormsg(env));
        exit(1);
    }

    // Free models
    GRBfreemodel(model);

    // Free environment
    GRBfreeenv(env);
    
    return 0;
 }