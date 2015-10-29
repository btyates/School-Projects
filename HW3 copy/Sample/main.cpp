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

int main()
{
	//variables
	vector<int> jobs, solution_set; 
	vector<int>::iterator iter;
	int solution = 0, sum = 0, time=0;
	int size = 15;
	char selection; 

	cout << "Welcome to the Weighted Job Calculation Program" << endl << endl;

	cout << "This program will calculate the most efficient order of completion for the jobs." << endl;

	cout << "Use a Greedy Algorithm or Exhausting Search" << endl;
	cout << "To find the optimal solution?" << endl << endl;
	cout << "Type G or E." << endl << endl;
	cin >> selection;

	//fill in job id's
	for (int i = 0; i != size; i++)
	{
		jobs.push_back(i + 1);
	}

	solution_set.resize(size);

	//fill weight and time data values
	double weights[15] = { 6, 7, 5, 7, 8, 2, 11, 9, 13, 11, 4, 10, 11, 12, 13 };
	double times[15] = { 4, 5, 2, 3, 6, 1, 10, 7, 8, 9, 4, 7, 7, 8, 9 };


	if (selection == 'G' || selection == 'g')
	{
		//timer implementation
		double startTime = clock();

		cout << endl << "Job data has been initialized" << endl << endl;

		cout << "Now the efficiency calculation will begin" << endl << endl;

		cout << "Sorting..." << endl << endl;

		//sort by ratio weight/time
		bool sorted = false;
		int swap;
		while (!sorted)
		{
			sorted = true;
			for (int i = 0; i != jobs.size() - 1; i++)
			{
				/*for (iter = jobs.begin(); iter != jobs.end(); iter++)
					cout << *iter << " ";
				cout << endl << endl;*/

				//sort the jobs by weight over time
				if (weights[jobs[i]-1] / times[jobs[i]-1] < weights[jobs[i+1]-1] / times[jobs[i+1]-1])
				{ 
					sorted = false;
					swap = jobs[i+1];
					jobs[i+1] = jobs[i];
					jobs[i] = swap;
				}
			}
		}

		//calculate the solution
		for (iter = jobs.begin();  iter != jobs.end(); iter++)
		{
			int index;

			//get the job id and use it as an index
			//the minus one accounts for the actual vector position
			index = *iter - 1;
			time += times[index];

			//calculate the solution
			solution += weights[index] * time;
		}

		//timer output
		double endTime = (double)(clock() - startTime) / 1000.00;
		cout << "Duration: " << endTime << endl << endl;
		//solution output
		cout << "Solution found!" << endl << endl;
		cout << "The optimal vector is: ";
		for (int i = 0; i != jobs.size(); i++)
		{
			cout << jobs[i] << " ";
		}
		cout << endl << "The solution value is: " << solution << endl;
	}
	else 
	{
		//timer implementation
		double startTime = clock();

		cout << "Job data has been initialized" << endl << endl;

		//initialize a starting solution
		for (iter = jobs.begin(); iter != jobs.end(); iter++)
		{
			int index;

			//get the job id and use it as an index
			//the minus one accounts for the actual vector position
			index = *iter - 1;
			time += times[index];

			//calculate the solution
			solution += weights[index] * time;
		}

		cout << "Now the efficiency calculation will begin" << endl << endl;

		cout << "Thinking..." << endl << endl;

		//generate all permutations
		while (next_permutation(jobs.begin(), jobs.end()))
		{
			//sum holds the summation of each job permutation for comparison to the current best solution
			sum = 0;
			//zero out the time for the beginning of each job permutation
			time = 0;

			for (iter = jobs.begin();iter != jobs.end(); iter++)
			{
				int index;
				index = *iter - 1;
				time += times[index];

				//calculate the solution
				sum += weights[index] * time;
			}
			//if the sum of the current permutation is better, save it
			if (sum < solution)
			{
				//store new solution
				solution = sum;
				for (int i = 0; i != solution_set.size(); i++)
					solution_set[i] = jobs[i];
			}
		}

		//timer output
		double endTime = (double)(clock() - startTime) / 1000.00;
		cout << "Duration: " << endTime << endl << endl;
		//solution output
		cout << "Solution found!" << endl << endl;
		cout << "The optimal vector is: ";
		for (int i = 0; i != solution_set.size(); i++)
		{
			cout << solution_set[i] << " ";
		}
		cout << endl << "The solution value is: " << solution << endl;
	}

	cout << endl << "Enter a character when finished" << endl;
	char c;
	cin >> c;

	return 0;
}