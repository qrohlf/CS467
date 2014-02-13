
#include <FPT.h>

// draw a mathematically perfect pentagonal star
 
int  main()
{
 char q ;
 double ssize,n,radius,k,i,xc,yc,x1,y1,x2,y2,frac,offset ;
 double rr,gg,bb ;

 outS("how many stars ? ") ;
 n = inD() ;

 ssize = 800.0 ;
 G_init_graphics(ssize, ssize) ;

 G_rgb (0.8, 0.8, 0.8) ;
 G_clear() ;



 // srand48(100) ;
 // srand48(101) ;
 // srand48(102) ;
 // srand48(103) ;
 srand48(104) ;

 frac = 0.39 ; // by experiment...cheating
 // but at least the stars are theoretically perfect
 
 xc = 0.5*ssize ;  yc = 0.5*ssize ;   
 radius = 0.44*ssize ;

 i = 0 ;
 while (i < n) {

     if (fmod(i,2.0) == 0) {
           offset = M_PI/2.0 ;
     } else {
           offset = 3.0*M_PI/2.0 ;
     }

     rr = drand48() ; gg = drand48() ; bb = drand48() ;
     G_rgb (rr,gg,bb) ;

     k = 0 ;
     while (k < 5) {
        
        x1 = xc + radius*cos( k * 2.0*M_PI/5.0 + offset ) ;
        y1 = yc + radius*sin( k * 2.0*M_PI/5.0 + offset ) ;
    
        x2 = xc + radius*cos( (k+2.0) * 2.0*M_PI/5.0 + offset ) ;
        y2 = yc + radius*sin( (k+2.0) * 2.0*M_PI/5.0 + offset ) ;

        G_fill_triangle(xc,yc,  x1,y1,  x2,y2) ;

        k = k + 1.0 ;
     }

     radius = frac*radius ;
     i++ ;

     G_display_image() ;
     q = G_wait_key() ;
 }

 G_display_image() ;
 q = G_wait_key() ;

 G_save_image_to_file("nested_stars.xwd") ;

}

