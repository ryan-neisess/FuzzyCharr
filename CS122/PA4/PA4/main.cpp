//Aerie, CS122 PA4
//24 Jan 2021

#include "FitnessAppWrapper.h"

int main() {
	
	fstream input, output;
	input.open("dietPlans.txt", std::ios::in);
	output.open("exercisePlans.txt", std::ios::out);

	FitnessAppWrapper programWrapper;
	programWrapper.loadWeeklyPlan(input);
	int c = 5;


	system("pause");
	return 0;
}