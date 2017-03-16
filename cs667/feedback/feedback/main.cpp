/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Fri Feb 25 13:09:38 EST 2000
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

/*
* This program attempts to teach a perceptron with a single hidden layer
*	the XOR function.  The weights are initialized to random values, and
* adjusted accordingly after each guess.  The hidden layer approach is
* necessary since the XOR function is not linerarly seperable.
*/

/*
* The network in this program does not correctly simulate the XOR function.
* The formulae and methods are all implemented, and the weights and values
* all change at the right times, but the values tend in the wrong direction
* When all is said and done, the outputs that this simulator generates are
* simply wrong.  There is a flaw somewhere in the system, but I don't know
* where to look for it.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DECIMAL double

class term
{
public:
	DECIMAL weight;
	DECIMAL value;
};

const DECIMAL e = 2.718281828;
const DECIMAL learning_rate = 0.3;
const DECIMAL error_range = 0.1;
const int a = 2;

DECIMAL error_energy(DECIMAL error[])
{
	DECIMAL error_sum = 0.0;

	for (int i=0; i<4; i++)
	{
		error_sum += pow( error[i], 2);
	}
	
	return ( error_sum / 4.0 );
}

DECIMAL logistic(const DECIMAL input)
{
	return (1 / ( 1 + pow( e,( -a * input ))));
}

DECIMAL combination(term x1, term x2, term bias)
{
	return ( x1.value * x1.weight + x2.value * x2.weight + bias.weight);		
	// Bias value always 1 - neglect it
}

DECIMAL random_weight(void)
{
	return ( (DECIMAL)( rand() % 200 ) - 100 ) / ((DECIMAL)100);
}

DECIMAL output_delta(const int a, const int desired, const DECIMAL output)
{
 	return ( a * ( desired - output ) * output * ( 1 - output ) );
}

DECIMAL hidden_delta(const int a, const DECIMAL output, const DECIMAL delta, const DECIMAL weight)
{
	return ( a * output * ( 1 - output ) * delta * weight);
}

int main(void)
{
	unsigned seed = time(NULL);
	srand(seed);

	int	input1 = 0, input2 = 0, i, correct_guesses = 0, desired,
			cycles = 0;	
	DECIMAL output[4], combo, error[4],
					y_delta[2],
					x_delta[4],
					b_delta[3];

	term	x[4],	// X are hidden neurons
				y[2],	// Y are output neurons
				b[3];	// B are bias neurons

	for (i=0; i<3; i++)
	{	
  	b[i].value = 1;	// Set the bias values
  	b[i].weight = random_weight();	// And the weights
	}

  for (i=0; i<4; i++)
  {
  	x[i].value = 0;
  	x[i].weight = random_weight();
  }

  for (i=0; i<2; i++)
  {
  	y[i].value = 0;
  	y[i].weight = random_weight();
  }

  // Randomization finished - now we run

  while ((correct_guesses<4) && (cycles<400000))
  // I use an artificial limit here to prevent an infinite loop
	{	
  	combo = combination(x[0], x[1], b[0]);
    y[0].value = logistic(combo);

  	combo = combination(x[2], x[3], b[1]);
    y[1].value = logistic(combo);

    combo = combination(y[0], y[1], b[2]);
  	output[cycles%4] = logistic(combo);
  	
  	desired = (input1 ^ input2);
  	error[cycles%4] =  desired - DECIMAL(output[cycles%4]);
  	
//  	cerr<<"The error was: "<<error<<" "<<input1<<" "<<input2<<endl;
  	
  	if ((error[cycles%4]<error_range) && (error[cycles%4]>-error_range))
  	{
			// We are within a certain error range
// 		cerr<<"Success!  "<<input1<<" xor "<<input2<<" = "<<output[cycles%4]<<endl;
  		correct_guesses++;
  	}  	
  	
  	else
  	{
		correct_guesses = 0;
			// The guess was incorrect

 		// First we change the weights of the output neuron
   		for (i=0; i<2; i++)
   		{
     		// We save the output for later
   			y_delta[i] = output_delta(a, desired, output[cycles%4]);		
   			y[i].weight += learning_rate * y_delta[i] * output[cycles%4];		
   			// Adjust the weight accordingly
   		}
  	
  		// Next we change the weights of the hidden neurons
  		for (i=0; i<4; i++)
  		{
  			x_delta[i] = hidden_delta(a, output[cycles%4], y[i%2].weight, y_delta[i%2]);
  			x[i].weight += learning_rate * x_delta[i] * output[cycles%4];			
  			// Adjust the weight accordingly				
  		}
  		
  		for (i=0; i<2; i++)
  		{
  			b_delta[i] = hidden_delta(a, output[cycles%4], y[i].weight, y_delta[i]);
  			b[i].weight += learning_rate * b_delta[i];
  		}
  			
  		b_delta[2] = output_delta(a, desired, output[cycles%4]);
  		b[2].weight += learning_rate * b_delta[2];
  	}		// END ELSE
  	
  	cycles++;	// We've gone around
  		
  	switch (cycles % 4)
  	{
  		case 0:
  			input1 = 0;
  			input2 = 0;
  			break;
  			
  		case 1:
  			input1 = 0;
  			input2 = 1;
  			break;
  			
  		case 2:
  			input1 = 1;
  			input2 = 0;
  			break;
  				
  		case 3:
  			input1 = 1;
  			input2 = 1;
  			break;
  				
  		default:
  			cerr<<"Shouldn't be here!"<<endl;
  			break;
  				
  	}		// END SWITCH			

  	x[0].value = input1;
  	x[1].value = input2;
  	x[2].value = input1;
  	x[3].value = input2;
				
  }	// END WHILE

  cout<<endl<<"It took "<<cycles/4<<" epochs to adjust the weights."<<endl<<endl;

  cout<<"0 xor 0 is: "<<output[0]<<endl
		  <<"0 xor 1 is: "<<output[1]<<endl
  		<<"1 xor 0 is: "<<output[2]<<endl
  		<<"1 xor 1 is: "<<output[3]<<endl;	

  return EXIT_SUCCESS;
}
