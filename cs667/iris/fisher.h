/*********************************************************
  fisher.h
  --------------------------------------------------------
  generated at Sun Mar 12 15:33:34 2000
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int fisher(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} fisherREC = {4,3,fisher};
