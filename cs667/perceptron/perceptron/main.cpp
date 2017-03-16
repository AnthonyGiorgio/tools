/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Feb  9 22:24:43 EST 2000
    copyright            : (C) 2000 by Anthony Giorgio
    email                : agiorg01@longisland.poly.edu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/***************************************************************************
 This program reads in letters from a data file and stores them into an array
 It then uses the letters to train a perceptron to visually recognize
 indivudual letters.
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fstream.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>       												//system timer for seed
#include <math.h>


#define INPUT_FILE "letters.txt"
#define ARRAY_MAX 36
#define ALPHABET 26

// BEGIN PERCEPTRON CLASS
class perceptron
{
public:
	float weight[ARRAY_MAX];
	int value[ARRAY_MAX];
	int desired, actual;	
};
// END PERCEPTRON CLASS


// BEGIN GRID CLASS
class grid
{
public:
	char letter;
	int matrix[ARRAY_MAX];
};
// END GRID CLASS


// BEGIN FUNCTION PROTOTYPES
int clean_array(grid letterbase[], perceptron net[]);

int open_file(ifstream& infile);

int read_data(ifstream& infile, grid letterbase[], int noise);

float get_learning_rate(void);

int train(perceptron& p, const grid letterbase[], const float learning_rate, char desired_letter);

int copy_letter(perceptron& percept, grid letterbase);

int sgn(const float input);

float calc_weight_delta(const float learning_rate, perceptron& percept, const int index);

int calc_actual(perceptron percept);

int calc_percept_weights(const float learning_rate, perceptron& percept);

int get_noise(void);

int corrupt(perceptron& percept, const float learning_rate, const int noise);
// END FUNCTION PROTOTYPES

int main(int argc, char *argv[])
{
	perceptron net[ALPHABET];												// The neural net
	grid letterbase[ALPHABET];											// Used to hold the letter templates
	float learning_rate=0.0;												// How fast do we learn?
	ifstream infile;																// Our data file
	int total_cycles=0;															// How many cycles through the data
	int noise=0;																		// How noisy is it?
	
  unsigned seed=time(NULL);												// Randomize timer
  srand(seed);

	(void) clean_array(letterbase, net);						// Initialize arrays

	if (open_file(infile)==EXIT_FAILURE)						// Open file for reading
	{
		cerr<<"Quitting!"<<endl;											// If no input file, quit
		return EXIT_FAILURE;
	}
	
	if (argc==1)
		learning_rate=get_learning_rate();						// Set learning rate
	else
		learning_rate=atof(argv[1]);									// Get from command line
		
	if (argc<=2)
		noise=get_noise();														// Set noise level
	else
		noise=atoi(argv[2]);													// Get from command line
		
	(void) read_data(infile, letterbase, noise);		// Retrieve data from disk
		
	for (char desired_letter='a'; desired_letter<='z'; desired_letter++)
	{
		total_cycles += train(net[desired_letter-'a'], letterbase, learning_rate, desired_letter);
																									// Train perceptrons
	}

	cout<<endl<<"It took "<<total_cycles<<" cycles to train the network"<<endl;

	(void) copy_letter(net[0], letterbase[0]);			// Fetch A image
	
	if (corrupt(net[0],learning_rate, noise)==1)
		cout<<"Noise successfully filtered!"<<endl;
	else
		cout<<"Noise NOT filtered"<<endl;
	
  return EXIT_SUCCESS;														// All done!
}


// This function simply cleans and initializes the arrays
int clean_array(grid letterbase[], perceptron net[])
{
	for (int i=0; i<ALPHABET; i++)									// Clean out the template array
	{
		letterbase[i].letter='a'+i;
		for (int j=0; j<ARRAY_MAX; j++)
		{
			letterbase[i].matrix[j]=0;
			
	  	net[i].value[j]=0;													// Clear the neurons
	  	net[i].weight[j]=0.0;
		}
	
  net[i].value[0]=1;															// Set bias value
 	}

	return EXIT_SUCCESS;
}


// This function opens a file from disk as specified by the INPUT_FILE macro
int open_file(ifstream& infile)
{
  infile.open(INPUT_FILE);
	
	if (infile.fail())
	{
		cerr<<INPUT_FILE<<" not found!"<<endl;				// No input file!
		return EXIT_FAILURE;
	}
	
	else
	{
		return EXIT_SUCCESS;                       		// We're OK!
	}
}


// This function fetches all the letter data from an external file and stores it in an array
int read_data(ifstream& infile, grid letterbase[], int noise)
{
	char current='\0';															// current buffer character

 for (int i=0; i<2*ALPHABET; i++)									// Start parsing the input file	
 {	
		current=infile.peek();
 	
 	// Strip off the trailing space at the end of a line and any errant newlines
  	while (current==' ' || current=='\n')
  	{
  		current=infile.get();										 		// Pull off the next char
  		current=infile.peek(); 						 					// Peek at the one after (non-destructive)
 		}
  	
  	if (current=='#')														 	// Are we a comment?
  	{
  		do
  		{
  			current=infile.get();								 			// If so, skip current line
  		}
  		while (current!='\n');										 	// Repeat until end of line
  	}

  	else
  	{
  		for (int j=1; j<ARRAY_MAX; j++)
  		{
  			infile>>letterbase[i/2].matrix[j]; 				// Store data
   		}		
  	}

	}
	infile.close();																	// Clean up
	
	// At this point we should have a complete listing of the alphabet

	return EXIT_SUCCESS;
}


// Here we get the learning rate for the perceptron from the user
float get_learning_rate(void)
{
	float l=0.0;
	
	while ( l <= 0.0 || l >= 1.0 )
	{
  	cout<<"Enter the learning rate: (0 < rate < 1): ";
  	cin>>l;
  	cout<<endl;
	}

	return l;
}


// This is the main perceptron training function
// This is the heart of the program
int train(perceptron& percept, const grid letterbase[], const float learning_rate, char desired_letter)
{

	bool training_complete=false;
	int training_cycle=0, cycle_step=0, correct_guesses=0;

	while (!training_complete)
	{
		for (cycle_step=0; cycle_step < ALPHABET; cycle_step++)
		{
			(void) copy_letter(percept, letterbase[cycle_step]);
																									// Grab letter from template
			percept.actual = calc_actual(percept);
			
			if (letterbase[cycle_step].letter == desired_letter)
				percept.desired=1;				
			else
				percept.desired=0;
			
			if (percept.desired==percept.actual)
			{
				correct_guesses++;												// Training complete!
			}

			else
			{
				correct_guesses=0;                        // We need more training!
				(void) calc_percept_weights(learning_rate, percept);
																									// Adjust weights becaue we screwed up
			}
    }
		cycle_step=0;																	// We finished one cycle of the alphabet
		training_cycle++;

		if (correct_guesses>=ALPHABET)								// We've checked the whole alphabet
			training_complete=true;											// So we're done!
	}
	
	cout<<(char)toupper(desired_letter)<<": "<<training_cycle<<endl;
	
	return training_cycle;
}


// Copies a letter from the letter template to a given perceptron
int copy_letter(perceptron& percept, grid letterbase)
{
	for (int i=1; i<ARRAY_MAX; i++)									// We start at one due to bias
		percept.value[i]=letterbase.matrix[i];				// Set up perceptron values

	return EXIT_SUCCESS;
}


// Calculates the signum function
int sgn(const float input)
{
	if (input > 0)
		return 1;
		
	else
		return 0;
}


// Calculates projected delta for a perceptron weight
float calc_weight_delta(const float learning_rate, perceptron& percept, const int index)
{
	return (learning_rate * ( (float)percept.desired - (float)percept.actual) * (float)percept.value[index] );
}


// Calculates desired return
int calc_actual(perceptron percept)
{
	float sum=0.0, weight=0.0;
	int value=0;
	
	weight = percept.weight[0];
	value = percept.value[0];
	
	for (int i=1; i<ARRAY_MAX; i++)
	{
		sum += (weight*(float)value);		// Find the sum
		
		weight = percept.weight[i];
		value = percept.value[i];
	}
	
	return sgn(sum);																			// We return either a 1 or 0
}


// Calculates and maked adjustments to perceptron weights
int calc_percept_weights(const float learning_rate, perceptron& percept)
{
 	for (int j=0; j<ARRAY_MAX; j++)
 	{																													
 		percept.weight[j] += calc_weight_delta(learning_rate, percept, j);
			 																									// Calculate the weight and modify
																												// The perceptron's corresponding weight
	}
	
	return EXIT_SUCCESS;
}


// This function prompts the user for the amount of noise that they want
int get_noise(void)
{
	int noise=0;
	
	while (noise<1 || noise>6)
	{
  	cout<<"What level of noise do you want?"<<endl
  			<<"\t1)\t0.0%"<<endl
  			<<"\t2)\t0.5%"<<endl
  			<<"\t3)\t1.0%"<<endl
  			<<"\t4)\t5.0%"<<endl
  			<<"\t5)\t10%"<<endl
  			<<"\t6)\t25%"<<endl
 				<<">";
		cin>>noise;
  }

	switch (noise)
	{
   case 1:
   	noise=0;
   	break;
   	
   case 2:
   	noise=200;
   	break;
   	
   case 3:
   	noise=100;
   	break;
   	
   case 4:
   	noise=20;
   	break;

   case 5:
  		noise=10;
  		break;
  		
  	case 6:
  		noise=4;
  		break;
  		
  	default:
  		noise=0;
  }
			
	return noise;
}


// This function corrupts a letter image
int corrupt(perceptron& percept, const float learning_rate, const int noise)
{
 	if (noise!=0)																													// No noise means do nothing here
 	{
 		for (int j=1; j<ARRAY_MAX; j++)
 		{
  		if (int(rand() % noise)==1)																				// Generate random noise
  		{
  			if (percept.value[j]==1)														// Invert data
  				percept.value[j]=0;
  			else if	(percept.value[j]==0)
  				percept.value[j]=1;
  			else
  			{
  				cerr<<"We shouln't be here!"<<endl;
  				exit(1);
  			}
  		}
  	}
 	}
  	
 	float sum=0.0, weight=0.0;
	int value=0;
	
	weight = percept.weight[0];
	value = percept.value[0];
	
	for (int i=1; i<ARRAY_MAX; i++)
	{
		sum += (weight*(float)value);		// Find the sum
		
		weight = percept.weight[i];
		value = percept.value[i];
	}
	
	return sgn(sum);																			// We return either a 1 or 0
 	
//percept 	return calc_actual(percept);
}