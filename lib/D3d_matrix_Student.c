
#include <D3d_matrix.h>



/*

 ( x')          (x)
 ( y')  =   M * (y)
 ( z')          (z)  
 ( 1 )          (1)

instead of (x',y',z',1) = (x,y,z,1) * M  

*/




int D3d_print_mat (double a[4][4])
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           printf(" %12.4lf ",a[r][c]) ;
      }
      printf("\n") ;
  }

  return 1 ;
} 




int D3d_copy_mat (double a[4][4], double b[4][4])
// a = b
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           a[r][c] = b[r][c] ;
      }
  }

  return 1 ;
} 




int D3d_mat_mult (double res[4][4], double a[4][4], double b[4][4])
// res = a * b
// this is SAFE, i.e. the user can make a call such as 
// D3d_mat_mult(p,  p,q) or D3d_mat_mult(p,  q,p) or  D3d_mat_mult(p, p,p)
{
  double sum ;
  int k ;
  int r,c ;
  double tmp[4][4] ;

  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           sum = 0.0 ;
           for (k = 0 ; k < 4 ; k++) {
                 sum = sum + a[r][k]*b[k][c] ;
           }
           tmp[r][c] = sum ;
      }
  }

  D3d_copy_mat (res, tmp) ;

  return 1 ;
}





int D3d_make_identity (double a[4][4])
// a = I
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           if (r == c) a[r][c] = 1.0 ;
               else    a[r][c] = 0.0 ;
      }
  }

  return 1 ;
} 








/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


int D3d_translate (double a[4][4], double b[4][4], 
                   double dx, double dy, double dz)
// a = translation*a  
// b = b*translation_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;

  t[0][3] =  dx ;  t[1][3] =  dy ;  t[2][3] =  dz ;  
  D3d_mat_mult(a,  t,a) ;

  t[0][3] = -dx ;  t[1][3] = -dy ;  t[2][3] = -dz ;  
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}


int D3d_scale (double a[4][4], double b[4][4],
               double sx, double sy, double sz)
// a = scale*a  
// b = b*scale_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;

  t[0][0] = sx ;  t[1][1] = sy;  t[2][2] = sz; 
  D3d_mat_mult(a,  t,a) ;

  if ((sx == 0) || (sy == 0) || (sz == 0)) { return 0 ; }

  t[0][0] = 1/sx ;  t[1][1] = 1/sy ;  t[2][2] = 1/sz; 
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}



int D3d_rotate_x (double a[4][4], double b[4][4], double radians)
// a = rotate*a  
// b = b*rotate_inverse  
{
  double t[4][4] ;
  double cs,sn ;

  cs =  cos( radians ) ;
  sn =  sin( radians ) ;

  D3d_make_identity(t) ;

  t[1][1] =   cs ;  t[1][2] = -sn ;
  t[2][1] =   sn ;  t[2][2] =  cs ;
  D3d_mat_mult(a,  t,a) ;

  t[1][1] =   cs ;  t[1][2] =  sn ;
  t[2][1] =  -sn ;  t[2][2] =  cs ;
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}



int D3d_rotate_y (double a[4][4], double b[4][4], double radians)
// a = rotate*a  
// b = b*rotate_inverse  
{
  double t[4][4] ;
  double cs,sn ;

  cs =  cos( radians ) ;
  sn =  sin( radians ) ;

  D3d_make_identity(t) ;

  t[0][0] =   cs ;  t[0][2] =  sn ;
  t[2][0] =  -sn ;  t[2][2] =  cs ;
  D3d_mat_mult(a,  t,a) ;

  t[0][0] =   cs ;  t[0][2] = -sn ;
  t[2][0] =   sn ;  t[2][2] =  cs ;
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}



