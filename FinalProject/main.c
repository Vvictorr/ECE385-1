#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

int main() {
	//Variable 'order' will hold the order of the fit
	//Variable 'numPopulation' will hold the number of the population
	//Variable 'numPoints' will hold the number of of points 
	int order, numPopulation, numPoints;

	//Initiailize arrays for the coordinates
	float xData[10];
	float yData[10];

	//Initialize random number gerator by using the time of system clock in seconds
	srand(time(0));

	//Input order of the polynomial fit
	printf("Select the order of the polynomial fit: ");
	scanf_s("%i", &order);
	printf("The fit will be drawn in the order of %i.\n\n", order);

	//Increment 1 from the value of order to include the constant
	int numCoefficient = order + 1;

	//Input number of population
	printf("Select the desired number of population (<100): ");
	scanf_s("%i", &numPopulation);
	if (numPopulation > 20)
	{
		printf("WARNING: population that is too large can result in slower compilation\n");
	}
	printf("The function will now generate the %i numbers of points.\n\n", numPopulation);

	//Input number of points
	printf("Select the number of points you want to choose (<10): ");
	scanf_s("%i", &numPoints);
	printf("The function will now generate the %i numbers of points.\n\n", numPoints);

	////Initialize the array for the population which contains coefficient information
	//int coefficient = (int*)malloc(numPopulation * numCoefficient * sizeof(int));

	//for (i = 0; i < numPoints; i++)
	//{
	//	printf("Please enter the x coordinate of P(%i).\n", i + 1);
	//	scanf_s("%f", &xData[i]);
	//	printf("Please enter the y coordinate of P(%i).\n", i + 1);
	//	scanf_s("%f", &yData[i]);
	//}

	////Get the estimated coefficient value boundary
	//printf("What is the estimated absolute value of the coefficient?: ");
	//scanf_s("%i", &estCoeff);
	//printf("The coefficient will be initialized between %i and %i.\n\n", -estCoeff, estCoeff);

	////Generate an initial population
	//for (row = 0; row < numPopulation; row++)
	//{
	//	for (col = 0; col < numCoefficient; col++)
	//	{
	//		n = (row * numCoefficient) + col;
	//		coefficient[n] = (int)(rand() % ((2 * estCoeff) + 1)) - estCoeff;
	//	}

	//}

	////Print the initial coefficient array in 2D format
	//printf("\nCoefficient Array: \n\n");
	//for (i = 0; i < (numPopulation * numCoefficient); i++)
	//{
	//	//Convert the coefficient[] into a shape of 2D by entering new line every 'numCoefficient'
	//	j = i % numCoefficient;
	//	if (j == 0)
	//	{
	//		printf("\n");
	//		printf("Population %i: ", (i / numCoefficient) + 1);
	//		printf("%i ", coefficient[i]);

	//	}

	//	else {
	//		printf("%i ", coefficient[i]);
	//	}

	//}

	//printf("\n\n");

	////Creation of the 
}