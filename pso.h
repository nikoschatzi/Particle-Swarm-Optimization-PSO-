#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------  -----------User input parameters for optimization--------------------------------------------------------------------//

//define the number of variables for optimization
#define var_num 2

int population = 10;
int max_iterations = 30;
double lower_bound[var_num] = {55,85};
double upper_bound[var_num] = {100,100};

double objective_function(double v[var_num]) {

	double sum = 0;	
	sum = v[0] + v[1];

	return sum;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

struct PSO {
	double objective;
	double variable[var_num]; 
};
 
struct PSO PSO_run(int noP, int maxIter, double lower[], double upper[])
{
	struct PSO result;
     
	double wMax = 0.9;
	double wMin = 0.2;
	double c1 = 2;
	double c2 = 2;
	double vMax[var_num];
	double vMin[var_num];
	double w;
	double X[noP][var_num];
	double V[noP][var_num];
	double O[noP];
	double obj_input[var_num];

	double particle_best_X[noP][var_num];
	double particle_best_obj[noP];

	double best_X[var_num];
	double best_obj;

	//calculate vMax and vMin	
	for(int i=0; i<var_num; i++)
	{
	vMax[i] = (upper[i] - lower[i])*0.2;
	vMin[i] = -(upper[i] - lower[i])*0.2;
	}

	//Initialize the particles
	srand(time(NULL));

	for(int k=0; k<noP; k++)
	{
	particle_best_obj[k] = 1000000;

	for(int l=0; l<var_num; l++)
	{
		X[k][l] = (upper[l] - lower[l])*(0.01*(rand()%100)) + lower[l];
		V[k][l] = 0;
		particle_best_X[k][l] = 0;
	}		

	}

	for(int z=0; z<var_num; z++)
	{
	best_X[z] = 0;
	}	
	best_obj = 1000000;

	//main loop
	for(int n=0; n<maxIter; n++)
	{
	//check if better solution is found
	for(int p=0; p<noP; p++)
	{
		for(int g=0; g<var_num; g++)
		{
			obj_input[g] = X[p][g];
		}

		O[p] = objective_function(obj_input);

		if(O[p]<particle_best_obj[p])
		{
			particle_best_obj[p] = O[p];

			for(int j=0; j<var_num; j++)
			{
				particle_best_X[p][j] = X[p][j];
			}
		}

		if(O[p]<best_obj)
		{
			best_obj = O[p];

			for(int r=0; r<var_num; r++)
			{
				best_X[r] = X[p][r];
			}
		}

	}

	//update X and V
	w = wMax - n*((wMax-wMin)/maxIter);


	srand(time(NULL));
	for(int z=0; z<noP; z++)
	{
		for(int b=0; b<var_num; b++)
		{
			V[z][b] = w*V[z][b] + c1*(0.01*(rand()%100))*(particle_best_X[z][b]-X[z][b]) + c2*(0.01*(rand()%100))*(best_X[b]-X[z][b]);

			if(V[z][b]>vMax[b])
			{
				V[z][b] = vMax[b];
			}

			if(V[z][b]<vMin[b])
			{
				V[z][b] = vMin[b];
			}

			//update X
			X[z][b] = X[z][b] + V[z][b];

			if(X[z][b]>upper[b])
			{
				X[z][b] = upper[b];
			}

			if(X[z][b]<lower[b])
			{
				X[z][b] = lower[b];
			}

		}			
	}

	}

	result.objective = best_obj;

	for(int a=0; a<var_num; a++)
	{
	result.variable[a] = best_X[a];
	}

	return result;
}
