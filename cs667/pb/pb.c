/*********************************************************
  pb.c
  --------------------------------------------------------
  generated at Mon Apr  3 17:14:56 2000
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

#include <math.h>

#define Act_TanH(sum, bias)         ( tanh(sum + bias) )
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
  static UnitType Units[27];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 1, Units + 2, Units + 3, Units + 4, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, 

  };

  /* Weigths definition section */
  static float Weights[] =  {
-0.408490, 0.050740, -2.573720, 2.639050, 
-0.500930, -2.240130, -0.520940, -2.140930, 
0.709840, 0.585150, -1.887620, 1.170920, 
-0.396460, 1.776920, 0.408110, 2.793740, 
1.153580, -0.699470, 0.431090, 2.335150, 
-0.022120, 1.102040, 2.889200, 1.949210, 
0.047110, 0.572800, -1.083790, 0.075390, 0.787990, 0.953130, 
-0.195740, 0.562890, 0.523540, -1.277930, 0.264650, 0.307220, 
-1.095080, -0.476770, 0.189300, -0.126540, -0.165190, 0.631080, 
1.687750, 0.148210, 2.556840, -0.311370, 0.317130, 0.001160, 
-0.589750, -0.438710, -0.804140, -0.228170, -0.659690, 1.070470, 
1.214480, 0.556180, 1.092960, -0.608120, -0.453360, -0.960630, 
0.309950, -0.331700, -0.222090, -0.966090, -1.507230, -0.382720, 
0.340160, 0.409810, 0.178840, 0.288090, 0.536720, 0.243850, 
0.206800, -0.104290, -0.055510, 0.557720, 0.965270, 0.384500, 
-0.759430, 0.037490, -0.085630, 0.093060, 0.384780, -0.516430, 
0.045580, -0.052100, 0.668060, 0.281010, 0.095370, 0.118180, 
0.149520, -0.255800, 0.808890, 0.555650, 0.369170, 0.257290, 
0.045720, -0.098310, -0.532420, -0.078220, -0.143420, -0.034610, 
-0.102290, 0.395960, -0.054300, -0.146240, -0.353930, -0.174390, 
-0.051770, 0.172490, -0.532700, 0.019360, -0.031630, -0.034090, 
-0.032640, -0.194440, -0.181270, -0.399570, -0.016380, 0.356820, 

  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[27] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (Old: 1) */
      0.0, -0.014720, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (Old: 2) */
      0.0, 0.297140, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (Old: 3) */
      0.0, 0.889890, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (Old: 4) */
      0.0, 1.211460, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (Old: 5) */
      0.0, -1.387610, 4,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (Old: 6) */
      0.0, 1.220270, 4,
       &Sources[4] , 
       &Weights[4] , 
      },
    { /* unit 7 (Old: 7) */
      0.0, 0.278660, 4,
       &Sources[8] , 
       &Weights[8] , 
      },
    { /* unit 8 (Old: 8) */
      0.0, 0.285950, 4,
       &Sources[12] , 
       &Weights[12] , 
      },
    { /* unit 9 (Old: 9) */
      0.0, 0.742260, 4,
       &Sources[16] , 
       &Weights[16] , 
      },
    { /* unit 10 (Old: 10) */
      0.0, 0.215790, 4,
       &Sources[20] , 
       &Weights[20] , 
      },
    { /* unit 11 (Old: 11) */
      0.0, -1.283150, 6,
       &Sources[24] , 
       &Weights[24] , 
      },
    { /* unit 12 (Old: 12) */
      0.0, -2.343050, 6,
       &Sources[30] , 
       &Weights[30] , 
      },
    { /* unit 13 (Old: 13) */
      0.0, 2.362920, 6,
       &Sources[36] , 
       &Weights[36] , 
      },
    { /* unit 14 (Old: 14) */
      0.0, -0.411180, 6,
       &Sources[42] , 
       &Weights[42] , 
      },
    { /* unit 15 (Old: 15) */
      0.0, -0.392650, 6,
       &Sources[48] , 
       &Weights[48] , 
      },
    { /* unit 16 (Old: 16) */
      0.0, 1.039320, 6,
       &Sources[54] , 
       &Weights[54] , 
      },
    { /* unit 17 (Old: 17) */
      0.0, -0.527850, 6,
       &Sources[60] , 
       &Weights[60] , 
      },
    { /* unit 18 (Old: 18) */
      0.0, -0.164640, 6,
       &Sources[66] , 
       &Weights[66] , 
      },
    { /* unit 19 (Old: 19) */
      0.0, -0.510650, 6,
       &Sources[72] , 
       &Weights[72] , 
      },
    { /* unit 20 (Old: 20) */
      0.0, -0.558190, 6,
       &Sources[78] , 
       &Weights[78] , 
      },
    { /* unit 21 (Old: 21) */
      0.0, -1.089590, 6,
       &Sources[84] , 
       &Weights[84] , 
      },
    { /* unit 22 (Old: 22) */
      0.0, -1.330660, 6,
       &Sources[90] , 
       &Weights[90] , 
      },
    { /* unit 23 (Old: 23) */
      0.0, -0.199180, 6,
       &Sources[96] , 
       &Weights[96] , 
      },
    { /* unit 24 (Old: 24) */
      0.0, -0.198060, 6,
       &Sources[102] , 
       &Weights[102] , 
      },
    { /* unit 25 (Old: 25) */
      0.0, 0.059590, 6,
       &Sources[108] , 
       &Weights[108] , 
      },
    { /* unit 26 (Old: 26) */
      0.0, -0.686990, 6,
       &Sources[114] , 
       &Weights[114] , 
      }

  };



int pb(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[4] = {Units + 1, Units + 2, Units + 3, Units + 4}; /* members */

  static pUnit Hidden1[6] = {Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10}; /* members */

  static pUnit Hidden2[6] = {Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16}; /* members */

  static pUnit Output1[10] = {Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26}; /* members */

  static int Output[10] = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

  for(member = 0; member < 4; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 6; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 6; member++) {
    unit = Hidden2[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for (member = 0; member < 10; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_TanH(sum, unit->Bias);
  };

  for(member = 0; member < 10; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
