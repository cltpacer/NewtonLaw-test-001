

//////////////////////////////////////////////////////
//
//   high  school  physics text book project
//   verify  Newtone law
//   2017-08-01
//  
//      david Tang Taiwan
///////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <tgmath.h>

#ifndef    PRJ_NTTEST
#define    PRJ_NTTEST  1

#define    FILE_NAME_OUT  " /tmp/test_output.txt "
#ifdef     DEBUG
#define    aprintf      printf
#else
#define    aprintf      {}
#endif

/////////////////////////////////////////////////////////////////////////
int test_file_open()
{
FILE *fp;

fp = NULL;
fp = fopen("w+",FILE_NAME_OUT);
if (fp ==NULL)
{
    printf("\n Error open file exit now !! \n");
   // flag_open_file = 0; // err
   exit(1);  
  return 1;
}
    printf(" \n\n file test ok PASS !! \n\n");
  fclose(fp);
  return 0;
}




/////////////////////////////////////////////////////////////////////////   
int test_main_002()
{
  
 // printf(" %20.10lf \n",M_PI);


#ifdef   FILE_OK
  FILE* fp;
    fp = fopen("w+",FILE_NAME_OUT);
    
    if(fp ==NULL) 
    {
	printf("fp ==NULL \n");
	return 1;
    }
#endif  
  
  // M_PI = 3.14159
  // M_PI_2 = 1.570796
  double z  = 0.000000000001;
  double rzz = 0.00001 ;
  double thzz = 0.00001 ;

  /////////////////////////////////
  double R_earth = 10000;
  double h  = 100;
  double R_Max = 100;
  /////////////////////////////////
  double delta_th = 2*M_PI* thzz;
  double delta_r = R_Max * rzz;
  int i, j;
  double delta_area =   z;
  double area =  z;
  double r, th;

  double density = 200;  // metal

  double total_fource =0;
  double fource_delta ;

  double M1 =100;
  double delta_M2 = 0;
  double G= 6.67*(10^(-11)) ;
  
  area =  z;
   i =0;
   j =0;
  for(r =z ; r < R_Max ; r = r +delta_r)
  {
    delta_area =  z;
    for(th =  z ; th < 2*M_PI; th =th +delta_th )
    {
       	delta_area += (delta_th*(r))*(delta_r);  // arc*delta_r 
    
    } // end for th

    if( ((i++)%100)==0)
          putchar('.');   // it can speed up remote CPU ..
                            // i did not why it happan ..

    area += delta_area;


    delta_M2 = delta_area * density ;

    double short_R =  sqrt( powl(R_earth,2)-powl(R_Max,2) ) ;
    
    double x = short_R + R_earth + h;

    fource_delta = G*M1*delta_M2/(powl(x,2)) * ((short_R)/(r)) ;
    
    // fource_delta = G*M1*delta_M2/pow(x,2) * ((short_R)/(R_earth)) ;

    total_fource += fource_delta;
    
  } // end for r
  
  printf("\n\n disk area   = %lf \n \n " , area) ;
  printf("\n\n disk fource = %lf \n \n " , total_fource ) ;
    
#ifdef FILE_OK    
    fclose(fp);
#endif

}// end test_main_002



///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////   
int test_main_001()
{
  
  printf("\n start PI = %20.10lf \n",M_PI);  
  double x,y,z; // coordination
  
  
  double h = 100;
  
  // M_PI = 3.14159
  // M_PI_2 = 1.570796
  double zero  = 0.000000000001;
  double rzz = 0.001 ;
  double thzz = 0.001 ;
  double R_Max = 100000;
  double delta_th = 2*M_PI* thzz;
  double delta_r = R_Max * rzz;
  int i, j;
  double delta_area =   zero;
  double area =  zero;
  double r, th;
  double density = 1000000;
  double total_fource =0;
  double fource_delta ;
  double M1 = 60;
  double M2 = 60;
  
  
  double G= 6.6525*pow(10,-11) ;
  double R_real_earth = 6378000.14 ;  
  double M1_delta;
  double M1_real_earth =  5.9742*pow(10,24)   ;
  double dtocenter;
  
  char temp_c[100];
  int temp_int;
  
  
  i=0;  j=0;
  area =  zero;
  //total_fource
  total_fource =0;
  area =zero;
  for(r =zero ; r < R_Max; r = r +delta_r)
  {
    delta_area =  zero;
    fource_delta = zero;
    for(th =  zero ; th < 2*M_PI; th =th +delta_th)
    {
    delta_area += (delta_th*(r))*(delta_r);  // arc*delta_r 
    
    }// end for
    
 
    area += delta_area;
    
    M1_delta = delta_area * density ;
    dtocenter =  pow(R_real_earth,2) - pow(r,2);
    
    dtocenter = sqrt(dtocenter);
    if(dtocenter < 0)
      {
          printf(" \n exit!!\n");
          return 1;
            scanf("%i\n",&temp_int);
      }
    //sqrt( (x^2)+(r^2) ) ;
    x = dtocenter +R_real_earth + h ; //  .....
    double factor = dtocenter/R_real_earth;
    double temp_gfource = (G*M1_delta*M2)/pow(x,2);
    aprintf("\n dbg %lf %lf %lf %lf %lf \n",x,pow(x,2),M1_delta,M2,G);
    fource_delta = temp_gfource*factor ;
    total_fource += fource_delta; 
    aprintf("\n dbg =%lf %lf %lf %le \n", dtocenter,fource_delta,factor,temp_gfource);
      // scanf("%i\n",&temp_int);
    
    
    i++;
    if((i%100)==0)
    {
      printf("\n start PI = %20.10lf <%010i> %20.10le %20.10le kg  "
      ,M_PI,i,fource_delta,total_fource/9.8);  
    
         // putchar('.');   
    }
  }// end for
  
  printf( "  \n\n area = %lf km*km    gfource= %le kg\n \n " 
  , (area/1000000.001),total_fource/9.8) ;

    
   return 0;

}// end test_main_001

#endif






