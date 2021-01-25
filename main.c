


#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "NQueensChecker.h"


candidateSolution workingCandidate;
candidateList  currentListOfCandidates; 
candidateList listOfExaminedCandidates; 



int main(int argc, char* argv[]) {
	int numberOfCompleteSolutionsFound = 0; //simple flag to let us know whether we have stopped
	int numberOfSolutionsExamined = 0; //simple counter
	int indexOfSolutionWeAreLookingAt; //index in list of current solution being examined
	int newLength, valueToAdd; // used when we extend the working candidate
	

	
	CleanListsOfSolutionsToStart();
	CleanWorkingCandidate();
	
	valueToAdd = 0;
	if (argc == 2)
	{
		valueToAdd = atoi(argv[1]);
		if (valueToAdd >= N || valueToAdd < 0)
			PrintThisMessageAndExit("Invalid Input");
	}


	AddQueenToNextRowInColumn(valueToAdd);
	CalculateNumberOfVulnerableQueensForWorkingCandidate(); //should return zero because there is only one queen:)
	numberOfSolutionsExamined = 1;

	//and we can put this as our first item in the list to start the process
	AddWorkingCandidateToCurrentList();

	//Now we will go into a loop examining solutions until we find one that is full and has no vulnerable queens

	while (numberOfCompleteSolutionsFound == 0)
	{
		indexOfSolutionWeAreLookingAt = currentListOfCandidates.indexOfLastEntryAdded;
		
		//Copy thwe solution into working candidate
		CopySolutionFromCurrentListIntoWorkingCandidate(indexOfSolutionWeAreLookingAt);
		
		//recmove it out of the open list so it's no longer reconsidered
		RemoveSolutionFromCurrentList(indexOfSolutionWeAreLookingAt);
		
		//This shows the progress of what is happening
		printf("Next solution to be examined was at index %d \n", indexOfSolutionWeAreLookingAt);
		
		PrintWorkingCandidate();

		numberOfSolutionsExamined++;

		//Calls the function to find out how many queens are vulnerable
		CalculateNumberOfVulnerableQueensForWorkingCandidate();

		if ((workingCandidate.numberOfDefinedValues == N)
			&& (workingCandidate.score == 0))
		{
			numberOfCompleteSolutionsFound++;

			//This prints the result if it is found
			printf("\n found a valid solution after %d candidates\n", numberOfSolutionsExamined);
		}
		else // if the result is not found it continues searching
		{
			if (workingCandidate.score > 0)
			{
				;
			}
			else
			{
				AddQueenToNextRowInColumn(0);
				newLength = workingCandidate.numberOfDefinedValues - 1;

				for (valueToAdd = 0; valueToAdd < N; valueToAdd++)
				{
					MoveQueenInRowToNewCol(newLength, valueToAdd);

					AddWorkingCandidateToCurrentList();					
				}				
			}
		}
	}
	PrintFinalSolutionAndExit();
	return 0;
}
	

	
		

