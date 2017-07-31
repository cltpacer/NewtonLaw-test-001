
#include <stdio.h>
#include <math.h>

int main()
{
  
 // printf(&quot;%20.10lf &#92;n&quot;,M_PI);
  
  
  // M_PI = 3.14159
  // M_PI_2 = 1.570796
  double z  = 0.000000000001;
  double rzz = 0.00001 ;
  double thzz = 0.00001 ;
  double R_Max = 100;
  double delta_th = 2*M_PI* thzz;
  double delta_r = R_Max * rzz;
  double i, j;
  double delta_area =   z;
  double area =  z;
  double r, th;
  double density = 2;
  double fource_total =0;
  double fource_delta ;
  double M1 =1, M2;
  double G= 6.67*(10^(-11)) ;
  
  area =  z;
  for(r =z ; r < R_Max; r = r +delta_r)
  {
    delta_area =  z;
    for(th =  z ; th < 2*M_PI; th =th +delta_th)
    {
    delta_area += (delta_th*(r))*(delta_r);  // arc*delta_r 
    
    
    //M2 = delta_area * density ;
    //double Real_R =  sqrt( (x^2)+(r^2) ) ;
    //fource_delta = G*M1*M2/(Real_R^2) * ((r+x)/(Real_R)) ;
    
    
    
    
    }
    area += delta_area;
    
  }
  
  printf("area=%lf \n \n", area) ;

    
    
    
}// end main


