/*********************************************************
  fisher.c
  --------------------------------------------------------
  generated at Sun Mar 12 15:33:34 2000
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

#include <math.h>

#define Act_Logistic(sum, bias)  ( (sum+bias<10000.0) ? ( 1.0/(1.0 + exp(-sum-bias) ) ) : 0.0 )
#ifndef NULL
#define NULL (void *)0
#endif

typedef struct UT {
          float act;         /* Activation       */
          float Bias;        /* Bias of the Unit */
          int   NoOfSources; /* Number of predecessor units */
   struct UT   **sources; /* predecessor units */
          float *weights; /* weights from predecessor units */
        } UnitType, *pUnit;

  /* Forward Declaration for all unit types */
  static UnitType Units[13];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-10.714110, -27.825939, 25.486219, 20.785660, 
1.287140, 1.244410, 1.074230, 1.807500, 
-1.493560, 18.179079, -1.998020, -47.827671, 
5.816290, -21.207720, -10.626740, 21.305170, 
1.549890, 1.945400, -4.704750, -2.914480, 
-1.251050, -4.091300, -0.036900, -4.885150, 12.632530, 
-10.926130, -0.516810, 9.962090, 9.060570, -16.754101, 
12.259230, -0.888640, -10.016030, -9.184950, -2.544580, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[13] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (Old: 1) */
      0.0, 0.061560, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (Old: 2) */
      0.0, -1.634870, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (Old: 3) */
      0.0, 0.687210, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (Old: 4) */
      0.0, -1.469770, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (Old: 5) */
      0.0, -7.403110, 4,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (Old: 6) */
      0.0, 0.810530, 4,
       &Sources[4] , 
       &Weights[4] , 
      },
    { /* unit 7 (Old: 7) */
      0.0, 50.944241, 4,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 8 (Old: 8) */
      0.0, 28.741751, 4,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 9 (Old: 9) */
      0.0, 0.733910, 4,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 10 (Old: 10) */
      0.0, -2.047080, 5,
       &Sources[20] , 
       &Weights[20] , 
      },
    { /* unit 11 (Old: 11) */
      0.0, 0.845800, 5,
       &Sources[25] , 
       &Weights[25] , 
      },
    { /* unit 12 (Old: 12) */
      0.0, -0.720060, 5,
       &Sources[30] , 
       &Weights[30] , 
      }

  };



int fisher(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[4] = {Units + 1, Units + 2, Units + 3, Units + 4}; /* members */

  static pUnit Hidden1[5] = {Units + 5, Units + 6, Units + 7, Units + 8, Units + 9}; /* members */

  static pUnit Output1[3] = {Units + 10, Units + 11, Units + 12}; /* members */

  static int Output[3] = {10, 11, 12};

  for(member = 0; member < 4; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 5; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 3; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 3; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
