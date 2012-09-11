#include <MarkovChain.h>

MarkovChain chain;

void testGetFirstStates(){
  Serial.println();
  Serial.println("*** TEST: testGetFirstStates ***");
  char ** sequences;
  sequences = (char **) malloc(3*sizeof(char *));
  for(int i = 0; i < 3; i++)
    sequences[i] = (char *) malloc(3*sizeof(char));
 
  sequences[0][0] = 'a';
  sequences[0][1] = 'b';
  sequences[0][2] = 'c';
  sequences[1][0] = 'a';
  sequences[1][1] = 'b';
  sequences[1][2] = 'c';
  sequences[2][0] = 'b';
  sequences[2][1] = 'b';
  sequences[2][2] = 'c';
    
  char elements [] = {'a', 'b', 'c'};
  int* firstStates = chain.getFirstStates(elements, 3, sequences, 3);
  
  Serial.print("** R1 expected value: 2 actual value: "); 
  Serial.print(firstStates[0]);
  Serial.println();
  Serial.print("** R2 expected value: 1 actual value: ");
  Serial.print(firstStates[1]);
  Serial.println();
  Serial.print("** R3 expected value: 0 actual value: ");  
  Serial.print(firstStates[2]);
  Serial.println();
  
  for(int i = 0; i < 3; i++)
    free(sequences[i]);
  free(sequences);
  free(firstStates);
}

void testCounterTransitionsInSequence(){
  Serial.println();
  Serial.println("*** TEST: testCounterTransitionsInSequence ***");
  char sequence [] = {'a','b','b','c','a','b','\0'};
  int actual = chain.counterTransitionsInSequence('a', 'b', sequence, 6);
  Serial.print("** Expected value: 2, actual: "); 
  Serial.print(actual);
  Serial.println();
  char sequence2 [] = {'a','b','b','c','a','b','\0'};
  int actual2 = chain.counterTransitionsInSequence('b', 'b', sequence2, 6);
  Serial.print("** Expected value: 1, actual: "); 
  Serial.print(actual2);
  Serial.println();

}

void testCountElementsInSequence(){
  Serial.println();
  Serial.println("*** TEST: testCountElementsInSequence ***");
  char sequence [] = {'a','b','b','c','a','b','\0'};
  int actual = chain.countElementsInSequence(sequence);
  Serial.print("** Expected value: 6, actual: "); 
  Serial.print(actual);
  Serial.println();
}

void testCreateTransitionMatrix(){
  Serial.println();
  Serial.println("*** TEST: testCreateTransitionMatrix ***");
  
  char ** sequences;
  sequences = (char **) malloc(3*sizeof(char *));
  for(int i = 0; i < 3; i++)
    sequences[i] = (char *) malloc(5*sizeof(char));
 
  //Sequence 0
  sequences[0][0] = 'a';  
  sequences[0][1] = 'b';  
  sequences[0][2] = 'b';  
  sequences[0][3] = 'b';  
  sequences[0][4] = '\0'; 
  //Sequence 1
  sequences[1][0] = 'b';  
  sequences[1][1] = 'a';  
  sequences[1][2] = 'b';  
  sequences[1][3] = 'a';  
  sequences[1][4] = '\0'; 
  //Sequence 2
  sequences[2][0] = 'a';  
  sequences[2][1] = 'a';  
  sequences[2][2] = 'b';  
  sequences[2][3] = 'a';  
  sequences[2][4] = '\0';  

  char elements [] = {'a', 'b'};
  int** matrix = chain.createTransitionMatrix(elements, 2, sequences, 3);
    
  Serial.print("** Expected value: 1, actual: "); 
  Serial.print(matrix[0][0]);
  Serial.println();
  Serial.print("** Expected value: 3, actual: "); 
  Serial.print(matrix[0][1]);
  Serial.println();
  Serial.print("** Expected value: 3, actual: "); 
  Serial.print(matrix[1][0]);
  Serial.println();
  Serial.print("** Expected value: 2, actual: "); 
  Serial.print(matrix[1][1]);
  Serial.println();
  
  for(int i = 0; i < 3; i++)
    free(sequences[i]);
  free(sequences);
  
  for(int i = 0; i < 2; i++)
    free(matrix[i]);
  free(matrix);
}

void testCountRowsTotals(){
  Serial.println();
  Serial.println("*** TEST: testCountRowsTotals ***");
 
   char ** sequences;
  sequences = (char **) malloc(3*sizeof(char *));
  for(int i = 0; i < 3; i++)
    sequences[i] = (char *) malloc(5*sizeof(char));
 
  //Sequence 0
  sequences[0][0] = 'a';  
  sequences[0][1] = 'b';  
  sequences[0][2] = 'b';  
  sequences[0][3] = 'b';  
  sequences[0][4] = '\0'; 
  //Sequence 1
  sequences[1][0] = 'b';  
  sequences[1][1] = 'a';  
  sequences[1][2] = 'b';  
  sequences[1][3] = 'a';  
  sequences[1][4] = '\0'; 
  //Sequence 2
  sequences[2][0] = 'a';  
  sequences[2][1] = 'a';  
  sequences[2][2] = 'b';  
  sequences[2][3] = 'a';  
  sequences[2][4] = '\0';  

  char elements [] = {'a', 'b'};
  int** matrix = chain.createTransitionMatrix(elements, 2, sequences, 3);
  int* rowsTotals = chain.countRowsTotals(matrix, 2);
  
  Serial.print("** Expected value: 4, actual: "); 
  Serial.print(rowsTotals[0]);
  Serial.println();
  Serial.print("** Expected value: 5, actual: "); 
  Serial.print(rowsTotals[1]);
  Serial.println();
  
  
  for(int i = 0; i < 3; i++)
    free(sequences[i]);
  free(sequences);
  
  for(int i = 0; i < 2; i++)
    free(matrix[i]);
  free(matrix);
  
  free(rowsTotals);
}

