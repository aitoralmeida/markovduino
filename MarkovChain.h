/*
  MarkovChain.h - Library for using Markov Chains in Arduino
*/
#ifndef MarkovChain_h
#define MarkovChain_h

#include "Arduino.h"

class MarkovChain
{
  public:
	int* getFirstStates(char* elements, int numOfElements, char** sequences, int rows);
	int counterTransitionsInSequence(char expectedFrom, char expectedTo, char sequence [], int numOfElements);
	int countElementsInSequence(char * sequence);
	int** createTransitionMatrix(char elements [], int numOfElements, char ** sequences, int numSequences);
	int* countRowsTotals(int** transitionMatrix, int numOfElements);
	double** createTransitionProbabilityMatrix(int* rowsTotals, int** transitionMatrix, int numOfElements);
	double * calculateFirstStatesProbabilities (char* elements, int numOfElements, char** sequences, int numOfSecuences);
	
	//******************************************************************************************
	//******* Only the following functions are needed to be called to use Markov Chains ********
	//******************************************************************************************
	double* getNextTransitions(char element, char* elements, int numOfElements, char ** sequences, int numSequences );
};

#endif