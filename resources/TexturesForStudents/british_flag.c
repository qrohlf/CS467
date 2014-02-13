
#include <FPT.h>

// british flag
 
int  main()
{
 char q ;
 // 1:2
 double w,h ;
 double xx[100],yy[100] ;
 int n ;
 double dx,dy,d ;
 double f1,f2,f3,f4 ; 

 printf("enter desired height of British flag (2:1 ratio) ") ;
 scanf("%lf",&h) ;
 w = 2*h ;


 G_init_graphics(w+1,h+1) ;

 // G_rgb(0.85,0,0) ; // shade of red by visual inspection (for later) 
 G_rgb(0.10,0,0.40) ; // shade of blue by visual inspection

 // G_rgb(0,1,0) ; // reveals defects on bottom and right border lines
 // because G_fill_polygon isn't quite perfect
 // There is a raster tool version of this that is perfect.
 G_clear() ;



 // these fractions control the widths of the stripes... guessed from visual
 f1 = 0.11 ; // controls width of diagonal white stripes
 f2 = 0.70 ; // controls width of diagonal red stripes
 f3 = 0.17 ; // controls width of vertical/horizontal white stripes
 f4 = 0.10 ; // controls width of vertical/horizontal red stripes


 // wide diagonal white stripes
 dx =f1*w ; 
 // (h - dy)/(w - dx) = h / w  for parallelism, ergo
 // w*dy = h*dx, ergo
 dy = h*dx/w ;

 n = 0 ;
 xx[n]=    0 ; yy[n] =    0 ; n++ ;
 xx[n]=   dx ; yy[n] =    0 ; n++ ;
 xx[n]=    w ; yy[n] = h-dy ; n++ ;
 xx[n]=    w ; yy[n] =    h ; n++ ;
 xx[n]= w-dx ; yy[n] =    h ; n++ ;
 xx[n]=    0 ; yy[n] =    dy ; n++ ;
 G_rgb(1,1,1) ;
 G_fill_polygon(xx,yy,n) ;




 n = 0 ;
 xx[n]=    w ; yy[n] =    0 ; n++ ;
 xx[n]=    w ; yy[n] =   dy ; n++ ;
 xx[n]=   dx ; yy[n] =    h ; n++ ;
 xx[n]=    0 ; yy[n] =    h ; n++ ;
 xx[n]=    0 ; yy[n] = h-dy ; n++ ;
 xx[n]= w-dx ; yy[n] =    0 ; n++ ;
 G_rgb(1,1,1) ;
 G_fill_polygon(xx,yy,n) ;


 /////////////////////////////////////////////////////////
 // less wide diagonal red stripes
 dx = f2*dx ;
 dy = f2*dy ;


 n = 0 ;
 xx[n]=      w/2 ; yy[n] =    h/2 ; n++ ;
 xx[n]=        0 ; yy[n] =      0 ; n++ ;
 xx[n]=       dx ; yy[n] =      0 ; n++ ;
 xx[n]= w/2 + dx ; yy[n] =    h/2 ; n++ ;

 G_rgb(0.85,0,0) ;
 G_fill_polygon(xx,yy,n) ;

 n = 0 ;
 xx[n]=      w/2 ; yy[n] =    h/2 ; n++ ;
 xx[n]=        w ; yy[n] =      h ; n++ ;
 xx[n]=   w - dx ; yy[n] =      h ; n++ ;
 xx[n]=  w/2 -dx ; yy[n] =    h/2 ; n++ ;
 G_rgb(0.85,0,0) ;
 G_fill_polygon(xx,yy,n) ;



 n = 0 ;
 xx[n]=      w/2 ; yy[n] =      h/2 ; n++ ;
 xx[n]=        0 ; yy[n] =        h ; n++ ;
 xx[n]=        0 ; yy[n] =   h - dy ; n++ ;
 xx[n]=      w/2 ; yy[n] = h/2 - dy ; n++ ;
 G_rgb(0.85,0,0) ;
 G_fill_polygon(xx,yy,n) ;


 n = 0 ;
 xx[n]=      w/2 ; yy[n] =      h/2 ; n++ ;
 xx[n]=        w ; yy[n] =        0 ; n++ ;
 xx[n]=        w ; yy[n] =       dy ; n++ ;
 xx[n]=      w/2 ; yy[n] = h/2 + dy ; n++ ;
 G_rgb(0.85,0,0) ;
 G_fill_polygon(xx,yy,n) ;


 /////////////////////////////////////////////////////////
 // the very wide white vertical and horizontal stripes
 d = f3*h ;

 n = 0 ;
 xx[n]=        0 ; yy[n] =  h/2 - d ; n++ ;
 xx[n]=        w ; yy[n] =  h/2 - d ; n++ ;
 xx[n]=        w ; yy[n] =  h/2 + d ; n++ ;
 xx[n]=        0 ; yy[n] =  h/2 + d ; n++ ;
 G_rgb(1,1,1) ;
 G_fill_polygon(xx,yy,n) ;


 n = 0 ;
 xx[n]=  w/2 - d ; yy[n] =   0 ; n++ ;
 xx[n]=  w/2 + d ; yy[n] =   0 ; n++ ;
 xx[n]=  w/2 + d ; yy[n] =   h ; n++ ;
 xx[n]=  w/2 - d ; yy[n] =   h ; n++ ;
 G_rgb(1,1,1) ;
 G_fill_polygon(xx,yy,n) ;



 /////////////////////////////////////////////////////////
 // the very wide red vertical and horizontal stripes
 d = f4*h ;

 n = 0 ;
 xx[n]=        0 ; yy[n] =  h/2 - d ; n++ ;
 xx[n]=        w ; yy[n] =  h/2 - d ; n++ ;
 xx[n]=        w ; yy[n] =  h/2 + d ; n++ ;
 xx[n]=        0 ; yy[n] =  h/2 + d ; n++ ;
 G_rgb(0.85,0,0) ;
 G_fill_polygon(xx,yy,n) ;


 n = 0 ;
 xx[n]=  w/2 - d ; yy[n] =   0 ; n++ ;
 xx[n]=  w/2 + d ; yy[n] =   0 ; n++ ;
 xx[n]=  w/2 + d ; yy[n] =   h ; n++ ;
 xx[n]=  w/2 - d ; yy[n] =   h ; n++ ;
 G_rgb(0.85,0,0) ;
 G_fill_polygon(xx,yy,n) ;



 G_display_image() ;
 q = G_wait_key() ;

 G_save_image_to_file("british_flag.xwd") ;

}