void testCreateTransitionProbabilityMatrix(){
  Serial.println();
  Serial.println("*** TEST: testCreateTransitionProbabilityMatrix ***");
 
   char ** sequences;
  sequences = (char **) malloc(3*sizeof(char *));
  for(int i = 0; i < 3; i++)
    sequences[i] = (char *) malloc(5*sizeof(char));
 
  //Sequence 0
  sequences[0][0] = 'a';  
  sequences[0][1] = 'b';  
  sequences[0][2] = 'b';  
  sequences[0][3] = 'b';  
  sequences[0][4] = '\0'; 
  //Sequence 1
  sequences[1][0] = 'b';  
  sequences[1][1] = 'a';  
  sequences[1][2] = 'b';  
  sequences[1][3] = 'a';  
  sequences[1][4] = '\0'; 
  //Sequence 2
  sequences[2][0] = 'a';  
  sequences[2][1] = 'a';  
  sequences[2][2] = 'b';  
  sequences[2][3] = 'a';  
  sequences[2][4] = '\0';  

  char elements [] = {'a', 'b'};
  int** matrix = chain.createTransitionMatrix(elements, 2, sequences, 3);
  int* rowsTotals = chain.countRowsTotals(matrix, 2);
  double** probMatrix = chain.createTransitionProbabilityMatrix(rowsTotals, matrix, 2);
		
  Serial.print("** Expected value: ");
  Serial.print(1.0/4.0);
  Serial.print(" actual: "); 
  Serial.print(probMatrix[0][0]);
  Serial.println();
  Serial.print("** Expected value: ");
  Serial.print(3.0/4.0);
  Serial.print(" actual: "); 
  Serial.print(probMatrix[0][1]);
  Serial.println();
  Serial.print("** Expected value: ");
  Serial.print(3.0/5.0);
  Serial.print(" actual: "); 
  Serial.print(probMatrix[1][0]);
  Serial.println();
  Serial.print("** Expected value: ");
  Serial.print(2.0/5.0);
  Serial.print(" actual: "); 
  Serial.print(probMatrix[1][1]);
  Serial.println();
  
  for(int i = 0; i < 3; i++)
    free(sequences[i]);
  free(sequences);
  
  for(int i = 0; i < 2; i++)
    free(matrix[i]);
  free(matrix);
  
  for(int i = 0; i < 2; i++)
    free(probMatrix[i]);
  free(probMatrix);
  
  free(rowsTotals);
}

void testCalculateFirstStatesProbabilities(){
  Serial.println();
  Serial.println("*** TEST: testCalculateFirstStatesProbabilities ***");
 
   char ** sequences;
  sequences = (char **) malloc(3*sizeof(char *));
  for(int i = 0; i < 3; i++)
    sequences[i] = (char *) malloc(5*sizeof(char));
 
  //Sequence 0
  sequences[0][0] = 'a';  
  sequences[0][1] = 'b';  
  sequences[0][2] = 'b';  
  sequences[0][3] = 'b';  
  sequences[0][4] = '\0'; 
  //Sequence 1
  sequences[1][0] = 'b';  
  sequences[1][1] = 'a';  
  sequences[1][2] = 'b';  
  sequences[1][3] = 'a';  
  sequences[1][4] = '\0'; 
  //Sequence 2
  sequences[2][0] = 'a';  
  sequences[2][1] = 'a';  
  sequences[2][2] = 'b';  
  sequences[2][3] = 'a';  
  sequences[2][4] = '\0';  

  char elements [] = {'a', 'b'};
  double * firstStatesProbs = chain.calculateFirstStatesProbabilities (elements, 2, sequences, 3);

  Serial.print("** Expected value: ");
  Serial.print(2.0/3.0);
  Serial.print(" actual: "); 
  Serial.print(firstStatesProbs[0]);
  Serial.println();
  Serial.print("** Expected value: ");
  Serial.print(1.0/3.0);
  Serial.print(" actual: "); 
  Serial.print(firstStatesProbs[1]);
  Serial.println();
  
  for(int i = 0; i < 3; i++)
    free(sequences[i]);
  free(sequences);
  
  free(firstStatesProbs);
}


void doTests(){
  testGetFirstStates(); 
  testCounterTransitionsInSequence();
  testCountElementsInSequence();
  testCreateTransitionMatrix();
  testCountRowsTotals();
  testCreateTransitionProbabilityMatrix();
  testCalculateFirstStatesProbabilities();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //showMsg();
  doTests();
  delay(10000);
}
