
#include <FPT.h>


int  make_arrow (double xs, double ys,  
                 double xe, double ye,
                 double half_thickness,
                 double *x, double *y)
// construct the coords for an arrow and leave them
// in the arrays pointed to by x and y
// return the number of points in the arrow polygon
// as the value of this function
{
  double h, dx,dy,len,cosangle,sinangle,t ;
  int i ;
  
  h = half_thickness ;

  dx = xe - xs ; dy = ye - ys ;
  len = sqrt(dx*dx + dy*dy) ;

  x[0] =  0 ; y[0] = 0 ;
  //  x[1] = -1.5*h ; y[1] =  1.5*h ;
  //  x[1] = -h ; y[1] =  h ;
  //  x[1] = 0 ; y[1] =  h ;
  //  x[1] = 0 ; y[1] =  0 ;
  //  x[1] = 0 ; y[1] = 0.5*h ;
  x[1] = 0 ; y[1] = 0.7*h ;

  x[2] =  len - 5*h ;  y[2] = h ;
  x[3] =  x[2] - 2*h ; y[3] = y[2] + 3*h ;
  x[4] =  len ; y[4] = 0 ;

  x[5] = x[3] ; y[5] = -y[3] ;
  x[6] = x[2] ; y[6] = -y[2] ;
  x[7] = x[1] ; y[7] = -y[1] ;

  cosangle = dx/len ;
  sinangle = dy/len ;
  i = 0 ;
  while (i < 8) {
    t    = cosangle*x[i] - sinangle*y[i] + xs ;
    y[i] = sinangle*x[i] + cosangle*y[i] + ys ;
    x[i] = t ;
    i = i + 1 ;
  }
  
  return i ;
}




int main()
{
  //  analog clock using double buffering...simpler
  double hours,minutes,seconds,x,y,nx,ny,theta,digit ;
  double hx,hy,mx,my,sx,sy,angle ;
  double oldhourtheta,oldminutetheta,oldsecondtheta ;
  char text[3] ;
  double hms[3] ;
  double xx[100],yy[100] ;
  int num ;
 

  G_init_graphics(600,600) ;

  while (0 < 1) {

    // blank the window
    G_rgb(0.3, 0.3, 0.3) ;
    G_clear() ;

    // outer circle of the clock face 

    G_rgb(0,0,1) ;
    G_fill_circle(300,300,230) ;
    G_rgb (1,0.5,0) ; 
    G_fill_circle(300,300,220) ;


    // digits on the clock face 
    G_rgb (0,0,0) ;
    theta = 90 ; // degrees 
    digit = 0 ;
    while (theta > -270) {
        theta = theta - 30 ;
        digit = digit + 1 ;
        nx = 200*cos(theta*M_PI/180) + 300 ;
        ny = 200*sin(theta*M_PI/180) + 300 ;
        if (digit >= 10) { 
                   text[0] = '1' ;
                   text[1] = '0' + digit - 10 ;
                   text[2] = '\0' ;
		 }
        else {
                   text[0] = '0' + digit ;
                   text[1] = '\0' ;
		 }
        G_draw_string(text,nx-5,ny-5) ;
    }


    //    get_timeD(hms) ;
    //    hours   = hms[0] ;
    //    minutes = hms[1] ;
    //    seconds = hms[2] ;
    printf("enter hours minutes seconds") ;
    scanf("%lf %lf %lf",&hours,&minutes,&seconds) ;




    G_rgb (0,0,0) ; 

    // set the second hand 
    theta = 90 - 6*seconds  ;
    angle = theta*M_PI/180 ;
    sx = 175*cos(angle) + 300 ;
    sy = 175*sin(angle) + 300 ;

    //    G_line(300,300,sx,sy) ;
    num = make_arrow (300,300,
                      sx,sy,
                      3.0,
                      xx,yy) ;
    G_fill_polygon(xx,yy,num) ;


    // set the minute hand 
    theta = 90 - 6*(minutes + seconds/60.0)  ;
    angle = theta*M_PI/180 ;
    mx = 140*cos(angle) + 300 ;
    my = 140*sin(angle) + 300 ;

    //    G_line(300,300,mx,my) ;
    num = make_arrow (300,300,
                      mx,my,
                      3.0,
                      xx,yy) ;
    G_fill_polygon(xx,yy,num) ;


    // set the hour hand 
    theta = 90 - 30*(hours + minutes/60.0 + seconds/3600.0)  ;
    angle = theta*M_PI/180 ;
    hx = 75*cos(angle) + 300 ;
    hy = 75*sin(angle) + 300 ;

    //    G_line(300,300,hx,hy) ;
    num = make_arrow (300,300,
                      hx,hy,
                      3.0,
                      xx,yy) ;
    G_fill_polygon(xx,yy,num) ;


    G_rgb(0,0,0) ;
    G_fill_circle(300,300,12) ;

    G_display_image() ;

    break ;
 } // end while (0 < 1) 

 
  G_save_image_to_file("clock.xwd") ;

}

