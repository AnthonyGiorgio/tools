// Anthony Giorgio
//
// This program alters the pattern file for CS667 A4 to fit the

#include <fstream.h>
#include <string.h>

#define STRLEN 25

#define DEBUG 0

void main (void)
{
	ifstream infile;
	ofstream outfile;
	
	char string[STRLEN];

	char temp;

	infile.open("iris_data.txt");
	outfile.open("temp");

	while(!infile.eof())
	{	
		infile.get(temp);
		
		if (temp==',')
			temp=' ';
			
		outfile.put(temp);
	}
	
	infile.close();
	outfile.close();

#if DEBUG >0
	cerr<<"First Pass Complete!"<<endl;
#endif
	
	infile.open("temp");
	outfile.open("iris_fields.txt");
	
	while (!infile.eof())
	{
		infile>>string;
		
		if (strncmp(string, "Iris-setosa", STRLEN)==0)
		{
			(void)strncpy(string,"1 0 0", STRLEN);
			outfile<<string<<"\n";
		}
			
		else if  (strncmp(string, "Iris-versicolor", STRLEN)==0)
		{
			(void)strncpy(string,"0 1 0", STRLEN);
			outfile<<string<<"\n";
		}

			
 		else if  (strncmp(string, "Iris-virginica", STRLEN)==0)
 		{
			(void)strncpy(string,"0 0 1", STRLEN);
			outfile<<string<<"\n";
		}

		else
			outfile<<string<<" ";
	}
	
	infile.close();
	outfile.close();
#if DEBUG >0	
	cerr<<"Second Pass Complete!"<<endl;	
#endif
}