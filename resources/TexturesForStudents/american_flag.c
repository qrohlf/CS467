
#include <FPT.h>

// american flag

void star (double xc, double yc, double r)
{
  double a,xa,ya,b,xb,yb ;
  int i ;

  for (i = 0 ; i < 5 ; i++) {
    a = M_PI/2 + i*2*M_PI/5 ;
    xa = xc + r*cos(a) ;
    ya = yc + r*sin(a) ;

    b = M_PI/2 + (i+2)*2*M_PI/5 ;
    xb = xc + r*cos(b) ;
    yb = yc + r*sin(b) ;

    G_fill_triangle(xa,ya,xb,yb,xc,yc) ;
  }
}


 
int  main()
{
 char q ;
 double w,h,uh,uw,uhgap,uwgap,dstar,tstripe ;
 int i,j ;
 double xc,yc ;


 printf("enter desired height of American flag ") ;
 scanf("%lf",&h) ;
 w = 1.9*h ;        // width of flag
 uh = 7.0*h/13.0 ;  // union height
 uw = 0.76*h ;      // union width
 uhgap = 0.054*h ;  // union height gap
 uwgap = 0.063*h ;  // union width gap
 dstar = 0.0616*h ; // diameter of a star
 tstripe = h/13.0 ; // thickness of a stripe



 G_init_graphics(w,h) ;

 G_rgb(255/255.0, 255/255.0, 255/255.0 ) ; // white background
 G_clear() ;


 // red stripes
 G_rgb(187/255.0, 19/255.0, 62/255.0 ) ; // proper shade of red

 // the seven red stripes
 for (i = 0 ; i < 6 ; i++) {
   G_fill_rectangle(0,i*2*tstripe, w,tstripe) ;
 }
 G_fill_rectangle(0,i*2*tstripe, w, (int)(h - i*2*tstripe + 0.5)) ;
 // the top stripe might need to be a bit wider to finish out the screen




 // blue union background
 G_rgb(0/255.0, 38/255.0, 100/255.0 ) ; // proper shade of blue
 // G_fill_rectangle(0,6.0*h/13.0, uw,uh) ;
 G_fill_rectangle(0,6.0*h/13.0, uw, (int)(h - 6.0*h/13.0 + 0.5)) ;
 // this makes sure there is no gap at the top



 G_rgb(255/255.0, 255/255.0, 255/255.0 ) ; // white stars
 // larger set of stars ... 5 rows of 6 stars
 for (i = 0 ; i < 5 ; i++) {
 for (j = 0 ; j < 6 ; j++) {

   yc = 6*tstripe + (2*i+1)*uhgap ;
   xc = (2*j+1)*uwgap ;
   star(xc,yc,dstar/2) ;
 }
 }


 // smaller set of stars ... 4 rows of 5 stars
 for (i = 0 ; i < 4 ; i++) {
 for (j = 0 ; j < 5 ; j++) {
   yc = 6*tstripe + (2*i+2)*uhgap ;
   xc = (2*j+2)*uwgap ;
   star(xc,yc,dstar/2) ;
 }
 }




 G_display_image() ;
 q = G_wait_key() ;

 G_save_image_to_file("american_flag.xwd") ;

}

