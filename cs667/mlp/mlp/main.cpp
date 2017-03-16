/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Mon Mar 27 22:18:25 EST 2000
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

#include <fstream.h>
#include <stdlib.h>

#define INPUT "pbdata.txt"
#define OUTPUT "pbready.txt"

#define MAX_STRING 6
#define MAX_PATTERNS 1519				// How many speech patterns do we have?
#define MAX_PRONUNCIATIONS 4			// How many different peaks are there?

int average(int frequency[MAX_PATTERNS]);

void remove_mean(int frequency[MAX_PATTERNS]);

int main(void)
{
	char freq_string[MAX_STRING];
	char garbage[MAX_STRING];
	char vowel_string[MAX_STRING];
	
	int vowels[MAX_PATTERNS];
	int frequency[MAX_PRONUNCIATIONS][MAX_PATTERNS];
	
	ifstream infile;
	ofstream outfile;
	
	infile.open(INPUT);
	if (infile.fail())
	{
		cerr<<"Input file not found!"<<endl;
		return 1;
	}
	
	infile >> garbage >> garbage;					// Strip off leading stuff
	
	for (int i=0; !infile.eof(); i++)
	{
		infile >> vowel_string  >> garbage;			// Get vowel
		vowels[i] = atoi(vowel_string);				// Convert to integer and save
		
		for (int j=0; j<MAX_PRONUNCIATIONS; j++)
		{
			infile>>freq_string;					// Get frequency						
			frequency[j][i] = atoi(freq_string);	// Convert to integer and save
		}
		
		infile >> garbage >> garbage;				// Strip off leading stuff
	}	// End while
	
	infile.close();
	
	for (int i=0; i<MAX_PRONUNCIATIONS; i++)
	{
		remove_mean(frequency[i]);
	}
	
	outfile.open(OUTPUT);	
	if (outfile.fail())
	{
		cerr<<"Unable to create output file!"<<endl;
		return 2;
	}
	
	for (int i=0; i<MAX_PATTERNS; i++)
	{
		outfile <<"# Pronunciation "<<i<<endl;		// Add a speech header
		
		for (int j=0; j<MAX_PRONUNCIATIONS; j++)
		{
			outfile<<frequency[j][i]<<" ";			// Place the frequency in the right spot
		}
		
		outfile<<endl<<vowels[i]<<endl;				// Place the vowel in the right spot
	}
	
	outfile.close();
	return 0;
}

int average(int frequency[MAX_PATTERNS])
{
	int sum = 0;
	
	for (int i=0; i<MAX_PATTERNS; i++)
	{
		sum+=frequency[i];
	}

	return (sum / MAX_PATTERNS);	
}

void remove_mean(int frequency[MAX_PATTERNS])
{
	int avg = average(frequency);
	
	for (int i=0; i<MAX_PATTERNS; i++)
	{
		frequency[i] -= avg;
	}
	
	return;
}