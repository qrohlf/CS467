
#include <FPT.h>


double x[13] = {175,225,225,300,225,225,250,200,150,175,175,100,175} ;
double y[13] = {300,300,250,225,225,200,100,175,100,200,225,225,250} ;
int n = 13 ;


void translate (double dx, double dy)
{
  int i ;

  i = 0 ;
  while (i < n) {
     x[i] = x[i] + dx ;
     y[i] = y[i] + dy ;
     i = i + 1 ;
  }
}


void scale (double s)
{
  int i ;

  i = 0 ;
  while (i < n) {
     x[i] = s * x[i] ;
     y[i] = s * y[i] ;
     i = i + 1 ;
  }
}


void rotate (double degrees)
{
  double radians,c,s,t ;
  int i ;

  radians = degrees*M_PI/180.0 ;
  c = cos(radians) ;
  s = sin(radians) ;

  i = 0 ;
  while (i < n) {
      t    = x[i]*c - y[i]*s ;
      y[i] = y[i]*c + x[i]*s ;
      x[i] = t ;
      i = i + 1 ;
  }
}



int main() 
{
 double j ;
 char q ;

 G_init_graphics(601, 601) ;

 // the original design was for a 400x400
 // window and the object is centered on 200,200
 // so we recenter it and make it larger
 translate(-200, -200) ;
 scale(2.0) ;
 translate(300, 300) ;


 j = 0 ;
 while (j < 100) {

   G_rgb(0,0,0) ;
   G_clear() ;

   G_rgb(0, 0.5, 1) ;
   G_fill_polygon(x,y,n) ;

   G_rgb(1, 1, 0) ;
   G_polygon(x,y,n) ;

   //   q = G_wait_key() ;
   G_display_image() ;
   usleep(25000) ;  // microseconds 
   
   translate(-300, -300) ;
   scale(0.95) ;
   rotate(4) ;
   translate(300, 300) ;

   j=j+1 ;
 }

 G_rgb(1,0,0) ;
 G_fill_circle(300,300, 50) ;

 q = G_wait_key() ;

}

