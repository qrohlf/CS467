#include <FPT.h>

int main (int argc, char **argv)
{
  int w,h,nrows, ncols ;
  double r[2],g[2],b[2] ;
  int i,j,k,q ;
  double dx,dy ;

  if (argc != 12) {
    printf("Usage : pgm  xwd_res_file_name  width height nrows ncols r0 g0 b0 r1 g1 b1\n") ;
    exit(0) ;
  }
  
  w = atoi(argv[2]) ;
  h = atoi(argv[3]) ;
  nrows = atoi(argv[4]) ;
  ncols = atoi(argv[5]) ;
  r[0] = atof(argv[6]) ;
  g[0] = atof(argv[7]) ;
  b[0] = atof(argv[8]) ;

  r[1] = atof(argv[9]) ;
  g[1] = atof(argv[10]) ;
  b[1] = atof(argv[11]) ;


  G_init_graphics(w,h) ;
  G_rgb(0,1,0) ;
  G_clear() ; 
  // reveals a green bottom line...error in FPT's G_fill_rectangle
  // ...now fixed

  dx = 1.0*w/ncols ;
  dy = 1.0*h/nrows ;

  for (i = 0 ; i < ncols ; i++) {
    for (j = 0 ; j < nrows ; j++) {
      k = (i + j) % 2 ;
      G_rgb(r[k],g[k],b[k]) ;
      G_fill_rectangle(i*dx,j*dy,dx,dy) ;
    }
  }

  q = G_wait_key() ;

  G_save_image_to_file(argv[1]) ;

}
