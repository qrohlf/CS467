
#include <D3d_matrix.h>


int main()
{
  double A[3],B[3],C[3],P[3] ;

  A[0] =  0.0 ;   A[1] =  0.0 ;   A[2] =  0.0 ; 
  B[0] =  0.0 ;   B[1] =  0.0 ;   B[2] = 20.0 ; 
  C[0] =  0.0 ;   C[1] = 10.0 ;   C[2] =  4.0 ; 


  P[0] = 17.0 ;   P[1] =  5.0 ;   P[2] =  8.0 ; 
  // distance from P to triangle ABC is 17

  printf("The original points are :\n") ;
  printf("%12.4lf %12.4lf %12.4lf\n",A[0],A[1],A[2]) ;
  printf("%12.4lf %12.4lf %12.4lf\n",B[0],B[1],B[2]) ;
  printf("%12.4lf %12.4lf %12.4lf\n",C[0],C[1],C[2]) ;
  printf("%12.4lf %12.4lf %12.4lf\n",P[0],P[1],P[2]) ;

  int n ;
  int tlist[100] ;
  double plist[100] ;
  double m[4][4], minv[4][4], mm[4][4] ;

  n = 0 ;
  tlist[n] = TX ; plist[n] = 100 ; n++ ;
  tlist[n] = TZ ; plist[n] =  75 ; n++ ;
  tlist[n] = RY ; plist[n] =  30 ; n++ ; // degrees
  tlist[n] = RZ ; plist[n] = -50 ; n++ ; // degrees
  tlist[n] = TY ; plist[n] = -10 ; n++ ; 

  D3d_make_movement_sequence_matrix(m,minv, n,tlist,plist) ;

  printf("m =\n") ;
  D3d_print_mat(m) ;

  printf("minv =\n") ;
  D3d_print_mat(minv) ;

  D3d_mat_mult(mm,   m,minv) ;
  printf("m * minv = \n") ;
  D3d_print_mat(mm) ;



  D3d_mat_mult_pt(A, m,A) ;
  D3d_mat_mult_pt(B, m,B) ;
  D3d_mat_mult_pt(C, m,C) ;
  D3d_mat_mult_pt(P, m,P) ;

  printf("The transformed points are :\n") ;
  printf("%12.4lf %12.4lf %12.4lf\n",A[0],A[1],A[2]) ;
  printf("%12.4lf %12.4lf %12.4lf\n",B[0],B[1],B[2]) ;
  printf("%12.4lf %12.4lf %12.4lf\n",C[0],C[1],C[2]) ;
  printf("%12.4lf %12.4lf %12.4lf\n",P[0],P[1],P[2]) ;

  // now find the distance from the new P to new triangle ABC
  // it should still be 17 since this transformation preserved
  // distances

  // method # 1.
  double AB[3],AC[3],AP[3],N[3] ;

  AB[0] = B[0] - A[0] ; AB[1] = B[1] - A[1] ; AB[2] = B[2] - A[2] ; 
  AC[0] = C[0] - A[0] ; AC[1] = C[1] - A[1] ; AC[2] = C[2] - A[2] ; 
  AP[0] = P[0] - A[0] ; AP[1] = P[1] - A[1] ; AP[2] = P[2] - A[2] ; 

  D3d_x_product (N, AB,AC) ;
  // N[0] *= -1 ; N[1] *= -1 ; N[2] *= -1 ; 
  // irrelevant here because of use of fabs below


  printf("N = AB x AC =\n") ;
  printf("%12.4lf %12.4lf %12.4lf\n",N[0],N[1],N[2]) ;

  // now distance / |AP| = cos(t)
  // where t is the ACUTE angle formed by AP and N
  // and furthermore,   cos(t) = fabs(AP . N) / (|AP| * |N|)
  // so distance = fabs(AP. N) / |N|

  double Nlen, distance ;
  Nlen = sqrt(N[0]*N[0] + N[1]*N[1] + N[2]*N[2]) ;
  distance = fabs(AP[0]*N[0] + AP[1]*N[1] + AP[2]*N[2]) / Nlen ;
  printf("distance = %12.4lf\n",distance) ;


  // method # 2.
  // create the view matrix with eye at A
  // coi at B, and up at C
  // then multiply P by the view matrix...the
  // fabs of the x-coordinate should be the distance

  double view[4][4], view_inv[4][4], vv[4][4], Q[3] ;
  D3d_view( view, view_inv,  A,B,C) ;

  printf("view = \n") ;
  D3d_print_mat(view) ;

  printf("view_inv = \n") ;
  D3d_print_mat(view_inv) ;

  D3d_mat_mult(vv,   view,view_inv) ;
  printf("view * view_inv = \n") ;
  D3d_print_mat(vv) ;




  D3d_mat_mult_pt(Q, view, P) ;
  printf("distance = fabs(Q[0]) = %12.4lf\n",fabs(Q[0])) ;


}
