#include <FPT.h>

int main (int argc, char **argv)
{
  int w,h ;
  double r[2],g[2],b[2] ;
  int i,j,k,q ;
  double cr,ci, zr,zi, t ;
  int max = 200 ;
  double u,v ;

  if (argc != 10) {
    printf("Usage : pgm  xwd_res_file_name  width height r0 g0 b0 r1 g1 b1\n") ;
    exit(0) ;
  }
  
  w = atoi(argv[2]) ;
  h = atoi(argv[3]) ;

  r[0] = atof(argv[4]) ;
  g[0] = atof(argv[5]) ;
  b[0] = atof(argv[6]) ;

  r[1] = atof(argv[7]) ;
  g[1] = atof(argv[8]) ;
  b[1] = atof(argv[9]) ;


  G_init_graphics(w,h) ;

  for (i = 0 ; i < w ; i++) {
    for (j = 0 ; j < h ; j++) {

      cr = (2.0*i/w - 1)*1.5 ;
      ci = (2.0*j/h - 1)*1.5 ;
      // so cr,ci in [-1.7, 1.7]
      cr -= 0.5 ; // translation for better centering

      zr = 0 ; 
      zi = 0 ;
      for (k = 0 ; k < max ; k++) {
	t = zr*zr - zi*zi + cr ;
        zi = 2*zr*zi + ci ;
        zr = t ;
        if (zr*zr + zi*zi > 4) { break ; }
      }

      u = 1.0*k/max ;
      v = 1.0 - u ;
      G_rgb(u*r[0] + v*r[1],
            u*g[0] + v*g[1],
            u*b[0] + v*b[1]) ;

      G_point(i,j) ;
    }
  }

  q = G_wait_key() ;

  G_save_image_to_file(argv[1]) ;

}
