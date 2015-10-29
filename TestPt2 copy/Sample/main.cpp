#include <string> //if you’re going to be using the string class.
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream> //when you want to use cout and cin.
#include <fstream> //when you want to read or write files.
#include <iomanip> //if you want advanced manipulator usage in your streams.
#include <stdlib.h> //for general operations, including system(“PAUSE”).
using namespace std;

//test part 2: triathalons
int main()
{
	//variables
	vector<int> person, solution_order, possible_solution_values;
	vector<int>::iterator iter;
	int solution = 0, sum = 0, time = 0;
	int size = 10;
	char selection;

	cout << "Welcome to the Triathelon Optimization Program" << endl << endl;

	cout << "This program will calculate the most efficient order of completion for triathelets." << endl;

	cout << "Use a Greedy Algorithm or Exhausting Search" << endl;
	cout << "To find the optimal solution?" << endl << endl;
	cout << "Type G or E." << endl << endl;
	cin >> selection;

	//fill in job id's
	for (int i = 0; i != size; i++)
	{
		person.push_back(i + 1);
	}

	solution_order.resize(size);
	possible_solution_values.resize(size);

	//fill weight and time data values
	double swimming[10] = { 20, 35, 40, 25, 22, 37, 42, 27, 31, 36 };
	double biking[10] = { 25, 20, 20, 30, 27, 18, 22, 32, 16, 24 };
	double running[10] = { 20, 15, 30, 25, 18, 17, 28, 24, 18, 26 };

	if (selection == 'G' || selection == 'g')
	{
		//timer implementation
		double startTime = clock();

		cout << endl << "Athelete data has been initialized" << endl << endl;

		cout << "Now the efficiency calculation will begin" << endl << endl;

		cout << "Sorting..." << endl << endl;

		//sort by ratio weight/time
		bool sorted = false;
		int swap;
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i != person.size() - 1; i++)
			{
				/*for (iter = person.begin(); iter != person.end(); iter++)
				cout << *iter << " ";
				cout << endl << endl;*/

				//sort the person by weight over time
				if ( (biking[person[i] - 1] + running[person[i] - 1]) < (biking[person[i + 1] - 1] + running[person[i + 1] - 1]) )
				{
					sorted = false;
					swap = person[i + 1];
					person[i + 1] = person[i];
					person[i] = swap;
				}
			}
		}

		int index;
		//calculate the solution
		for (iter = person.begin(); iter != person.end(); iter++)
		{
			//get the job id and use it as an index
			//the minus one accounts for the actual vector position
			index = *iter - 1;

			//calculate the solution
			//solution += swimming[index];
			possible_solution_values[index] += (time + swimming[index] + biking[index] + running[index]);

			//accumulate the time for each person
			time += swimming[index];
		}

		//fill the solution variable that is currently zero with the latest finish time
		for (iter = person.begin(); iter != person.end(); iter++)
		{
			index = *iter - 1;
			if (possible_solution_values[index] > solution)
				solution = possible_solution_values[index];
		}

		//timer output
		double endTime = (double)(clock() - startTime) / 1000.00;
		cout << "Duration: " << endTime << endl << endl;
		//solution output
		cout << "Solution found!" << endl << endl;
		cout << "The optimal vector is: ";
		for (int i = 0; i != person.size(); i++)
		{
			cout << person[i] << " ";
		}
		cout << endl << "The solution value is: " << solution << endl;
	}
	else
	{
		//timer implementation
		double startTime = clock();

		cout << "Job data has been initialized" << endl << endl;

		int index; 

		//initialize a starting solution with the default ordering 1...N for comparisons
		for (iter = person.begin(); iter != person.end(); iter++)
		{
			//get the job id and use it as an index
			//the minus one accounts for the actual vector position
			index = *iter - 1;

			//calculate the solution
			//solution += swimming[index];
			possible_solution_values[index] += (time + swimming[index] + biking[index] + running[index]);

			//accumulate the time for each person
			time += swimming[index];

			//initialize a solution order
			solution_order[index] = person[index];
		}

		//fill the solution variable that is currently zero with the latest finish time
		for (iter = possible_solution_values.begin(); iter != possible_solution_values.end(); iter++)
		{
			if (*iter > solution)
				solution = *iter;
		}

		cout << "Now the efficiency calculation will begin" << endl << endl;

		cout << "Thinking..." << endl << endl;

		//generate all permutations
		while (next_permutation(person.begin(), person.end()))
		{
			//sum holds the summation of each job permutation for comparison to the current best solution
			sum = 0;
			//zero out the time for the beginning of each job permutation
			time = 0;

			int index;

			possible_solution_values.clear();
			possible_solution_values.resize(size);

			for (iter = person.begin(); iter != person.end(); iter++)
			{
				//get the job id and use it as an index
				//the minus one accounts for the actual vector position
				index = *iter - 1;

				//calculate the solution
				//solution += swimming[index];
				possible_solution_values[index] += (time + swimming[index] + biking[index] + running[index]);

				//accumulate the time for each person
				time += swimming[index];
			}

			//fill the solution variable that is currently zero with the latest finish time
			for (iter = possible_solution_values.begin(); iter != possible_solution_values.end(); iter++)
			{
				if (*iter > sum)
					sum = *iter;
			}

			//if the sum of the current permutation is better, save it
			if (sum < solution)
			{
				//store new solution
				solution = sum;
				for (int i = 0; i != solution_order.size(); i++)
					solution_order[i] = person[i];
			}

		}

		//timer output
		double endTime = (double)(clock() - startTime) / 1000.00;
		cout << "Duration: " << endTime << endl << endl;
		//solution output
		cout << "Solution found!" << endl << endl;
		cout << "The optimal order of atheletes is: ";
		for (int i = 0; i != solution_order.size(); i++)
		{
			cout << solution_order[i] << " ";
		}
		cout << endl << "The solution value is: " << solution << endl;
	}

	cout << endl << "Enter a character when finished" << endl;
	char c;
	cin >> c;

	return 0;
}