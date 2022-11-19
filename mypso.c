#include "pso.h"

int main(int argc, char **argv) {
	
	struct PSO result;  
    result = PSO_run(population, max_iterations, lower_bound,upper_bound);
    
    printf("best objective = %f", result.objective);
    printf("\nbest v1 = %f", result.variable[0]);
    printf("\nbest v2 = %f", result.variable[1]);

    return 0;

}
