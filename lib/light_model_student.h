#include <math.h>

// Globals from light model
extern double light_in_eye_space[3] ;
extern double AMBIENT;
extern double MAX_DIFFUSE;
extern double SPECPOW;

void nu_light_model (double irgb[3],
                     double s[3],
                     double p[3],
                     double n[3],
                     double argb[3]);




