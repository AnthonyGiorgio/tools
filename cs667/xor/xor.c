/*********************************************************
  xor.c
  --------------------------------------------------------
  generated at Wed Mar  8 21:37:34 2000
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

#include <math.h>

#define Act_Logistic(sum, bias)  ( (sum+bias<10000.0) ? ( 1.0/(1.0 + exp(-sum-bias) ) ) : 0.0 )
#define NULL (void *)0

typedef struct UT {
          float act;         /* Activation       */
          float Bias;        /* Bias of the Unit */
          int   NoOfSources; /* Number of predecessor units */
   struct UT   **sources; /* predecessor units */
          float *weights; /* weights from predecessor units */
        } UnitType, *pUnit;

  /* Forward Declaration for all unit types */
  static UnitType Units[6];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, 
Units + 1, Units + 2, 
Units + 3, Units + 4, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-6.946080, 3.753360, 
-6.631810, -3.114600, 
5.105400, -4.934060, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[6] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (Old: 1) */
      0.0, 1.037460, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (Old: 2) */
      0.0, 0.507340, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (Old: 3) */
      0.0, -2.911510, 2,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (Old: 4) */
      0.0, 0.676990, 2,
       &Sources[2] , 
       &Weights[2] , 
      },
    { /* unit 5 (Old: 5) */
      0.0, -0.015450, 2,
       &Sources[4] , 
       &Weights[4] , 
      }

  };



int xor(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[2] = {Units + 1, Units + 2}; /* members */

  static pUnit Hidden1[2] = {Units + 3, Units + 4}; /* members */

  static pUnit Output1[1] = {Units + 5}; /* members */

  static int Output[1] = {5};

  for(member = 0; member < 2; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 2; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 1; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 1; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