int D3d_rotate_z (double a[4][4], double b[4][4], double radians)
// a = rotate*a  
// b = b*rotate_inverse  
{
  double t[4][4] ;
  double cs,sn ;

  cs =  cos( radians ) ;
  sn =  sin( radians ) ;

  D3d_make_identity(t) ;

  t[0][0] =   cs ;  t[0][1] = -sn ;
  t[1][0] =   sn ;  t[1][1] =  cs ;
  D3d_mat_mult(a,  t,a) ;

  t[0][0] =   cs ;  t[0][1] =  sn ;
  t[1][0] =  -sn ;  t[1][1] =  cs ;
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}





int D3d_cs_rotate_x (double a[4][4], double b[4][4], double cs, double sn)
// a = rotate*a  
// b = b*rotate_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;

  t[1][1] =   cs ;  t[1][2] = -sn ;
  t[2][1] =   sn ;  t[2][2] =  cs ;
  D3d_mat_mult(a,  t,a) ;

  t[1][1] =   cs ;  t[1][2] =  sn ;
  t[2][1] =  -sn ;  t[2][2] =  cs ;
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}



int D3d_cs_rotate_y (double a[4][4], double b[4][4], double cs, double sn)
// a = rotate*a  
// b = b*rotate_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;

  t[0][0] =   cs ;  t[0][2] =  sn ;
  t[2][0] =  -sn ;  t[2][2] =  cs ;
  D3d_mat_mult(a,  t,a) ;

  t[0][0] =   cs ;  t[0][2] = -sn ;
  t[2][0] =   sn ;  t[2][2] =  cs ;
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}



int D3d_cs_rotate_z (double a[4][4], double b[4][4], double cs, double sn)
// a = rotate*a  
// b = b*rotate_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;

  t[0][0] =   cs ;  t[0][1] = -sn ;
  t[1][0] =   sn ;  t[1][1] =  cs ;
  D3d_mat_mult(a,  t,a) ;

  t[0][0] =   cs ;  t[0][1] =  sn ;
  t[1][0] =  -sn ;  t[1][1] =  cs ;
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}





int D3d_negate_x (double a[4][4], double b[4][4])
// negate the x....reflects in the yz-plane
// a = reflect*a 
// b = b*reflect_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;
  t[0][0] =   -1 ;
  D3d_mat_mult(a,  t,a) ;

  // the transformation, t, is its own inverse
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}



int D3d_negate_y (double a[4][4], double b[4][4])
// negate the y....reflects in the xz-plane
// a = reflect*a 
// b = b*reflect_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;
  t[1][1] =   -1 ;
  D3d_mat_mult(a,  t,a) ;

  // the transformation, t, is its own inverse
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}


int D3d_negate_z (double a[4][4], double b[4][4])
// negate the z....reflects in the xy-plane
// a = reflect*a 
// b = b*reflect_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;
  t[2][2] =   -1 ;
  D3d_mat_mult(a,  t,a) ;

  // the transformation, t, is its own inverse
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}




int D3d_mat_mult_points (double *X, double *Y, double *Z,
                         double m[4][4],
                         double *x, double *y, double *z, int numpoints)
// |X0 X1 X2 ...|       |x0 x1 x2 ...|
// |Y0 Y1 Y2 ...| = m * |y0 y1 y2 ...|
// |Z0 Z1 Z2 ...|       |z0 z1 z2 ...|
// | 1  1  1 ...|       | 1  1  1 ...|

// SAFE, user may make a call like D3d_mat_mult_points (x,y,z, m, x,y,z, n) ;
{
  double u,v,w ;
  int i ;

  for (i = 0 ; i < numpoints ; i++) {
    u = m[0][0]*x[i] + m[0][1]*y[i] + m[0][2]*z[i] + m[0][3] ;
    v = m[1][0]*x[i] + m[1][1]*y[i] + m[1][2]*z[i] + m[1][3] ;
    w = m[2][0]*x[i] + m[2][1]*y[i] + m[2][2]*z[i] + m[2][3] ;

    X[i] = u ;
    Y[i] = v ;
    Z[i] = w ;
  }

  return 1 ;
}



