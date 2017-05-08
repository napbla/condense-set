# condense-set
A command line for finding condense set using Euclidean distance

## Setup
### Install
Install.sh will compile condense.cpp and knn.cpp and copy them to bin folder of the project and user's local bin folder.
### Build
Build.sh only build condense.cpp and knn.cpp then copy them to bin folder of the project
### Uninstall
Will remove condense and knn from user's local bin folder

## Usage
### Condense
Condense will print to the standard output the condense set of a dataset using Euclidean distance. This is the original algorithm, not the improved version but was optimized in implementation to be fast.

#### condense -f filename -p classifier position -d delimiter (--debug --hasid)

Option :

  * filename : name of the data set file
  
  * classifier position : the position of the classifier collumn , count from 0 from left to right
  
  * delimiter : delimiter character of the dataset, if it is a space then use -d " "
  
  * --debug : will print debug
  
  * --hasid : use if the dataset has the id number in the first collumn

### KNN
KNN will run knn algorithm on each line of test file then compare with the right answer. In the end, knn will print the percentage that your knn prediction is right. This is for testing but can be modified easily to become a general-purpose knn command.

knn train_filename test_filename delimiter classifier_position k_number debug=0 hasid

Option : 

  * train_filename - path to train dataset file
	
  * test_filename - path to test dataset file
	
  * delimiter - use  if it is a space
	
  * classifier position - the position of the class value, counting from 0 and from left to right
	
  * k_number - k number in knn algorithm
	
  * debug - default is 0, set to 1 to print debug
   
## Dataset

Dataset comes with some bonus bash scripts used to prepare the data.
