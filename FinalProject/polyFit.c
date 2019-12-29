#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

int main() {
	//Declare indexes for the loops
	int i, j, k, n;
	int row, col;
	int temp;

	//Variable 'numPoints' will hold the number of of points 
	int numPoints;

	//Variable 'DECPOINT' holds the constant to generate the random float value instead of int
	int DECPOINT = 100;

	//Initiailize arrays for the coordinates
	float xData[10] = {0};
	float yData[10] = {0};

	//Initialize random number gerator by using the time of system clock in seconds
	srand(time(0));

	//Input number of points
	printf("Select the number of points you want to choose (Max: 10): ");
	scanf_s("%i", &numPoints);
	printf("The function will now generate the %i numbers of points.\n\n", numPoints);

	//Input the float values between -1 and 1
	for (i = 0; i < numPoints; i++)
	{
		printf("Point %i: ", i + 1);

		//xData[i] = ((rand() % 201) - 100)/100;
		xData[i] = (float)((rand() % ( (1-(-1)) * DECPOINT ) + 1) + ((-1) * DECPOINT))/100;
		printf("(%.2f, ",xData[i]);
		
		//yData[i] = ((rand() % 201) - 100)/100;
		yData[i] = (float)((rand() % ( (1-(-1)) * DECPOINT ) + 1) + ((-1) * DECPOINT))/100;
		printf("%.2f)\n",yData[i]);
	}

	//Start the genetic algorithm to create the fit for polynomial to the points
	//The fit will be in order of 'order' inputted

	//Variable 'numPopulation' will hold the number of the population
	//Variable 'order' will hold the order of the fit
	int order, numPopulation;

	//Input order of the polynomial fit
	printf("\nSelect the order of the polynomial fit (Max: 10): ");
	scanf_s("%i", &order);
	printf("The fit will be drawn in the order of %i.\n\n", order);

	//Increment 1 from the value of order to include the constant
	int numCoefficient = order + 1;

	//Input number of population
	printf("Select the desired number of population (Max: 100): ");
	scanf_s("%i", &numPopulation);
	if (numPopulation > 20)
	{
		printf("WARNING: population that is too large can result in slower compilation\n");
	}
	printf("The function will now generate the %i numbers of points.\n\n", numPopulation);

	//Generate initial population
	//Initialize 2D array for the population which contains coefficients and constant information
	//Usage: float coefficient[maxPopulation][maxCoefficient]
	float coefficient[100][11];

	//Input randomly genearated value inside the array
	for (i = 0; i < numPopulation; i++)
	{
		for (j = 0; j < numCoefficient; j++)
		{
			coefficient[i][j] = (float)((rand() % ( (10-(-10)) * DECPOINT ) + 1) + ((-10) * DECPOINT))/100;
			printf("%.2f ", coefficient[i][j]);
		}
		printf("\n");
	}

	//Calculate initial fitness
	
	float totSqDiff = 0;
	int minLocation = 0, maxLocation = 0;
	int minLocationSecond = 0, maxLocationSecond = 0;
	
	float yCalced[100][10] = { 0 };
	float sqDiff[10] = { 0 };
	float error[100] = { 0 };

	for (i = 0; i < numPopulation; i++)
	{
		for (j = 0; j < numPoints; j++)
		{
			for (k = 0; k < numCoefficient; k++)
			{
				yCalced[i][j] += coefficient[i][k] * pow(xData[j], k); 
			}

			sqDiff[j] = pow((yData[j] - yCalced[i][j]), 2); 
			totSqDiff += sqDiff[j];
		}

		error[i] = totSqDiff/numPoints;
		totSqDiff = 0;

		printf("Error of Population %i: %f\n", i+1, error[i]);

		if (error[i] < error[minLocation])
		{
			minLocationSecond = minLocation;
			minLocation = i;
		}
		else if (error[i] < error[minLocationSecond] && error[i] > error[minLocation])
		{
			minLocationSecond = i;
		}

		if (error[i] > error[maxLocation])
		{
			maxLocationSecond = maxLocation;
			maxLocation = i;
		}
		else if (error[i] > error[maxLocationSecond] && error[i] < error[maxLocation])
		{
			maxLocationSecond = i;
		}
	}

	printf("\n\n");
	printf("The lower the error is, the better the fitness is.\n");
	printf("Current minimum and maximum error present is %f and %f.\n", error[minLocation], error[maxLocation]);
	printf("Second minimum and maximum error present is %f and %f.\n", error[minLocationSecond], error[maxLocationSecond]);

	//Variable 'iterCnt' saves the number of generations
	int iterCnt = 0;

	//Evolve if fitness isn't good enough and no perfect fit is found
	while (iterCnt < 10000 && error[minLocation] != 0)
	{

		//Count the number of evolution
		iterCnt++;

		//Selection phase of genetic algorithm
		//Select two dataset with highest fitness (lowest error) and create offspring
		float offspring1[11] = { 0 };
		float offspring2[11] = { 0 };

		for (i = 0; i < numCoefficient; i++)
		{
			offspring1[i] = coefficient[minLocation][i];
			offspring2[i] = coefficient[minLocationSecond][i];
		}

		//Crossover phase of genetic algorithm
		//Generate random crossover point
		int crPoint;
		crPoint = (int)(rand() % (order + 1));

		//Exchange genes inside the chromosome
		for (i = 0; i < crPoint; i++)
		{
			temp = offspring1[i];
			offspring1[i] = offspring2[i];
			offspring2[i] = temp;
		}

		//Mutation phase of genetic algorithm to maintain the diversity
		//Randomly generate the values to decide whether the genome will mutate or not, and its intensity if it mutates

		int mutationProb = 20;
		int mutaIntensity = 5;
		float randMutaIntensity;
		int randMutation;

		randMutation = (int)(rand() % 100);
		randMutaIntensity = (float)(((rand() % ((2 * mutaIntensity) + 1)) - mutaIntensity) / 10);
		int mutaPoint;
		mutaPoint = (int)(rand() % (order + 1));

		if (mutationProb > randMutation)
		{
			printf("Mutation occured!\n");
			for (i = 0; i < (numCoefficient / 4); i++)
			{
				offspring1[mutaPoint] = offspring1[mutaPoint] + (randMutaIntensity * offspring1[mutaPoint]);
				offspring2[mutaPoint] = offspring2[mutaPoint] + (randMutaIntensity * offspring2[mutaPoint]);
			}

		}

		//Replace phase of genetic algorithm
		for (i = 0; i < numCoefficient; i++)
		{
			coefficient[maxLocation][i] = offspring1[i];
			coefficient[maxLocationSecond][i] = offspring2[i];
		}

		//Update the new fitness
		totSqDiff = 0;
		minLocation = 0, maxLocation = 0;
		minLocationSecond = 0, maxLocationSecond = 0;

		//Clear the used array
		for (i = 0; i < 100; i++)
		{
			for (j = 0; j < 10; j++)
			{
				yCalced[i][j] = 0;
			}
		}

		for (i = 0; i < 10; i++)
		{
			sqDiff[i] = 0;
		}

		for (i = 0; i < 10; i++)
		{
			error[i] = 0;
		}

		for (i = 0; i < numPopulation; i++)
		{
			for (j = 0; j < numPoints; j++)
			{
				for (k = 0; k < numCoefficient; k++)
				{
					yCalced[i][j] += coefficient[i][k] * pow(xData[j], k);
				}

				sqDiff[j] = pow((yData[j] - yCalced[i][j]), 2);
				totSqDiff += sqDiff[j];
			}

			error[i] = totSqDiff / numPoints;
			totSqDiff = 0;

			printf("Error of Population %i: %f\n", i + 1, error[i]);

			if (error[i] < error[minLocation])
			{
				minLocationSecond = minLocation;
				minLocation = i;
			}
			else if (error[i] < error[minLocationSecond] && error[i] > error[minLocation])
			{
				minLocationSecond = i;
			}

			if (error[i] > error[maxLocation])
			{
				maxLocationSecond = maxLocation;
				maxLocation = i;
			}
			else if (error[i] > error[maxLocationSecond] && error[i] < error[maxLocation])
			{
				maxLocationSecond = i;
			}
		}

		printf("\n\n");
		printf("The lower the error is, the better the fitness is.\n");
		printf("Current minimum and maximum error present is %f and %f.\n", error[minLocation], error[maxLocation]);
		printf("Second minimum and maximum error present is %f and %f.\n", error[minLocationSecond], error[maxLocationSecond]);

	}

	printf("\nFit found!\n");
	printf("The fit for the point: \n");

	for (i = 0; i < numPoints; i++)
	{
		printf("Point %i: ", i + 1);

		//xData[i] = ((rand() % 201) - 100)/100;
		xData[i] = (float)((rand() % ((1 - (-1)) * DECPOINT) + 1) + ((-1) * DECPOINT)) / 100;
		printf("(%.2f, ", xData[i]);

		//yData[i] = ((rand() % 201) - 100)/100;
		yData[i] = (float)((rand() % ((1 - (-1)) * DECPOINT) + 1) + ((-1) * DECPOINT)) / 100;
		printf("%.2f)\n", yData[i]);
	}

	printf("is: \n");

	for (k = 0; k < numCoefficient; k++)
	{
		if (k == numCoefficient - 1)
		{
			printf("%.2f*x^%i!", coefficient[minLocation][k], k);
		}
		else
		{
			printf("%.2f*x^%i + ", coefficient[minLocation][k], k);
		}
	}

}