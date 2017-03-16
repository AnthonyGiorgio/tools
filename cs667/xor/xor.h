/*********************************************************
  xor.h
  --------------------------------------------------------
  generated at Wed Mar  8 21:37:34 2000
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int xor(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} xorREC = {2,1,xor};
