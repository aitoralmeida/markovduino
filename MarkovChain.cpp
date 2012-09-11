/*
  MarkovChain.cpp - Library for using Markov Chains in Arduino.
*/

#include "Arduino.h"
#include "MarkovChain.h"

int* MarkovChain::getFirstStates(char* elements, int numOfElements, char** sequences, int rows){
  int* firstStates = (int *)malloc(numOfElements*sizeof(int));

  
  for(int iElement = 0; iElement < numOfElements; iElement++){
    int count = 0;
    char element = elements[iElement];
    for(int iSequence = 0; iSequence < rows; iSequence++){
      char firstElement = sequences[iSequence][0];
      if (firstElement == element){
        count++;  
      }
    }
    firstStates[iElement] = count;
  }
  return firstStates;
}

int MarkovChain::counterTransitionsInSequence(char expectedFrom, char expectedTo, char sequence [], int numOfElements){
  int count = 0;
  for (int i = 0; i < numOfElements; i++) {
    char actualFrom = sequence[i];
    char actualTo = sequence[i + 1];	
    if((actualFrom == expectedFrom) && (actualTo == expectedTo))
      count++;
    }
    return count;
}

int MarkovChain::countElementsInSequence(char * sequence){
  int count = -1;
  char current = '1';
  while(current != '\0'){
    count++;
    current = sequence[count];
  }
  return count;
}


int** MarkovChain::createTransitionMatrix(char elements [], int numOfElements, char ** sequences, int numSequences){
  //The number of rows and columns of the transition matrix always equals
  //to the number of distinc elements
  int** matrix;
  matrix = (int **) malloc(numOfElements*sizeof(int *));
  for(int i = 0; i < numOfElements; i++)
    matrix[i] = (int *) malloc(numOfElements*sizeof(int));
    
  int row = 0;
  int col = 0;
  int count = 0;
  for(int iFrom = 0; iFrom < numOfElements; iFrom++){		
    for (int iTo = 0; iTo < numOfElements; iTo++){
      for(int iSequences = 0; iSequences < numSequences; iSequences++){
        char from = elements[iFrom];	
        char to = elements[iTo];
        char* sequence  = sequences[iSequences];
        int num = countElementsInSequence(sequence);
        count = count + counterTransitionsInSequence(from, to, sequence,num);
      }
      matrix[row][col] =  count;
      count = 0;
      col++;
    }
    row++;
    col = 0;			
  }
  return matrix;
}

int* MarkovChain::countRowsTotals(int** transitionMatrix, int numOfElements){
  int* totals = (int *)malloc(numOfElements*sizeof(int));
  for(int i = 0; i < numOfElements; ++i){
    totals[i] = 0;
  }
    	
  for(int i = 0; i < numOfElements; ++i){
    for (int j = 0; j < numOfElements; ++j){
      totals[i] = totals[i] + transitionMatrix[i][j];
    }			
  }  
  return totals;	
}

double** MarkovChain::createTransitionProbabilityMatrix(int* rowsTotals, int** transitionMatrix, int numOfElements){	
  double** probMatrix;
  probMatrix = (double **) malloc(numOfElements*sizeof(double *));
  for(int i = 0; i < numOfElements; i++)
    probMatrix[i] = (double *) malloc(numOfElements*sizeof(double));
    
  for (int i = 0; i < numOfElements; i++) {
    for (int j = 0; j < numOfElements; j++) {
      probMatrix[i][j] = (double)transitionMatrix[i][j] / (double)rowsTotals[i];				
    }			
  }
  
  return probMatrix;
}

//the returning array has the state probabilities in the same order as the "elements" array
double * MarkovChain::calculateFirstStatesProbabilities (char* elements, int numOfElements, char** sequences, int numOfSecuences){
  double * firstStateProbs = (double *)malloc(numOfElements*sizeof(double));
  int* firstStates = getFirstStates(elements, numOfElements, sequences, numOfSecuences);
  int total = 0;
  for(int i = 0; i < numOfElements; i++){
    total = total + firstStates[i];
  }
 
  for(int i = 0; i < numOfElements; i++){
    firstStateProbs[i] = (double)firstStates[i] / (double)total;
  }

  return firstStateProbs;
}

