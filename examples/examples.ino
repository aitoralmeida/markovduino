#include <MarkovChain.h>

MarkovChain chain;

void usageExample(){
  
  //Training set to create the transition matrix. It has 3 different sequences.  
  char ** trainingSet;
  trainingSet = (char **) malloc(3*sizeof(char *));
  for(int i = 0; i < 3; i++)
    trainingSet[i] = (char *) malloc(5*sizeof(char));
 
  //Sequence 0
  trainingSet[0][0] = 'a';  
  trainingSet[0][1] = 'b';  
  trainingSet[0][2] = 'c';  
  trainingSet[0][3] = 'c';  
  trainingSet[0][4] = '\0'; 
  //Sequence 1
  trainingSet[1][0] = 'a';  
  trainingSet[1][1] = 'a';  
  trainingSet[1][2] = 'a';  
  trainingSet[1][3] = 'a';  
  trainingSet[1][4] = '\0'; 
  //Sequence 2
  trainingSet[2][0] = 'b';  
  trainingSet[2][1] = 'a';  
  trainingSet[2][2] = 'b';  
  trainingSet[2][3] = 'c';  
  trainingSet[2][4] = '\0';  

  // The sequences are composed by three elements: a, b and c
  char elements [] = {'a', 'b', 'c'};
  
  //We calculate the probability of a element apearing after 'a'  
  double* probs = chain.getNextTransitions('a', elements, 3, trainingSet, 3);
  
  Serial.println("Probability of appearing after element /'a/'");
  for (int i = 0; i < 3; i++){
    Serial.print(elements[i] + ": ");
    Serial.print(probs[i]);
    Serial.println();
  }
  
  //We can also calculate the ocurrence probability of a given sequence using the transition matrix
  //and first element probabilities
  char sequence [] = {'a','b','a'};
  double probability = chain.getSequenceProbability(sequence, 3, elements, 3, trainingSet, 3);
  Serial.print("Ocurrence probability of the sequence a-b-a: ");
  Serial.print(probability);
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  usageExample();
}

void loop() {
}
