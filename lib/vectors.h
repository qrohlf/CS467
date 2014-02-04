#ifndef vectors_h
#define vectors_h

// return the magnitude of vector a
double magnitude(double a[3]);

// return the unit vector of a in b
void unit_vector(double a[3], double b[3]);

// return the result of a x b in c
void cross_product(double a[3], double b[3], double c[3]);

#endif