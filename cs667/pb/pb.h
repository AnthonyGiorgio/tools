/*********************************************************
  pb.h
  --------------------------------------------------------
  generated at Mon Apr  3 17:14:56 2000
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int pb(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} pbREC = {4,10,pb};
